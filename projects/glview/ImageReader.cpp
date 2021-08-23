#include "ImageReader.h"

#include <iostream>
#include <image/Image.h>
//#include <image/codecs/GifImageCodec.h>
#include <image/codecs/ImageCodec.h>
//#include <image/codecs/JasperImageCodec.h>
#include <image/codecs/JpegImageCodec.h>
#include <image/codecs/PngImageCodec.h>
//#include <image/codecs/TiffImageCodec.h>
#include <io/BufferedInputStream.h>
#include <io/file/File.h>
#include <io/file/FileInputStream.h>
#include <lang/CleanUpObject.h>
#include <util/profile/ProfileObject.h>

std::string ImageReader::toLower(std::string &s) {
  char* buf = new char[s.length()];
  s.copy(buf, s.length());
  for(int i = 0; i < s.length(); i++) {
    buf[i] = tolower(buf[i]);
  }
  std::string r(buf, s.length());
  delete[](buf);
  return(r);
}

bool ImageReader::matches(std::string filename, std::string pattern) {
  return filename.find(pattern) != std::string::npos;
}

Image* ImageReader::readImage(std::string fileName) throw (Exception) {
  ProfileObject profiler("ImageReader::readImage");

  ImageCodec* codec = nullptr;
  std::string lowerCase = toLower(fileName);
  std::cout << "trying " << lowerCase << std::endl;
  if (matches(lowerCase, ".png")) {
    codec = new PngImageCodec();
  } else if (matches(lowerCase, ".jpg") ||
             matches(lowerCase, ".jpeg")) {
    codec = new JpegImageCodec();
  } else if (matches(lowerCase, ".gif")) {
    //codec = new GifImageCodec();
  } else if (matches(lowerCase, ".tif") ||
             matches(lowerCase, ".tiff")) {
  //  codec = new TiffImageCodec();
  } else if (matches(lowerCase, ".jp2") ||
             matches(lowerCase, ".jpc") ||
             matches(lowerCase, ".bmp") ||
             matches(lowerCase, ".pnm")) {
  //  codec = new JasperImageCodec();
  } else {
    std::string errorMessage("cannot find a codec for the file: ");
    errorMessage += fileName;
    throw Exception(errorMessage, __FILE__, __LINE__);
  }
  if (codec == nullptr) {
    throw Exception("no codec found", __FILE__, __LINE__);
  }
  CleanUpObject<ImageCodec> codecCleaner(codec);
  FileInputStream fIn(fileName);
  BufferedInputStream bIn(&fIn, false, 2048);
  Image* res = codec->read(&bIn);
  fflush(stdout);
  return res;
}

Image* ImageReader::readImage(File* file) throw (Exception) {
  return ImageReader::readImage(file->getPathName());
}
