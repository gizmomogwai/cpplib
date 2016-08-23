#pragma once

#include <lang/Exception.h>

#include <io/InputStream.h>
#include <io/OutputStream.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>       // gethostbyname
#include <netinet/in.h>  // struct sockaddr_in
#include <unistd.h>      // for close
#include <arpa/inet.h>  // in_ntoa

#include <lang/Exception.h>

class SocketInputStream;
class SocketOutputStream;

/** Socketklasse. Es werden input und outputstreams angeboten, mit denen
 * dann zum Socket geschrieben, von ihm gelesen werden kann.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-05-14, cK, Created.
 *   <li> 2000-12-06, cK, Erweitert um friends und besseres aufraeumen.
 * </ul>
 *
 * @todo muss man auf is und os syncprobleme abfangen ..
 *       oder sollte das nur singlethreaded sein
 * @todo <b>BUG:</b> Auch im Fehlerfall sollte der winsockzaehler am ende
 *       runtergezaehlt werden!
 *
 * @version $Revision: 1.2 $, $Date: 2001/07/05 13:27:23 $
 *
 * @author cK, $Author: koestlin $
 **/
class Socket {
  friend class SocketInputStream;
  friend class SocketOutputStream;

 public:

  /** Stellt eine tcp-verbindung her.
   *
   * @param _address IP-Adresse.
   * @param _port Portnummer.
   *
   * @exception Exception falls der host nicht gefunden werden kann
   *            oder die verbindung nicht hergestellt werden kann.
   */
  Socket(const char* _address, int _port) throw (Exception);

  /** Stellt eine tcp-verbindung her.
   *
   * @param _host Hostname.
   * @parma _port Portnummer.
   *
   * @exception Exception, falls der host nicht gefunden werden kann,
   *            oder ein anders problem auftritt.
   */
  Socket(const std::string& _host, int _port) throw (Exception);

  /** Initialisiert den Socket mit einem verbundenen SOCKET.
   *
   * @param _theSocket linux socket
   * @param _hostName HostName
   * @param port Port.
   */
  Socket(int _theSocket, std::string _hostName, int port) throw (Exception);

  /** Baut die Verbindung ab.
   *
   * Evtl. erzeugt Input oder Outputstroeme werden auch zerstzoehrt.
   */
  virtual ~Socket();

  /** Liefert den Strom vom Socket. Ein Socket kann nur einen InputStream
   * haben.
   *
   * Der gelieferte Strom wird vom Socket im Deconstructor zerstoehrt.
   * Kann aber nach belieben auch schon vorher zerstoehrt werden.
   *
   * @return InputStream Datenstrom.
   *
   * @exception Exception falls der strom schon geschlossen ist.
   */
  InputStream& getInputStream() throw (Exception);

  /** Liefert den OutputStream zum Socket hinaus. Ein Socket kann nur einen
   * OutputStream haben.
   *
   * Der gelieferte Strom wird vom Socket im Deconstructor zerstoehrt.
   * Kann aber auch von extern zerstoeht werden.
   *
   * @return OutputStream Datenstrom.
   *
   * @exception Exception falls der Strom schon zerstoehrt ist.
   */
  OutputStream& getOutputStream() throw (Exception);

 private:
  /** Initialisiert die Verbindung.
   *
   * @param _remoteHost Hostname.
   * @param _port Portnummer.
   *
   * @exception Exception falls etwas schiefgeht.
   */
  void init() throw (Exception);

  /** Disables receive auf dem Socket. */
  void shutdownInput();

  /** Disables send auf dem Socket. */
  void shutdownOutput();

  /** Erzeugt den Input und den OutputStream. */
  void createStreams();

  /** Inputstream der zum lesen vom Socket verwendet wird. */
  InputStream* is;

  /** Outputstream der zum schreiben in den Socket verwendet wird. */
  OutputStream* os;

  /** Speichert sich den Remote-Hostnamen und verwaltet diesen String auch. */
  std::string hostName;

  /** Der zugrundeliegende Socket. */
  int theSocket;

  /** Speichert den Port der Remote-verbindung. */
  int port;
};
