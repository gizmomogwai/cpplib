#pragma once

#include "SelectionListener.h"
#include <sgtools/KeyListener.h>
#include <sgtools/KeyEvent.h>
#include <sgtools/Engine.h>
#include "ImageViewNavigator.h"

class DeleteFileHandler : public SelectionListener {
  public:
    DeleteFileHandler(Engine* engine, ImageViewNavigator* navigator);

    virtual ~DeleteFileHandler() {
      std::cout << "~DeleteFileHandler" << std::endl;
    }

    void deleteFile();

};

class DeleteFileListener : public KeyListener {

  public:
    DeleteFileListener(DeleteFileHandler* handler) : fHandler(handler) {}
    virtual ~DeleteFileListener() {}
    void keyPressed(KeyEvent* e);
  private:
    DeleteFileHandler* fHandler;

};
