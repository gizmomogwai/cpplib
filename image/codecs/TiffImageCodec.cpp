#include <image/codecs/TiffImageCodec.h>

#include <io/IOTools.h>
#include <io/ByteArrayOutputStream.h>

#include <image/Image.h>
#include <util/profile/ProfileObject.h>
#include <iostream>

class TIFFCleaner {

  public:
    TIFFCleaner(TIFF* _tiff) : tiff(_tiff) {
      if (tiff == 0) throw (Exception("illegal tiff-object"));
    }

    virtual ~TIFFCleaner() {
      TIFFClose(tiff);
    }

  private:
    TIFF* tiff;
};

Image* TiffImageCodec::read(InputStream* _in) throw (Exception) {

  ProfileObject profile("TiffImageCodec::read");

  ByteArrayOutputStream theStream(2000000);
  memMapping = &theStream;
  IOTools::copy(_in, memMapping, 2048);

  TIFFSetWarningHandler(TiffImageCodec::warningHandler);
  TIFF* tiff = TIFFClientOpen("dummy", 
                              "r", 
                              (thandle_t)this, 
                              TiffImageCodec::tiffReadFunc,
                              TiffImageCodec::tiffWriteFunc,
                              0, //TiffImageCodec::tiffSeekFunc,
                              TiffImageCodec::tiffCloseFunc,
                              TiffImageCodec::tiffSizeFunc,
                              TiffImageCodec::tiffMapFileFunc,
                              TiffImageCodec::tiffUnmapFileFunc);
  TIFFCleaner cleaner(tiff);

  int imageWidth;
  TIFFGetField(tiff, TIFFTAG_IMAGEWIDTH, &imageWidth);
  
  int imageHeight;
  TIFFGetField(tiff, TIFFTAG_IMAGELENGTH, &imageHeight);

  int scanLine = TIFFScanlineSize(tiff);
  int bytesPerPixel = scanLine / imageWidth;
  int bitPerPixel = bytesPerPixel * 8;

  if (bitPerPixel != 24) {
    throw(Exception("only 24-bit supported"));
  }

  Image* image = new Image(imageWidth, imageHeight, bitPerPixel);

  try {
    ProfileObject profile("TiffImageCodec::readscanlines");
    for (int j=0; j<imageHeight; j++) {
      TIFFReadScanline(tiff, (tdata_t)image->getData(0, j), j);
    }
  } catch (...) {
    delete(image);
    image = 0;
    throw;
  }

  return(image);
}


void TiffImageCodec::warningHandler(const char* module, const char* fmt, va_list ap) {
  std::cout << "TiffCodec - " << module << ", " << fmt << std::endl;
  return;
}

int TiffImageCodec::tiffMapFileFunc(thandle_t clientData, tdata_t* data, toff_t* size) {

  TiffImageCodec* codec = (TiffImageCodec*)clientData;
  *data = codec->memMapping->getData()->getData();
  *size = codec->memMapping->getBytesWritten();
  return(1);
}

