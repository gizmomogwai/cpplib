#ifndef _Timer_h_
#define _Timer_h_

#include <lang/Thread.h>
#include <lang/Event.h>

/** Sollte eignetlich ein Timer sein, der alle paar Millisekunden 
 * losschlaegt.
 *
 * Das mit dem Thread ist unschoen, aber unter windows ist das mit dem 
 * Windowhandle soo bloed.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-05-06, cK, Created.
 * </ul>
 *
 * @todo Das mit dem Thread ist nicht tight!
 *
 * @version $Revision: 1.1 $, $Date: 2002/10/28 23:27:36 $
 *
 * @author cK, $Author: gizmo $
 */
class Timer : public Thread, public Event {
 public:
	/** Erzeugt einen Timer der in Regelmaessigen abstaenden losschlaegt.
	 *
	 * @param _millis Anzahl von Millisekunden zwischen den aufrufen.
	 */
	Timer(int _millis) : millis(_millis), stop(false) {
		start();
	}

	/** Raeumt auf. */
	virtual ~Timer() {
	}

	/** Stoppt den Timer. */
	void pleaseStop() {
		stop = true;
	}

	/** Implementiert die fastendlosschleife.
	 * Nach der angegebenen Zeit wird jeweils timeElapsed aufgerufen
	 */
	void run() {
		while (stop == false) {
			sleep(millis);
			timeElapsed();
		}
		setEvent();
	}

	/** Muss ueberschrieben werden um etwas zu machen		
	 */
	virtual void timeElapsed() = 0;	

 private:
	/** Anzahl von Millisekunden zwischen den TimeElapsed aufrufen. */
	unsigned int millis;

	/** Flag um den Timer zu stoppen. */
	bool stop;
	
};

#endif // _Timer_h_
