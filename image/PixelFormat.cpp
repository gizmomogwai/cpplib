#include <image/PixelFormat.h>

PixelFormat::PixelFormat(int _bitPerPixel) {
  init(_bitPerPixel);
}

PixelFormat::PixelFormat(PixelFormat* format) {
  init(format->bitPerPixel);
}

void PixelFormat::init(int _bitPerPixel) {
	bitPerPixel = _bitPerPixel;
	bytePerPixel = _bitPerPixel / 8;
}
