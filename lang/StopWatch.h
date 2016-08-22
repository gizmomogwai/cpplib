#ifndef _StopWatch_h_
#define _StopWatch_h_

#include <lang/LangApi.h>

/** Stopuhr die GetTickCount verwendet.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-11-21, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.1 $, $Date: 2002/10/28 23:27:35 $
 *
 * @author cK, $Author: gizmo $
 */
class LANG_API StopWatch {
 public:
	virtual ~StopWatch() {
	}

	/** Startet die Stopuhr. */
	virtual void start() = 0;

	/** Stoppt die Stopuhr. */
	virtual void stop() = 0;
	
	/** Liefert die Zeit zwischen dem letzen start und stop in
	 * millisekunden. 
	 *
	 * @return double Zeit in Millisekunden.
	 */
	virtual double getDelta() = 0;

};


#endif // _StopWatch_h_
