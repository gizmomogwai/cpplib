#include <image/Image.h>
#include <image/ImageReader.h>
#include <image/ImageOperations.h>
#include <iostream>
#include <lang/CleanUpObject.h>
#include <lang/Exception.h>
#include <io/file/File.h>

class AView {

  public:
    AView(Image* i, int maxWidth, int maxHeight) {

      float xRatio = ((float)maxWidth) / i->getWidth();
      float yRatio = ((float)maxHeight) / i->getHeight();

      float ratio = min(xRatio, yRatio);

      CleanUpObject<Image> originalCleaner(i);
      CleanUpObject<Image> image(ImageOperations::getThumbnail(*i, (int)(i->getWidth() * ratio)));

      unsigned char* data = image->getData(0, 0);
      unsigned char grey2Ascii[] = {'W', 'X', 'V', 'T', 'Y', 'I', ';', ':', '|', '!', '.', ' '};
      float tableSize = (float)sizeof(grey2Ascii);
      for (int j=0; j<image->getHeight(); j++) {
        for (int i=0; i<image->getWidth(); i++) {
          float v = 0;
          if (image->getFormat().bytePerPixel == 1) {
            v = data[0];
          } else if (image->getFormat().bytePerPixel == 3) {
            v = (float)(data[0] + data[1] + data[2]) / 3;
          } else {
            throw Exception("pixelformat not supported");
          }
          unsigned char greyIdx = (int)((v * tableSize) / 256);
          std::cout << grey2Ascii[greyIdx];
          data += image->getFormat().bytePerPixel;
        }
        std::cout << std::endl;
      }
    }
};


int main(int argc, char** args) {
  try {
    if (argc != 2) {
      throw Exception("usage: aview filename");
    }

    File f(args[1]);
    AView aview(ImageReader::readImage(&f), 80, 50);
  } catch (Exception& e) {
    std::cout << e.getMessage() << std::endl;
    return -1;
  }

  return 0;
}

