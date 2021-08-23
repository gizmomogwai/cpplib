#pragma once

#include <io/InputStream.h>
#include <io/DataInputStream.h>
#include <lang/Exception.h>
#include <map>
#include <memory>

/** Nimmt die Antwort eines HTTP-Servers entgegen.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-12-31, cK, Created.
 *   <li> 2001-02-14, cKtS, Chunked Encoding durch getValue unterstuetzt.
 *   <li> 2001-03-31, cK, An linux angepasst.
 *   <li> 2001-08-15, gS, bug: bei isOK() == true wurde auch exception geworfen.
 * </ul>
 *
 *
 * @version $Revision: 1.4 $, $Date: 2001/08/29 11:48:01 $
 *
 * @author cK, $Author: schaefer $
 */
class HTTPResponce {

 public:
	/** Liesst die Antwort vom Server aus. 
	 *
	 * @param in Daten vom Server.
	 */
	HTTPResponce(InputStream* _in) throw (Exception);
    
	/** Raeumt auf. */
	virtual ~HTTPResponce();  

	/** Liesst die Parameter des Headers ein.
	 */
	virtual void readHeader() throw (Exception);

	/** Liefert die Anzahl von Byte, die der Server
	 * laut HTTP-Response bereitstellt.
	 *
	 * @return long Anzahl von zu uebertragenden byte.
	 */
	virtual long getTransferVolume() {
		return(transferVolume);
	}


  /** Liefert einen Value zu einem Key, oder 0, falls das Feld 
   * im Header nicht vorkommt.
   *
   * @param key Schluessel.
   * 
   * @return std::string* string oder 0 (muss vom caller befreit werden).
   */
  virtual std::string* getValue(std::string key);

 private:
	/** Datenquelle. */
	DataInputStream* in;

	/** Header der Antwort. */
	std::map<std::string, std::string>* header;

	/** Groesse der zu uebertragenden Daten. */
	long transferVolume;
    
};


/** Kleine Hilfsklasse, die die erste Zeile einer Serverantwort untersucht.
 *
 * Es wird nur eine HTTP/1.1 antwort akzeptiert.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-12-31, cK, Created.
 * </ul>
 *
 * @version $Revsion$, $Date: 2001/08/29 11:48:01 $
 *
 * @author cK, $Author: schaefer $
 */
class FirstHTTPLine {
 public:
  /** Parst die erste Zeile einer Server-antwort.
   *
   * @param in Datenquelle.
   *
   * @exception Exception falls nicht das richtige protokoll.
   */
  FirstHTTPLine(DataInputStream* in) throw (Exception);
  
  /** Raeumt auf. */
  virtual ~FirstHTTPLine();
  
  /** Testet, ob die Antwort positiv war. 
   *
   * @return true falls die Antwort positiv ist.
   */
  bool isOK();
  
  /** Liefert die genaue antwort. 
   *
   * @return std::string antwort vom http-server.
   */
  std::string getAnswer();
  
 private:
  /** String vom server. */
  std::unique_ptr<std::string> line;
  
  /** HTTP-ergebniscode. */
  int result;
  
};
