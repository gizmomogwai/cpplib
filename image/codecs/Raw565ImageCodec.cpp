#include <image/codecs/Raw565ImageCodec.h>

#include <io/OutputStream.h>
#include <image/Image.h>
#include <assert.h>
#include <io/DataOutputStream.h>

void Raw565ImageCodec::write(Image* image, OutputStream* out) throw (Exception) {

  assert(image->getFormat().bitPerPixel == 24);
  DataOutputStream help(out, false);

	unsigned char* data = image->getData(0, 0);
  help.writeShort(image->getWidth());
  help.writeShort(image->getHeight());

  for (unsigned int j=0; j<image->getHeight(); j++) {
    for (unsigned int i=0; i<image->getWidth(); i++) {
      int r = *data++;
			int g = *data++;
		  int b = *data++;
			writePixel(out, r, g, b);
    }
  }
}

void Raw565ImageCodec::writePixel(OutputStream* out, 
																										       int r, 
                                                           int g, 
                                                           int b) throw (IOException) {
  unsigned char byte = (r & 0xf8) | ((g & 0xe0) >> 5);
	out->write(byte);
	byte = ((g & 0x1c) << 3) | ((b & 0xf8) >> 3);
	out->write(byte);
}
