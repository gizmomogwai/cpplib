#include "ExifDateHandler.h"

#include <lang/CleanUpObject.h>
#include <io/file/FileInputStream.h>

// this handles the correct includement of the libjpeg.h
#include <image/codecs/JpegImageCodec.h>
#include <image/codecs/PngImageCodec.h>
#include <ExifImageFile.h>
#include "ImageReader.h"
#include <lang/Thread.h>
#include <assert.h>

ExifKeyListener::ExifKeyListener(ExifDateHandler* handler) : fHandler(handler) {}

ExifKeyListener::~ExifKeyListener() {}

void ExifKeyListener::keyPressed(KeyEvent* e) {
  if (e->keyPressed('a') == true) {
    fHandler->adjustDate();
  }
}

ExifDateHandler::ExifDateHandler(Engine* engine, ImageViewNavigator* navigator, SwitchableWatermark* thumb, SwitchableWatermark* async)
  : fExifDate(0), fThumb(thumb), fAsync(async) {

  fThumb->addReference();
  fAsync->addReference();
  navigator->addSelectionListener(this);
  engine->addKeyListener(new ExifKeyListener(this));
}

ExifDateHandler::~ExifDateHandler() {
  std::cout << "~exif date handler" << std::endl;
  fThumb->releaseReference();
  fAsync->releaseReference();
}


void ExifDateHandler::selectionChanged(File* file) {
  SelectionListener::selectionChanged(file);

  getExifInfos();
  checkSyncState();
}


void ExifDateHandler::adjustDate() {
  if (fCurrentFile != 0) {
    std::cout << "adjust file modification date from exif date" << std::endl;
    CleanUpObject<Date> accessDate(fCurrentFile->getLastAccessDate());
    fCurrentFile->setDates(*accessDate, fExifDate);
    checkSyncState();
  }
}

int getNextPow2(int v) {
  int res = 1;
  while (res < v) {
    res = res << 1;
  }
  return res;
}

void ExifDateHandler::getExifInfos() {
  ExifImageFile exifImageFile;
  Image* thumbImage = 0;
  int w = 0;
  int h = 0;

  if (exifImageFile.open(fCurrentFile->getPathName().c_str(), "rb") == EXIF_OK) {
    ExifImageDesc* thumb = exifImageFile.getThumbnail();
    if (thumb != 0) {
      w = thumb->numberOfColumns;
      h = thumb->numberOfRows;
      if (thumb->numberOfComponents == 3) {
        thumbImage = new Image(getNextPow2(w), getNextPow2(h), 24);
        thumbImage->clear();

        ExifImageComponentDesc* r = &thumb->components[0];
        for (int j=0; j<h; j++) {
          for (int i=0; i<w; i++) {
            unsigned char* data = thumbImage->getData(i, j);
            unsigned char* source = r->theData + i*r->columnStride + j*r->lineStride;

            *data++ = *source++;
            *data++ = *source++;
            *data++ = *source++;
          }
        }
      } else {
        std::cout << "can only handle 3 channel images" << std::endl;
      }
    } else {
      std::cout << "no thumbnail" << std::endl;
    }

    ExifPathsTags path;

    exifImageFile.getAllTags( 0xFFE1, "Exif", path );

    ExifPathsTagsIter i = path.begin() ;

    ExifPathsTagsIter pathEnd = path.end() ;
    while (i != pathEnd) {

           ExifTagsIter j = (*i).second.begin() ;
                ExifTagsIter tagEnd = (*i).second.end() ;

                while( j != tagEnd ) {
                    ExifTagEntry* tag = *(j) ;
                    exiftag_t tagId = tag->getTagNum();
                    ExifTagEntryT<std::string>* stringTag = 0;
                    if (tag->getType() == 2) {
                      stringTag = (ExifTagEntryT<std::string>*)tag;
                    }
                    switch (tagId) {
                      case 271:
                        std::cout << "Manufacturer " << stringTag->getValue() << std::endl;
                        break;
                      case 272:
                        std::cout << "Camera " << stringTag->getValue() << std::endl;
                        break;
                      case 306:
                        std::cout << "Date " << stringTag->getValue() << std::endl;
                        int y, mon, d, h, min, s;
                        int res = sscanf(stringTag->getValue().c_str(), "%d:%d:%d %d:%d:%d", &y, &mon,&d, &h, &min, &s);
                        assert(res == 6);

                        freeExifDate();
                        fExifDate = new Date(y, mon, d, h, min, s);

                        break;
                    }
                    j++;
                }

      i++;
    }
    if( exifImageFile.close() != EXIF_OK ) {
      std::cout << "could not close exifImageFile" << std::endl;
    }
  } else {
    std::cout << "could not open exif image file" << fCurrentFile->getPathName() << std::endl;
    freeExifDate();
  }

  if (thumbImage == 0) {
    fThumb->setVisible(false);
  } else {
    fThumb->setImage(thumbImage, w, h);
    fThumb->setVisible(true);
  }
}

void ExifDateHandler::freeExifDate() {
  if (fExifDate != 0) {
    delete fExifDate;
    fExifDate = 0;
  }
}

void ExifDateHandler::checkSyncState() {
  fAsync->setVisible(!isSynced());
}

bool ExifDateHandler::isSynced() {
  if (fExifDate != 0) {
    CleanUpObject<Date> fileDate(fCurrentFile->getModificationDate());
    bool res = fExifDate->equals(*fileDate, 4);
    if (!res) {
      std::cout << "warning! async dates" << std::endl;
      std::cout << "  filedate: " << fileDate->toString() << std::endl <<
                   "  exifdate: " << fExifDate->toString() << std::endl;
      std::cout << "press a to adjust" << std::endl;
    }
    return res;
  }
  return true;
}
