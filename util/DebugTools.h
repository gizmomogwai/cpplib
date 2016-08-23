#ifndef _DebugTools_h_
#define _DebugTools_h_

#ifdef WIN32
  #include <windows.h>
#endif

/** Klasse die mit Systemfehlern umgeht.
 *
 * <p>
 * Currciulum Vitae:
 * <ul>
 *   <li> 2001-03-31, Created.
 * </ul>
 *
 * @version $Revision: 1.1 $, $Date: 2002/10/28 23:39:49 $
 *
 * @author cK, $Author: gizmo $
 */
class DebugTools {
  
 public:
	/** Gibt den letzen Systemfehler in einer Messagebox aus.
	 *
	 * @param value Soll der Fehler untersuchtwerden.
	 */
  static void printLastError(bool value);		
  
};

#endif
