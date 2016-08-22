#include <image/JpegImage.h>

#include <stdio.h>
#include <iostream>
#include <cassert>

#include <lang/CleanUpObject.h>
#include <util/Date.h>
#include <image/Image.h>

#include <ExifImageFile.h>
#include <image/ExifImageFileCleaner.h>

#include <ExifImageDescUtils.h>
#include <ExifTags.h>

const char* JpegImage::format = "%.4d:%.2d:%.2d %.2d:%.2d:%.2d"; 
const char* JpegImage::easyFormat = "%d:%d:%d %d:%d:%d";

JpegImage::JpegImage(const File& file) : fFile(file) {
}

JpegImage::~JpegImage() {
}

class Rotation {
public:
  uint16 fValue;
  Rotation(uint16 value) : fValue(value) {
  }

  uint16 rotateRight() {
    switch (fValue) {
    case ORIENTATION_TOPLEFT:
      return ORIENTATION_RIGHTTOP;
    case ORIENTATION_RIGHTTOP:
      return ORIENTATION_BOTRIGHT;
    case ORIENTATION_BOTRIGHT:
      return ORIENTATION_LEFTBOT;
    case ORIENTATION_LEFTBOT:
      return ORIENTATION_TOPLEFT;
    default:
      std::cout << "unknown rotation: " << fValue << std::endl;
      throw Exception("unknown rotation");
    }
  }
  
  uint16 rotateLeft() {
    return Rotation(Rotation(rotateRight()).rotateRight()).rotateRight();
  }

  static uint16 getNormal() {
    return ORIENTATION_TOPLEFT;
  }

  bool isNormal() {
    return Rotation::getNormal() == fValue;
  }
  
};


void JpegImage::rotateLeft() {
  rotate(JXFORM_ROT_270);
  Rotation* rotation = getRotation();
  CleanUpObject<Rotation> cleaner(rotation);
  if (rotation) {
    setRotation(rotation->rotateRight());
  }
}

void JpegImage::normalizeRotation() {
  Rotation* rotation = getRotation();
  if (!rotation) return;
  while (!rotation->isNormal()) {
    delete rotation;
    rotateLeft();
    rotation = getRotation();
  }

  delete rotation;
}

void JpegImage::resetRotation() {
  setRotation(ORIENTATION_TOPLEFT);
}

void JpegImage::rotateRight() {
  rotate(JXFORM_ROT_90);
  Rotation* rotation = getRotation();
  CleanUpObject<Rotation> cleaner(rotation);
  if (rotation) {
    setRotation(rotation->rotateLeft());
  }
}

void JpegImage::setRotation(int rotation) {
  ExifImageFile exifImageFile;
  if (exifImageFile.open(fFile.getPathName().c_str(), "r+") == EXIF_OK) {
    ExifImageFileCleaner cleaner(&exifImageFile);
    
    ExifTagEntryT<uint16> rotationTag((exiftag_t)EXIFTAG_ORIENTATION, EXIF_SHORT, 1, static_cast<uint16>(rotation));
    
    ExifStatus res = exifImageFile.setGenericTag(rotationTag, EXIF_APP1_IFD0);
    if (res != EXIF_OK) {
      throw Exception("problems while writing exif-rotation", __FILE__, __LINE__);
    }
  } else {
    throw Exception("could not open exifdata for reading/writing", __FILE__, __LINE__);
  }
}

Rotation* JpegImage::getRotation() {
  ExifImageFile exifImageFile;
  if (exifImageFile.open(fFile.getPathName().c_str(), "rb") == EXIF_OK) {
    ExifImageFileCleaner cleaner(&exifImageFile);
    
    ExifStatus res;
    ExifTagEntry* rotationTag = exifImageFile.getGenericTag(EXIFTAG_ORIENTATION, EXIF_APP1_IFD0, res);
    if (res != EXIF_OK) {
      throw Exception("could not read exif-rotation!", __FILE__, __LINE__);
    }
    
    if (rotationTag == 0) {
      throw Exception("could really not load exif-rotation!", __FILE__, __LINE__); 
    }
    
    ExifTagEntryT<uint16>* rotation = (ExifTagEntryT<uint16>*)rotationTag;
    return new Rotation(rotation->getValue());
  }
  return 0;
}


void JpegImage::rotate(JXFORM_CODE transform) {
  FILE* inputFile = fopen(fFile.getPathName().c_str(), "rb");
  assert(inputFile);
  
  File outFile(fFile.getParent(), "transform.jpg");
  FILE* outputFile = fopen(outFile.getPathName().c_str(), "wb");
  assert(outputFile);
	
  struct jpeg_error_mgr errorManager;
  jpeg_std_error(&errorManager);
  
  struct jpeg_decompress_struct srcInfo;
  struct jpeg_compress_struct dstInfo;
  srcInfo.err = &errorManager;
  jpeg_create_decompress(&srcInfo);

  dstInfo.err = &errorManager;
  jpeg_create_compress(&dstInfo);

  jpeg_stdio_src(&srcInfo, inputFile);
  jpeg_stdio_dest(&dstInfo, outputFile);

  srcInfo.mem->max_memory_to_use = dstInfo.mem->max_memory_to_use;
	
  jcopy_markers_setup(&srcInfo, JCOPYOPT_ALL);
  (void) jpeg_read_header(&srcInfo, TRUE);
	
  jpeg_transform_info transformOption;
  transformOption.transform = transform;
  transformOption.trim = FALSE;
  transformOption.force_grayscale = FALSE;
  jtransform_request_workspace(&srcInfo, &transformOption);
  jvirt_barray_ptr* srcCoefArrays = jpeg_read_coefficients(&srcInfo);
  
  jpeg_copy_critical_parameters(&srcInfo, &dstInfo);
  jvirt_barray_ptr* dstCoefArrays = jtransform_adjust_parameters(&srcInfo, &dstInfo,
								 srcCoefArrays,
								 &transformOption);
  
  jpeg_write_coefficients(&dstInfo, dstCoefArrays);
  
  jcopy_markers_execute(&srcInfo, &dstInfo, JCOPYOPT_ALL);
  
  jtransform_execute_transformation(&srcInfo, &dstInfo,
				    srcCoefArrays,
				    &transformOption);
  
  jpeg_finish_compress(&dstInfo);
  jpeg_destroy_compress(&dstInfo);
  
  (void) jpeg_finish_decompress(&srcInfo);
  jpeg_destroy_decompress(&srcInfo);
  
  fclose(inputFile);
  fclose(outputFile);
  
  fFile.remove();
  outFile.rename(&fFile);
}

Date* JpegImage::getExifDate() {
  ExifImageFile exifImageFile;
  if (exifImageFile.open(fFile.getPathName().c_str(), "rb") == EXIF_OK) {
    ExifImageFileCleaner cleaner(&exifImageFile);

    ExifStatus res; 
    ExifTagEntry* dateTag = exifImageFile.getGenericTag(EXIFTAG_DATETIME, EXIF_APP1_IFD0, res);
    if (res != EXIF_OK) {
      throw Exception("could not read exifdate!", __FILE__, __LINE__);
    }

    if (dateTag == 0) {
      throw Exception("could really not load exifdate!", __FILE__, __LINE__); 
    }

    ExifTagEntryT<std::string>* date = (ExifTagEntryT<std::string>*)dateTag;
    int y, mon, d, h, min, s;
    int res2 = sscanf(date->getValue().c_str(), easyFormat, &y, &mon, &d, &h, &min, &s);

    if (res2 != 6) {
      std::string msg("unknown dateformat: '");
      msg += date->getValue();
      msg += "'";
      throw Exception(msg, __FILE__, __LINE__); 
    }


    return new Date(y, mon, d, h, min, s);
  }
  throw Exception("could not open exif info", __FILE__, __LINE__);
}

void JpegImage::setExifDate(const Date& d) {
  setTagByDate(EXIFTAG_DATETIME, EXIF_APP1_IFD0, d);
}

void JpegImage::setTagByDate(unsigned int tag, ExifTagLocation location, const Date& d) {
  ExifImageFile exifImageFile;
  if (exifImageFile.open(fFile.getPathName().c_str(), "r+") == EXIF_OK) {
    ExifImageFileCleaner cleaner(&exifImageFile);

    std::string value = JpegImage::date2String(d);
    
    ExifTagEntryT<std::string> dateTag(static_cast<exiftag_t>(tag), EXIF_ASCII, value.length()+1, value);
    ExifStatus res;
    exifImageFile.getGenericTag((exiftag_t)tag, location, res);
    if (res != EXIF_OK) {
      return;
    }
    res = exifImageFile.setGenericTag(dateTag, location);
    if (res != EXIF_OK) {
      throw Exception("problems while writing exif date", __FILE__, __LINE__);
    }
  } else {
    throw Exception("could not open exifdata for reading/writing", __FILE__, __LINE__);
  }

}

void JpegImage::setDateTimeDigitized(const Date& date) {
  setTagByDate(EXIFTAG_DALETIMEDIGITIZED, EXIF_APP1_EXIFIFD, date);
}

void JpegImage::setDateTimeOriginal(const Date& date) {
  setTagByDate(EXIFTAG_DATETIMEORIGINAL, EXIF_APP1_EXIFIFD, date);
}

std::string JpegImage::date2String(const Date& date) {
  char buffer[2048];
  sprintf(buffer, format, date.getYear(), 
	  date.getMonth(), 
	  date.getDay(), 
	  date.getHours(), 
	  date.getMinutes(), 
	  date.getSeconds());
  return std::string(buffer);
}

bool JpegImage::isExifDateInSyncWithFileDate() {
  CleanUpObject<Date> exifDate(getExifDate());
  CleanUpObject<Date> fileDate(fFile.getModificationDate());
      
  return exifDate->equals(*fileDate, 4);
}

void JpegImage::adjustFileDateFromExifDate() {
  CleanUpObject<Date> accessDate(fFile.getLastAccessDate());
  CleanUpObject<Date> exifDate(getExifDate());
  fFile.setDates(*accessDate, *exifDate);
}

Image* JpegImage::getThumbnail() {
	ExifImageFile exifImageFile;
	Image* res = 0;
    
	if (exifImageFile.open(fFile.getPathName().c_str(), "rb") == EXIF_OK) {
	  ExifImageFileCleaner cleaner(&exifImageFile);
  	ExifImageDesc* thumb = exifImageFile.getThumbnail();
		if (thumb != 0) {
			int w = thumb->numberOfColumns;
			int h = thumb->numberOfRows;
			if (thumb->numberOfComponents == 3) {
				res = new Image(w, h, 24);
				res->clear();

				ExifImageComponentDesc* r = &thumb->components[0];
				for (int j=0; j<h; j++) {
	  			for (int i=0; i<w; i++) {
  					unsigned char* data = res->getData(i, j);
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
		  std::cout << "no thumbnail in exif" << std::endl;
		}
	} else {
	  std::cout << "could not read exif" << std::endl;
	}
  
  return res;  
}

void JpegImage::setThumbnail(Image& image) {
  ExifImageFile exifImageFile;
  if (exifImageFile.open(fFile.getPathName().c_str(), "r+") == EXIF_OK) {
    ExifImageFileCleaner cleaner(&exifImageFile);
    
    ExifTagEntryT<exif_uint32> widthEntry(EXIFTAG_IMAGEWIDTH, EXIF_LONG, 1, image.getWidth());
    exifImageFile.setGenericTag(widthEntry, EXIF_APP1_IFD1);

    ExifTagEntryT<exif_uint32> heightEntry(EXIFTAG_IMAGELENGTH, EXIF_LONG, 1, image.getHeight());
    exifImageFile.setGenericTag(heightEntry, EXIF_APP1_IFD1);

    ExifImageInfo thumbInfo;
    thumbInfo.width = image.getWidth();
    thumbInfo.height = image.getHeight();
    
    ExifImageDesc* thumb = new ExifImageDesc; // is freed by exifimagefile
    exifAllocImageDesc(thumbInfo, *thumb);
    
    ExifImageComponentDesc* r = thumb->components;
    for (unsigned int j=0; j<image.getHeight(); j++) {
      for (unsigned int i=0; i<image.getWidth(); i++) {
        unsigned char* data = image.getData(i, j);
        unsigned char* target = r->theData + i*r->columnStride + j*r->lineStride;
        
        *target++ = *data++;
        *target++ = *data++;
        *target++ = *data++;
      }
    }
    exifImageFile.setThumbnail(thumb);
  } else {
    throw Exception("could not open exif file", __FILE__, __LINE__);
  }
}
