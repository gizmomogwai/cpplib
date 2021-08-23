#ifndef LosslessRotationHandler_h_
#define LosslessRotationHandler_h_

#include <io/file/File.h>
#include <sgtools/KeyListener.h>
#include <sgtools/KeyEvent.h>
#include <sgtools/Engine.h>

#include "ImageViewNavigator.h"
#include "SelectionListener.h"
#include <image/codecs/JpegImageCodec.h>
#include <image/JpegImage.h>

class LosslessRotationHandler : public SelectionListener {
  public:
  LosslessRotationHandler(Engine* engine, ImageViewNavigator* navigator);

  virtual ~LosslessRotationHandler() {
  }

  void rotateLeft() {
    if (fCurrentFile != 0) {
      JpegImage image(fCurrentFile);
      std::cout << "rotate left" << std::endl;
      image.rotateLeft();
      fNavigator->reload();
    }
  }

  void rotateRight() {
    if (fCurrentFile != 0) {
      JpegImage image(fCurrentFile);
      std::cout << "rotate right" << std::endl;
      image.rotateRight();
      fNavigator->reload();
    }
  }

  void selectionChanged(File* f) {
    SelectionListener::selectionChanged(f);
  }

  private:
  ImageViewNavigator* fNavigator;

};

class LosslessRotationListener : public KeyListener {
  public:
  LosslessRotationListener(LosslessRotationHandler* handler) : fHandler(handler) {
  }

  virtual ~LosslessRotationListener() {}

  void keyPressed(KeyEvent* e);

  private:
  LosslessRotationHandler* fHandler;
};

#endif
