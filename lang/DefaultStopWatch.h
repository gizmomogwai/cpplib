#ifndef _DefaultStopWatch_h_
#define _DefaultStopWatch_h_

#include <lang/StopWatch.h>

#ifdef WIN32
  #ifdef _AFX
    #include <afx.h>
  #endif
  #ifdef _COMMAND
    #include <windows.h>
  #endif
#endif // WIN32

#ifdef LINUX

#endif

/** StopWatch, die auf GetTickCount arbeitet. 
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-11-??, ck, Created.
 *   <li> 2000-11-27, cK, Commented.
 * </ul>
 *
 * @version $Revision: 1.1 $, $Date: 2002/10/28 23:27:35 $
 *
 * @author $Author: gizmo $
 */
class DefaultStopWatch : public StopWatch {

 public:
	/** Erzeugt die neue Stopuhr. */
	DefaultStopWatch();

	/** Raeumt auf. */
	virtual ~DefaultStopWatch();

	void start();

	void stop();

	double getDelta();

 private:
#ifdef WIN32
	/** Startzeit. **/
	DWORD startTime;

	/** Endzeit. **/
	DWORD endTime;
#endif // WIN32

#ifdef LINUX
#endif // LINUX

};

#endif // _DefaultStopWatch_h_
