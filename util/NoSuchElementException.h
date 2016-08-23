#ifndef _NoSuchElementException_h_
#define _NoSuchElementException_h_

#include <lang/Exception.h>

/** Exception falls ein eigentlich erwartetes element nicht 
 * gefunden werden kann.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-12-31, cK, Created.
 *   <li> 2001-02-08, cK, Message erzwungen.
 *   <li> 2001-07-05, cK, ToDo angepasst.
 * </ul>
 *
 * @version $Revision: 1.1 $, $Date: 2002/10/28 23:39:49 $
 *
 * @author cK, $Author: gizmo $
 */
class NoSuchElementException : public Exception {
  
 public: 
	/** Erzeugt eine Exception mit Fehlermessage.
	 *
	 * @param message Fehlerursache
	 */
	NoSuchElementException(const std::string message) : Exception(message) {
	}
	
	/** Erzeugt eine Exception mit Fehlermessage.
	 *
	 * @param message Fehlerursaceh.
	 * @param fileName Name des Files.
	 * @parma lineNr Zeile.
	 */
	NoSuchElementException(const std::string message, 
												 const std::string fileName, 
												 const int lineNr) 
		: Exception(message, fileName, lineNr) {
	}

};

#endif // _NoSuchElementException_h_
