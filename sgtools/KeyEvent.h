#pragma once

/** Alle infos ueber den aktuellen Tastendruck.
 *
 * Eigneltich interface zu verschiednene Events ...
 * so kann man leicht glut gegen win32 oder so austauschen,
 * da alles im KeyEvent drin ist.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-04-05, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.1.1.1 $, $Date: 2001/04/27 14:10:37 $
 *
 * @author cK, $Author: koestlin $
 */
class KeyEvent {
public:
  virtual ~KeyEvent() {
  }

    /** Ist die CTRLTaste gedrueckt.
     *
     * @return bool true falls ja.
     */
    virtual bool ctrlPressed() = 0;

    /** Ist die ALT-Taste gedrueckt.
     *
     * @return bool true falls ja.
     */
    virtual bool altPressed() = 0;

    /** Ist die SHIFT-Taste gedrueckt.
     *
     * @return bool true falls ja.
     */
    virtual bool shiftPressed() = 0;


    /** Ist eine normale Zeichentaste gedrueckt.
     *
     * @param key Buchstabe.
     *
     * @return bool true oder false
     */
    virtual bool keyPressed(unsigned int key) = 0;

    /** Konstante fuer Pfeil nach oben. */
    const static unsigned int UP;

    /** Konstante fuer Pfeil nach unten. */
    const static unsigned int DOWN;

    /** Konstante fuer Pfeil nach links. */
    const static unsigned int LEFT;

    /** Konstante fuer Pfeil nach rechts. */
    const static unsigned int RIGHT;

    /** Konstante fuer page up. */
    const static unsigned int PAGE_UP;

    /** Konstante fuer page down. */
    const static unsigned int PAGE_DOWN;

};
