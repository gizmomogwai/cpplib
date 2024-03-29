#pragma once

#ifdef OSX
#define GL_SILENCE_DEPRECATION
  #include <GLUT/glut.h>
#else
  #include <GL/glut.h>
#endif


#include <sgtools/KeyEvent.h>

#include <iostream>

/** KeyEvents, die von einem GLUTKeyListener verschickt werden.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-04-05, cK, Created.
 * </ul>
 *
 * @author cK
 */
class GLUTKeyEvent : public KeyEvent {

 public:
  /** Erzeugt ein neues GLUTKeyEvent.
   *
   * @@param _key GLUT-Keycode
   */
  GLUTKeyEvent(unsigned int _key) : key(_key) {
    modifiers = glutGetModifiers();
  }

  bool shiftPressed() {
    return((modifiers & GLUT_ACTIVE_SHIFT) != 0);
  }

  bool ctrlPressed() {
    return((modifiers & GLUT_ACTIVE_CTRL) != 0);
  }

  bool altPressed() {
    return((modifiers & GLUT_ACTIVE_ALT) != 0);
  }

  bool keyPressed(unsigned int _key);

 private:
  /** Gedrueckte Taste. */
  unsigned int key;

  /** Modifiers. */
  int modifiers;

};
