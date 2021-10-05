#pragma once

#include <sgtools/KeyListener.h>
#include <sgtools/KeyEvent.h>
#include <sgtools/Engine.h>

/** KeyListener, der bei Tastendruck, die Engine zerstoehrt und dann
 * das programm per exit beendet.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-04-11, cK, Created.
 *   <li> 2001-04-30, cK, esc als quitkey added.
 * </ul>
 *
 * @@version $Revision: 1.1.1.1 $, $Date: 2001/04/27 14:10:37 $
 *
 * @@author cK, $Author: koestlin $
 */
class QuitKeyListener : public KeyListener {

  public:
    /** Neuer Listener.
     *
     * @@param _engine Engine, die beendet werden soll.
     */
    QuitKeyListener(Engine* _engine) : engine(_engine) {
    }

    void keyPressed(KeyEvent* e) {
      if (((e->keyPressed('q') == true) && (e->ctrlPressed() == true)) ||
         (e->keyPressed((unsigned int)27) == true)) {
        engine->quit();
      }
    }

  private:
    /** Zugehoerige Engine. */
    Engine* engine;

};
