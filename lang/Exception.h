#pragma once

#include <string>
#include <sstream>

/** Minimale Exceptionklasse.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-05-14, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.1 $, $Date: 2002/10/28 23:27:35 $
 *
 * @author cK, $Author: gizmo $
 */
class Exception {

 public:

	/** Erzeugt eine Exception ohne fehlermeldung. 
	 */
	Exception();

	/** Erzeugt einen Fehler mit einer Fehlermessage. 
	 *
	 * @param msg Message.
	 */
	Exception(const char* msg);

	/** Erzeugt einen neuen Error mit einer string-message. 
	 *
	 * @param _msg Stringmessage.
	 */
	Exception(const std::string _msg);

  /** Erzeugt einen neuen Error mit einer string-message. 
	 *
	 * @param _msg Stringmessage.
   * @param fileName Name des Files in dem der Fehler auftrat.
   * @param lineNr Zeilennr des Fehlers.
	 */
  Exception(const std::string _msg, 
            const std::string _fileName, 
            const int lineNr);

	/** Erzeugt eine neue Exception mit einer stringMessage.
	 *
	 * @parma msg Fehlerursache.
	 * @param fileName File in dem der Fehler auftrat.
	 * @param lineNr Zeile in der der Fehler auftrat.
	 */
	Exception(std::ostringstream* msg,
		  const std::string fileName,
		  const int lineNr);
	
	/** Gibt die resourcen wieder frei. 
	 */
	virtual ~Exception() {}
		
	/** Liefert die Fehlermessage.
	 *
	 * @return string* fehlermessage.
	 */
	std::string getMessage();

 private:
	/** Fehlermessage. */
	std::string msg;

};
