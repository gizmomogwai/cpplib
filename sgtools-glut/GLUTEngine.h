#pragma once

#include <GLUT/glut.h>

#include <list>
#include <util/ListIterator.h>

#include <sgtools/Engine.h>
#include <sgtools/KeyListener.h>
#include <sgtools-glut/GLUTKeyEvent.h>

#include <assert.h>


/** Erster Versuch einer Engine ... es ist noch nicht gewiss,
 * was so eine Engine alles koennen muss!
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-04-04, cK, Created.
 *   <li> 2001-04-11, cK, An Engine-Schnittstelle angepasst.
 * </ul>
 *
 * @@version $Revision: 1.2 $, $Date: 2001/08/06 15:44:10 $
 *
 * @@author cK, $Author: koestlin $
 */
class GLUTEngine : public Engine {

  public:
    /** Erzeugt die Engine mit einer gewissen anfangsgroesse.
     *
     * @@param _width gewuenschte Breite.
     * @@param _height gewuenschte Hoehe.
     * @@param _windowName name des Fensters.
     */
    GLUTEngine(int argc, char** args,
               int _width, int _height,
               std::string windowName);

    /** Raeumt auf. */
    virtual ~GLUTEngine() {
    }

    void setSize(int width, int height);

    /** GLUTHilfsmethoden. */
    static void staticDisplayFunc();

    /** reshape methode die der glut angeboten werden kann.
     *
     * @@param width Neue breite,.
     * @@param height neue Hoehe.
     */
    static void staticReshapeFunc(int width, int height);

    /** keypressed methode, die der glut angeboten werden kann.
     *
     * @@param key Tastencode.
     * @@param x X-Position.
     * @@param y Y-Position.
     */
    static void staticKeyPressed(unsigned char key, int x, int y);

    /** spectialPressed dir der glut angeboten werden kann.
     *
     * @@param key Tastencode.
     * @@param x X-Position.
     * @@param y Y-Positoin.
     */
    static void staticSpecialPressed(int key, int x, int y);

    /** Beendet alles. */
    void quit() {
      std::cout << "GlutEngine::quit - so jetzt raus" << std::endl;
      if (fWindow != 0) {
        glutDestroyWindow(fWindow);
        fWindow = 0;
      }
      Engine::quit();
      std::cout << "GlutEngine::quit - calling exit" << std::endl;
      exit(0);
    }

    /** Laessst die Engine losrennen. */
    void run() {
      if (root == nullptr) {
        throw(Exception("GLUTEngine::run - vergessen root zu setzen???", __FILE__, __LINE__));
      }
      glutMainLoop();
      std::cout << "hier" << std::endl;
    }

  private:
    /** Engineinstance. */
    static GLUTEngine* instance;

    /** Soll die Visitorloop unterbrochen werden. */
    static bool forceRedisplay;

    /** The GLUT Window */
    int fWindow;

};
