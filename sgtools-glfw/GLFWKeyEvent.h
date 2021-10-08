#pragma once

#include <sgtools/KeyEvent.h>


class GLFWKeyEvent : public KeyEvent {
 public:
 GLFWKeyEvent(int _key, int _scancode, int _action, int _mods) : key(_key)//,
    /*
      scancode(_scancode), action(_action), mods(_mods)
     */ {
   }

  bool ctrlPressed() {
    return false;
  }

  bool altPressed() {
    return false;
  }

  bool shiftPressed() {
    return false;
  }

  bool keyPressed(unsigned int _key) {
    if ((_key >= GLFW_KEY_0) && (_key <= GLFW_KEY_Z)) {
      return key == _key;
    }
    if (_key == UP) {
      return key == GLFW_KEY_UP;
    }
    if (_key == DOWN) {
      return key == GLFW_KEY_DOWN;
    }
    if (_key == PAGE_UP) {
      return key == GLFW_KEY_PAGE_UP;
    }
    if (_key == PAGE_DOWN) {
      return key == GLFW_KEY_PAGE_DOWN;
    }
    if (_key == '-') {
      return key == GLFW_KEY_SLASH;
    }
    if (_key == '+') {
      return key == GLFW_KEY_RIGHT_BRACKET;
    }
    if (_key == 27) {
      return key == GLFW_KEY_ESCAPE;
    }
    return false;
  }
 private:
  int key;
  /*
  int scancode;
  int action;
  int mods;
  */
};
