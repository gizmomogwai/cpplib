#include <image/codecs/RleImageCodec.h>

#include <io/OutputStream.h>
#include <image/Image.h>
#include <assert.h>
#include <io/DataOutputStream.h>

void RleImageCodec::write(Image* image, OutputStream* out) throw (Exception) {

  assert(image->getFormat().bitPerPixel == 24);
  DataOutputStream help(out, false);
  dOut = &help;

  unsigned char* data = 0;
  int lineDelta = image->getWidth() * 3;
  if (vFlip == false) {
    data = (unsigned char*)(image->getData(0, 0));
  } else {
    lineDelta = -lineDelta;
    data = (unsigned char*)(image->getData(0, 
                                           image->getHeight()-1));
  }

  dOut->writeInt(image->getWidth());
  dOut->writeInt(image->getHeight());

  unsigned char r = data[0];
  unsigned char g = data[1];
  unsigned char b = data[2];
  unsigned int rle = 0;
  unsigned char* line = data;
  for (unsigned int j=0; j<image->getHeight(); j++) {
    for (unsigned int i=0; i<image->getWidth(); i++) {

      unsigned char newR = *line++;
      unsigned char newG = *line++;
      unsigned char newB = *line++;

      if ((r == newR) && (g == newG) && (b == newB)) {

        rle++;
        
      } else {

        while (rle > 255) {

          writePixels(255, r ,g, b);
          rle -= 255;
        }
        writePixels(rle, r , g , b);
                
        r = newR;
        g = newG;
        b = newB;
        rle = 1;
      }
    }
    data += lineDelta;
    line = data;
  }

  if (rle != 0) {

    while (rle > 255) {   
      
      writePixels(255, r ,g, b);
      rle -= 255;
    }
    writePixels(rle, r, g, b);
  }
}

void RleImageCodec::writePixels(int rle, 
                                unsigned char r, 
                                unsigned char g, 
                                unsigned char b) throw (Exception) {

  dOut->writeByte(rle & 0xff);
  dOut->writeByte(r);
  dOut->writeByte(g);
  dOut->writeByte(b);
}
