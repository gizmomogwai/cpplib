#include <image/Image.h>

#include <stdlib.h>
#include <iostream>
#include <string.h>

#include <lang/ByteDataBuffer.h>

Image::Image(unsigned int _width, unsigned int _height, unsigned int _bitPerPixel) 
  : width(_width), 
    height(_height), 
    format(_bitPerPixel), 
    data(new ByteDataBuffer(_width * _height * format.bytePerPixel)),
    fOwnData(true)
{
}

Image::Image(unsigned int width_, unsigned int height_, unsigned int bitPerPixel_, DataBuffer& buffer_) 
  : width(width_), 
    height(height_), 
    format(bitPerPixel_), 
    data(&buffer_),
    fOwnData(false) {
  if (format.bytePerPixel * width * height != data->getSize()) {
    throw Exception("wrong datasize for width and height");
  }
}

Image::~Image() {
  if (fOwnData) {
    delete data;
  }
}

void Image::clear() {
  getBuffer()->clear();
}

DataBuffer* Image::getBuffer() {
  return(data);
}

unsigned int Image::getWidth() {
  return(width);
}

unsigned int Image::getHeight() {
  return(height);
}

PixelFormat& Image::getFormat() {
  return format;
}

void Image::setAlpha(unsigned char v) {
  if (getFormat().bitPerPixel != 32) {
    throw Exception("Image::setAlpha - cannot handle bitdepth != 32 bit", 
		    __FILE__, __LINE__);
  }
  unsigned char* help = (unsigned char*)(data->getData());
  help += 3;
  for (unsigned int i=getWidth()*getHeight(); i>0; i--) {
    *help = v;
    help += 4;
  }
}

Image* Image::getRect(int left, int top, int width, int height) {
  Image* res = new Image(width, height, getFormat().bitPerPixel);
  int sourceRowStride = getRowStride();
  int targetRowStride = res->getRowStride();
  unsigned char* sourceData = getData(left, top);
  unsigned char* targetData = res->getData(0, 0);
  for (int j=0; j<height; j++) {
    memcpy(targetData, sourceData, targetRowStride);
    sourceData += sourceRowStride;
    targetData += targetRowStride;
  }
  return(res);
}

Image* Image::getClippedRect(int left, int top, int width, int height) {
  Image* res = new Image(width, height, getFormat().bitPerPixel);
  res->clear();
  int realHeight = (top + height < (int)getHeight()) ? height : getHeight() - top;
  int realWidth = (left + width < (int)getWidth()) ? width : getWidth() - left;
  int sourceRowStride = getRowStride();
  int copyStride = realWidth * getFormat().bytePerPixel;
  int targetRowStride = res->getRowStride();
  unsigned char* sourceData = getData(left, top);
  unsigned char* targetData = res->getData(0, 0);
  for (int j=0; j<realHeight; j++) {
    memcpy(targetData, sourceData, copyStride);
    sourceData += sourceRowStride;
    targetData += targetRowStride;
  }
  return(res);
}
