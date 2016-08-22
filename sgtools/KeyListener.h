#ifndef _KeyListener_h_
#define _KeyListener_h_

class KeyEvent;

/** Interface fuer Keylistener. 
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-04-04, cK, Created.
 *   <li> 2001-04-11, cK, BugFix: Vergessen Destructor virtual anzugeben.
 * </ul>
 *
 * @@version $Revision$, $Date$
 *
 * @@author cK, $Author$
 */
class KeyListener {

	public:
    /** Raeumt auf. */
    virtual ~KeyListener() {
    }

    /** Wird aufgerufen, falls eine Taste gedrueckt wird.
     *
     * @@param KeyEvent Das event.
     */
		virtual void keyPressed(KeyEvent* e) = 0;
			
};


#endif // _KeyListener_h_

