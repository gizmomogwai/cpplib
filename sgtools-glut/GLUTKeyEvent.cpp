#include <sgtools-glut/GLUTKeyEvent.h>


bool GLUTKeyEvent::keyPressed(unsigned int _key) {
  if (_key == KeyEvent::UP) {
    return key == 101;
  } else if (_key == KeyEvent::DOWN) {
    return key == 103;
  } else if (_key == KeyEvent::LEFT) {
    return key == 100;
  } else if (_key == KeyEvent::RIGHT) {
    return key == 102;
  } else if (_key == KeyEvent::PAGE_UP) {
    return key == 104;
  } else if (_key == KeyEvent::PAGE_DOWN) {
    return key == 105;
  } else {
    if (ctrlPressed() == true) {
      return _key == key + 96;
    } else {
      return _key == key;
    }
  }
}

