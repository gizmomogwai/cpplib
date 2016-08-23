#pragma once

#include <string>
#include <lang/Exception.h>

/** Klasse, die den Systemfehlercode auswertet und eine 
 * lesbare Ausgabe zu dem code erzeugt.
 *
 * <h2>WIN32</h2>
 * Geht auf GetLastError ab.
 *
 * <h2>LINUX</h2>
 * Geht auf errno ab.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-01-03, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.1 $, $Date: 2002/10/28 23:27:36 $
 *
 * @author cK, $Author: gizmo $
 */
class SysError {

 public:
	/** Wirft eine Exception.
	 *
	 * @param base Zusaetzlicher Text.
	 *
	 * @exception Exception abhangig vom Fehlercode.
	 */
  static void throwDetailedException(const char* base) throw (Exception) {
    std::string h(base);
    throwDetailedException(h);
  }
  
	/** Wirft eine Exception.
	 *
	 * @param base Zusaetzlicher Text.
	 *
	 * @exception Exception abhangig vom Fehlercode.
	 */
  static void throwDetailedException(std::string base) throw (Exception);

};
