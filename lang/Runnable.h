#pragma once

/** Oberklasse aller Klassen die von Threads ausgefuehrt werden koennen.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-06-02, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.1 $ $Date: 2002/10/28 23:27:35 $
 *
 * @author cK, $Author: gizmo $
 */
class Runnable {

public:
	/** Raeumt auf. */
	virtual ~Runnable() {
	}

	/** Wird von normalerweie von einem Thread ausgefuehrt, kann aber auch so
	 * aufgerufen werden.
	 */
	virtual void run() = 0;

};
