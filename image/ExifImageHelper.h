#ifndef ExifImageHelper_h_
#define ExifImageHelper_h_

#include <image/ImageApi.h>

#include <string>
#include <sstream>

class IMAGE_API ExifImageHelper {
  public:
  static std::string getDescription(int id) {
    switch (id) {
    case 256:
      return "Image Width";
    case 257:
      return "Image Height";
    case 258:
      return "Bits Per Channel";
    case 259:
      return "Compression";
    case 270:
      return "Image Description";
    case 271:
      return "Manufacturer Name";
    case 272:
      return "Model Name";
    case 273:
      return "Strip Offset";
    case 274:
      return "Image Orientation";
    case 277:
      return "Samples Per Pixel";
    case 278:
      return "Rows Per Strip";
    case 282:
      return "Pixels/resolution in x";
    case 283:
      return "Pixels/resolution in y";
    case 296:
      return "Units of resolution";
    case 305:
      return "Software";
    case 306:
      return "Creation Date";
    case 513:
      return "JPEGIFOFFSET";
    case 514:
      return "JPEGIFBYTECOUNT";
    case 531:
      return "subsample positioning";
    case 34665:
      return "EXIFIFDPOINTER";
    case 33434:
      return "Exposuretime";
    case 33437:
      return "FNumber";
    case 34850:
      return "EXPOSUREPROGRAM";
    case 36867:
      return "EXIFTAG_DATETIMEORIGINAL";
    case  36868:
      return "EXIFTAG_DATETIMEDIGITIZED";
    case 36864:
      return "Exif Version";
    case 37121:
      return "COMPONENTSCONFIGURATION";
    case 37122:
      return "Compressed Bit Per Pixel";
    case 37380:
      return "EXPOSUREBIASVALUE";
    case 37381:
      return "MaxApertureValue";
    case 37382:
      return "SubjectDistance";
    case 37383:
      return "Metering Mode";
    case 37384:
      return "Light Source";
    case 37385:
      return "Flash";
    case 37386:
      return "Focallength";
    case 37500:
      return "Makernote";
    case 40960:
      return "FlashPixVersion";
    case 40961:
      return "ColorSpace";
    case 40962:
      return "PixelXDimension";
    case 40963:
      return "PixelYDimension";
    case 40965:
      return "EXIFINTEROPIFDPOINTER";
    case 41728:
      return "FILESOURCE";
      
    default:
      std::ostringstream s;
      s << "unknown " << id;
      return s.str();
    }
  }
};

#endif

