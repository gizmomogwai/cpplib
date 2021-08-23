#include "LosslessRotationHandler.h"


void LosslessRotationListener::keyPressed(KeyEvent* e) {
	if (e->keyPressed('l') == true) {
	  fHandler->rotateLeft();
	} else if (e->keyPressed('r') == true) {
	  fHandler->rotateRight();
	}
}

LosslessRotationHandler::LosslessRotationHandler(Engine* engine, ImageViewNavigator* navigator) : fNavigator(navigator) {
  navigator->addSelectionListener(this);
  engine->addKeyListener(new LosslessRotationListener(this));
}
