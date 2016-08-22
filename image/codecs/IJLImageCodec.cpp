#include <image/codecs/IJLImageCodec.h>

#include <io/ByteArrayOutputStream.h>
#include <lang/ByteDataBuffer.h>
#include <lang/CleanUpObject.h>
#ifdef WIN32
#include <ijl.h>
#endif
#include <iostream>
#include <lang/HPStopWatch.h>

#ifdef LINUX
Image* IJLImageCodec::read(InputStream* in) throw (Exception) {
  throw(Exception("IJLImageCodec::read - not or never implemented for linux", __FILE__, __LINE__));
}
#endif

#ifdef WIN32
Image* IJLImageCodec::read(InputStream* in) throw (Exception) {

  HPStopWatch stopper;
  stopper.start();
  // alles kopieren und als buffer der ijl anbieten
  ByteArrayOutputStream out(500000);
  ByteDataBuffer buffer(500000);
  
  int red = in->read(&buffer);
  while (red != -1) {
    out.write(&buffer, 0, red);
    red = in->read(&buffer);
  }

  stopper.stop();
  std::cout << "In Buffer kopieren: " << stopper.getDelta();
  stopper.start();
  JPEG_CORE_PROPERTIES imageProperties;
  memset(&imageProperties, 0, sizeof(JPEG_CORE_PROPERTIES));

  IJLERR res = IJL_OK;
  res = ijlInit(&imageProperties);
  if (res != IJL_OK) {
    std::cout << "Error" << ijlErrorStr(res);
    throw(Exception("IJLImageCodec::read - could not Initialize IJL", 
                    __FILE__, __LINE__));
  }

  // ijl mit bytes fuettern
  imageProperties.JPGBytes = (unsigned char*)(out.getData()->getData());
  imageProperties.JPGSizeBytes = out.getBytesWritten();

  res = ijlRead(&imageProperties, IJL_JBUFF_READPARAMS);
  if (res != IJL_OK) {
    std::cout << "Error" << ijlErrorStr(res);
    ijlFree(&imageProperties);
    throw(Exception("IJLImageCodec::read - could not read params", 
                    __FILE__, __LINE__));
  }

  switch (imageProperties.JPGChannels) {
    case 1:
      throw(Exception("IJLImageCodec::read - 1 channel not suppoerted", __FILE__, __LINE__));
    case 3:
      imageProperties.JPGColor    = IJL_YCBCR;
      imageProperties.DIBChannels = 3;
      imageProperties.DIBColor    = IJL_RGB;
      break;
  }

  imageProperties.DIBWidth = imageProperties.JPGWidth;
  imageProperties.DIBHeight = imageProperties.JPGHeight;
  imageProperties.DIBPadBytes = 0;

  Image* result = new Image(imageProperties.DIBWidth, imageProperties.DIBHeight, 24);
  
  imageProperties.DIBBytes = (unsigned char*)(result->getBuffer()->getData());

  res = ijlRead(&imageProperties, IJL_JBUFF_READWHOLEIMAGE);
  if (res != IJL_OK) {
    std::cout << "Error" << ijlErrorStr(res);
    delete(result);
    result = 0;
    ijlFree(&imageProperties);
    throw(Exception("IJLImageCodec::read - error while reading image", __FILE__, __LINE__));
  }

  ijlFree(&imageProperties);
  
  stopper.stop();
  std::cout << "auslesen: " << stopper.getDelta() << std::endl;
  
  return(result);
}


#endif
