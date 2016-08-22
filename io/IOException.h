#ifndef _IOException_h_
#define _IOException_h_

#include <io/IoApi.h>

#include <lang/Exception.h>

/** Oberklasse fuer alle Exceptions, die im modul 
 * io auftreten koennen.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-01-01, cK, Created
 * </ul>
 *
 * @version $Revision: 1.3 $, $Date: 2001/06/06 10:37:20 $
 *
 * @author cK, $Author: koestlin $
 */
class IO_API IOException : public Exception {  

 public:
	/** Erzeugt eine neue IOException.
	 *
	 * @param _msg Message.
	 */
	IOException(const std::string _msg) : Exception(_msg) {
	}

	/** Erzeugt eine neue IOException.
	 *
	 * @param _msg Message.
	 * @param fileName Name des Sourcefiles in dem der Fehler auftrat.
	 * @param lineNr Zeile des Sourcefiles in dem der Fehler auftrat.
	 */
  IOException(const std::string _msg, 
              const std::string fileName, 
              const int lineNr) : Exception(_msg, fileName, lineNr) {
  }

};

#endif // _IOException_h_
