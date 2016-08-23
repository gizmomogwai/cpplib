#pragma once

#include <string>
#include <list>

#include <net/Socket.h>
#include <io/InputStream.h>
#include <io/DataOutputStream.h>
#include <net/http/HTTPResponce.h>

/** Minimalistischer HTTP-Client.
 *
 * Zunaechst muss ein HTTP mit server und port erzeugt werden.
 * Dann muss mit setFile das gewuenschte File selektiert werden.
 * Nun koennen weitere Parameter gesetzt werden.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-12-31, cK, Created.
 *   <li> 2001-02-14, cKtS, get liefert nun InputStream, chunked.
 *   <li> 2001-02-14, cK, setFile eingefuehrt.
 *   <li> 2001-06-15, cKgS, Das oeffnen des Sockets vom Constructor in
 *        das get verlagert, parameters nicht mehr gepointert.
 * </ul>
 *
 * @todo Http-Header caseInsensitive machen
 * @todo Mehr http-parameter unterstuetzen.
 * @todo evtl. mehr http-befehle unterstuetzen.
 *
 * @version $Revision: 1.5 $ $Date: 2001/08/29 11:48:01 $
 *
 * @author cK, $Author: schaefer $
 */
class HTTP {

 public:
  /** Erzeugt eine neue HTTP-Verbindung.
   *
   * @param _host Host, der Kontaktiert werden soll.
   * @param _port Port, auf dem der HTTP-Server laeuft.
   */
  HTTP(std::string _host, int _port);
  
  /** Raeumt auf. */
  virtual ~HTTP();

  /** Schaltet Keep-Alive an.
   */
  virtual void setKeepAlive();

  /** Setzt den Namen des Files, das geholte werden soll.
   *
   * @param resName ResourcenName.
   */
  virtual void setFile(std::string resName);
  
  /** Fuegt den Parametern einen Referrer hinzu.
   *
   * @param referrer Referrer.
   */
  virtual void setReferer(std::string referrer);
  
  /** Fuegt den Parametern eine Range hinzu.
   *
   * @param from von.
   * @param to bis.
   */
  virtual void setRange(long from, long to);

  /** Setzt die Basicauthentisierung.
   *
   * @param userName Name des Benutzers.
   * @param passwd Passwort.
   */
  virtual void setAuthorization(std::string userName, std::string passwd);
  
  /** Stellt eine Anfrage fuer das zuletzt bei setFile gesetzte File an 
   * den HTTP-server und liefert die Ausgabe.
   *
   * @return InputStream Stream zum File.
   */
  virtual InputStream* get() throw (Exception);
  
 private:
  /** Initialisiert den Socket und die Streams vom und zum Server. */
  void init();

  /** Holt den Header des Files, das zuletzt bei setFile gesetzt wurde.
   */
  void getHeader();
   
  /** Hostname. */
  std::string host;
  
  /** Port. */
  int port;

  /** ResourcenName. */
  std::string resName;

	/** Authentisierungsstring. */
  std::string* authLine;
  
  /** Parameterliste, die zusaetzlichge parameter aufnimmt ...
	 * eigentlich koennte man da alles reinschreiben.
	 */
  std::list<std::string> parameters;
  
  /** Zur Kommunikation verwendeter Socket. */
  Socket* s;
  
  /** Datenstrom vom Server. */
  InputStream* fromServer;
  
  /** Datenstrom zum Server. */
  DataOutputStream* toServer;
  
  /** Antwort vom Server. */
  HTTPResponce* responce;
  
};
