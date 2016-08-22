#ifndef ExifImageFileCleaner_h_
#define ExifImageFileCleaner_h_

#include <image/ImageApi.h>

//#include <image/codecs/JpegImageCodec.h>
#include <ExifImageFile.h>

class IMAGE_API ExifImageFileCleaner {
 public:
  
 ExifImageFileCleaner(ExifImageFile* imageFile) : fImageFile(imageFile) {
  }
  
  virtual ~ExifImageFileCleaner() {
    if( fImageFile->close() != EXIF_OK ) {
      std::cout << "could not close exifImageFile" << std::endl;
    }
  }
  
 private:
  ExifImageFile* fImageFile;
};

#endif
