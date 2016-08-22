#include <image/codecs/GifImageCodec.h>

#include <assert.h>
#include <iostream>
#include <io/InputStream.h>
#include <image/Image.h>

GifFileTypeWrapper::GifFileTypeWrapper(GifImageCodec* codec) 
  : fileType(0) {      

  fileType = ::DGifOpen(codec, GifImageCodec::gifRead);
	if (fileType == 0) {
		throw(Exception("could not read gifheader"));
	}
}

GifFileTypeWrapper::~GifFileTypeWrapper() {
  ::DGifCloseFile(fileType);
}

void GifFileTypeWrapper::readData() {
  int res = ::DGifSlurp(fileType);
  if (res == GIF_ERROR) {
    throw(Exception("could not read whole gif"));
  }
}

int GifFileTypeWrapper::getNOfImages() {
  return(fileType->ImageCount);
}

SavedImage* GifFileTypeWrapper::getImage(int idx) {
  assert((idx >= 0) && (idx < getNOfImages()));
  return(&(fileType->SavedImages[idx]));
}

void GifImageCodec::write(Image* image, OutputStream* out) throw (Exception) {
	throw(Exception("Not Implemented", __FILE__, __LINE__));
}

Image* GifImageCodec::read(InputStream* _in) throw (Exception) {
  in = _in;

  GifFileTypeWrapper wrapper(this);
  wrapper.readData();

	if (wrapper.getNOfImages() <= imageIdx) {
    throw(Exception("the desired imageidx is not available"));
  }

  SavedImage* gifImage = wrapper.getImage(imageIdx);
  GifImageDesc* imageDesc = &(gifImage->ImageDesc);
  colorMap = wrapper.getColorMap();
  if (colorMap == 0) {
    throw(Exception("keine globale farbtabelle evtl local???"));
  }

  // search for transparent color!!!!
  transparent = false;
  transparentIdx = 0;
  for (int ex=0; ex<gifImage->ExtensionBlockCount; ex++) {
    ExtensionBlock* ext = &(gifImage->ExtensionBlocks[ex]);
    if (ext->Function == 0xf9) {
      char flags = ext->Bytes[0];
      if ((flags & 0x1) != 0) {
        transparent = true;
        transparentIdx = (unsigned char)(ext->Bytes[3]);
      }
    }
  }

  width = imageDesc->Width;
	
  Image* image = new GifImage(width, imageDesc->Height, 
                           (transparent == true) ? 32 : 24, imageDesc->Left, imageDesc->Top);
  
  data = (unsigned char*)image->getBuffer()->getData();
  gifData = (unsigned char*)gifImage->RasterBits;

  if (imageDesc->Interlace) {
    const int startRows[] = {0, 4, 2, 1};
    const int offsets[] = {8, 8, 4, 2};
    for (int pass=0; pass<4; pass++) {
      for (unsigned int j=startRows[pass]; 
           j<image->getHeight(); 
           j += offsets[pass]) {
        data = image->getData(0, j);
        makeLine();
      }
    }
  } else {
    for (unsigned int j=0; j<image->getHeight(); j++) {
      makeLine();
    }
  }

  return image;
}

int GifImageCodec::gifRead(GifFileType* fileType, GifByteType* target, int length) {
  GifImageCodec* codec = (GifImageCodec*)fileType->UserData;
  return(codec->read(target, length));
}


int GifImageCodec::read(GifByteType* target, int length) {
  DataBuffer buffer(target, length, false);
  return(in->readFully(buffer));
}
