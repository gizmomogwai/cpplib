#pragma once

#include <io/OutputStream.h>
#include <lang/DataBuffer.h>
#include <lang/Exception.h>

/** Gefilterter OutputStream.
 *
 * Es wird ein Stream untergeschoben. Die Defaultimplementierungen
 * der Methoden liefert die Werte des unterliegenden Stroms, man
 * kann diese jedoch auch ueberschreiben.
 *
 * Der gewrappte stream koennte nur ueber Getter/Setter 
 * angesprochen werden, der direktere Weg fuer unterklassen ist aber 
 * auch nicht schlechter.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-12-06, cK, Created.
 *   <li> 2001-02-07, cK, flush implementiert.
 * </ul>
 *
 * @version $Revision: 1.2 $, $Date: 2001/07/05 13:27:22 $
 *
 * @author cK, $Author: koestlin $
 */
class FilterOutputStream : public OutputStream {

 public:
	/** Erzeugt einen neuen FilterOutputStream auf einem zugrundeliegenden
	 * OutputStream. 
	 *
	 * @param _out OutputStream.
	 * @param _handleStream wird hier true angegeben wird die Verwaltung des
	 *    zugrundeliegende Streams uebernommen.
   *
   * @exception Exception falls _out 0 ist.
	 */
	FilterOutputStream(OutputStream* _out, bool _handleStream) throw (Exception);

	/** Raeumt auf. Der unterliegende Strom wird gegebenenfalls geschlossen.
   */
  virtual ~FilterOutputStream();

	void write(int v) throw (IOException);

	void write(DataBuffer* b, int offset, int length) throw (IOException);

  void flush() throw (IOException);

 protected:
	/** Unterliegender Strom. */
	OutputStream* out;

	/** Soll der Strom von FilterOutputStream verwaltet werden. */
	bool handleStream;

};
