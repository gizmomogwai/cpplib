#include <image/ImageOperations.h>

#include <string.h>
#include <cassert>

Image* ImageOperations::rotateLeft(Image& original) {

  PixelFormat& format = original.getFormat();
  Image* res = new Image(original.getHeight(), original.getWidth(), format.bitPerPixel);
  int bytePerPixel = format.bytePerPixel;

  for (unsigned int j=0; j<original.getHeight(); j++) {
    unsigned char* data = original.getData(0, j);
    unsigned char* targetData = res->getData(j, res->getHeight()-1);
    for (unsigned int i=0; i<original.getWidth(); i++) {
      memcpy(targetData, data, bytePerPixel);

      targetData -= res->getRowStride();
      data += bytePerPixel;
    }
  }

  return res;
}

Image* ImageOperations::rotateRight(Image& original) {
  PixelFormat& format = original.getFormat();
  Image* res = new Image(original.getHeight(), original.getWidth(), format.bitPerPixel);
  unsigned int bytePerPixel = format.bytePerPixel;

  for (unsigned int j=0; j<original.getHeight(); j++) {
    unsigned char* data = original.getData(0, j);
    unsigned char* targetData = res->getData(res->getWidth()-1-j, 0);

    for (unsigned int i=0; i<original.getWidth(); i++) {
      memcpy(targetData, data, bytePerPixel);

      targetData += res->getRowStride();
      data += bytePerPixel;
    }
  }

  return res;
}

Image* ImageOperations::getThumbnail(Image& original, int width) {
  float factor = ((float)width) / ((float)original.getWidth());

  int newWidth = width;
  int newHeight = (int)(original.getHeight() * factor);

  PixelFormat& format = original.getFormat();
  unsigned int bytePerPixel = format.bytePerPixel;
  unsigned int bitPerPixel = format.bitPerPixel;
  Image* res = new Image(newWidth, newHeight, bitPerPixel);

  float xPixelsPerPixel = ((float)original.getWidth()) / ((float)width);
  float yPixelsPerPixel = ((float)original.getHeight()) / ((float)newHeight);

  unsigned char* target = res->getData(0, 0);
  for (unsigned int j=0; j<res->getHeight(); j++) {
    for (unsigned int i=0; i<res->getWidth(); i++) {
      unsigned int startX = (int)(xPixelsPerPixel * i);
      unsigned int startY = (int)(yPixelsPerPixel * j);

      unsigned int endX = (int)(xPixelsPerPixel * (i+1));
      unsigned int endY = (int)(yPixelsPerPixel * (j+1));

      int count = (endX - startX) * (endY - startY);
      for (unsigned int channel=0; channel<bytePerPixel; channel++) {
        int v = 0;
        for (unsigned int j2=startY; j2<endY; j2++) {
          for (unsigned int i2=startX; i2<endX; i2++) {
            v += original.getData(i2, j2)[channel];
          }
        }
        *target++ = (unsigned char)(((float)v) / count);
      }
    }
  }

  return res;
}

Image* ImageOperations::getImageAsRGBA(Image& image) {
  assert(24 == image.getFormat().bitPerPixel);
  Image* res = new Image(image.getWidth(), image.getHeight(), 32);
  unsigned char* src = image.getData(0, 0);
  unsigned char* dst = res->getData(0, 0);
  for (unsigned int j=0; j<image.getHeight(); j++) {
    for (unsigned int i=0; i<image.getWidth(); i++) {
      *dst++ = *src++;
      *dst++ = *src++;
      *dst++ = *src++;
      *dst++ = 255;
    }
  }
  return res;
}
