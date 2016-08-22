#ifndef _GLUTKeyEvent_h_
#define _GLUTKeyEvent_h_

#ifdef OSX
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
 * @@version $Revision: 1.1.1.1 $, $Date: 2001/04/27 14:10:37 $
 *
 * @@author cK, $Author: koestlin $
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

#endif // _GLUTKeyEvent_h_

