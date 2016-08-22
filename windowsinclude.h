#ifndef _windowsinclude_h_
#define _windowsinclude_h_

/** Windowsspezifisches include fuer alle sourcen.
 *
 * Vorteil:
 *  - kann als precompiled header verwendet werden???
 *  - WIN32_LEAN_AND_MEAN muss nur einmal angegeben werden.
 *
 * Usage:
 * statt windows.h oder aehnlichem #include <windowsinclude.h> verwenden.
 * 
 * <p>
 * Curriculum Vitae.
 * <ul>
 *   <li> 2001-04-17, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.1.1.1 $, $Date: 2001/04/27 14:10:22 $
 *
 * @author cK, $Author: koestlin $
 */
#ifdef WIN32
  #include <pragmaincludes.h>
  #ifndef WIN32_LEAN_AND_MEAN
	  #define WIN32_LEAN_AND_MEAN
  #endif
  #ifdef _AFX
    #include <AfxWin.h>
  #endif
  #ifdef _COMMAND
    #include <windows.h>
  #endif
#endif

#endif // _windowsinclude_h_
