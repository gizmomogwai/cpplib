#ifndef _ServerSocket_h_
#define _ServerSocket_h_

// gefaehrlich .. aber socket macht alles was noetig ist???!!!
#include <net/Socket.h>

#include <iostream>

/** ServerSocket.
 *
 * <h3>Linux</h3>
 * Das serversockzeug hier scheint etwas problematisch zu sein ..
 * ich weiss nciht , wie man den serversocket korrekt freigibt
 * bei beenden des serverSocketCheck-programms (auch mit closen etc.
 * kann nicht sofort wieder gebunden werden). Vielleciht sollte man 
 * das ganz mal mit einem c-client verwenden .. evtl. hat man da mehr
 * kontrolle... 
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-11-24, cK, Created.
 * </ul>
 *
 * @todo Auf welche Adresse muss der ServerSocket gebunden werden ... oder
 *       sollte man das  configgen koennen???? momentan INADDR_ANY
 * @todo Was auch nicht so sehr schoen ist, ist das mit dem umschalten ...
 *       momentan hab ich wieder LinuxSocket und WIN32Socket am start ...
 *       ob das aber so gut ist ...
 *
 * @version $Revision: 1.2 $, $Date: 2001/07/05 13:27:23 $
 *
 * @author cK, $Author: koestlin $
 */
class ServerSocket {
  
 public:
  /** Erzeugt einen neuen ServerSocket auf einem Port. 
   *
   * @param port Der Port.
   *
   * @exception Exception falls etwas nicht klappt.
   */
  ServerSocket(int port) throw (Exception);
  
  /** Raeumt auf. **/
  virtual ~ServerSocket();
  
  /** Wartet auf ein connect und liefert den KommunikationsSocket zurueck.
   *
   * @return Socket* gelieferter Socket.
   */
  Socket* accept();
  
 private:
#ifdef WIN32
  /** Wirft einen Exception, der den Fehlercode von WinSock genauer
	 * auswertet.  
   *
   * @param base Basisstring zur fehlerbeschreibung, der um den 
   *        spezifischen WinSockFehler erweitert wird.
   */
  void throwDetailedException(const char* base);

  /** Intern verwendeter Socket, der nach aussen gebunden wird. */
  SOCKET serverSocket;
#endif // WIN32

#ifdef LINUX
  /** Intern verwendeter Socket, der nach aussen gebunden wird. */
  int serverSocket;
#endif // LINUX
  
};


#endif // _ServerSocket_h_
