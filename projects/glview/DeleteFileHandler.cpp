#include "DeleteFileHandler.h"

#include <lang/Exception.h>

DeleteFileHandler::DeleteFileHandler(Engine* engine, ImageViewNavigator* navigator) {
  engine->addKeyListener(new DeleteFileListener(this));
 // navigator->addSelectionListener(this);
}

void DeleteFileHandler::deleteFile() {
  if (fCurrentFile != 0) {
    fCurrentFile->remove();
    File f(fCurrentFile->getPathName() + ".properties");
    if (f.exists()) {
      f.remove();
    }
  }
}

void DeleteFileListener::keyPressed(KeyEvent* e) {
  if (e->keyPressed(127) == true) {
    fHandler->deleteFile();
  }
}
