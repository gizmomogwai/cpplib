#ifndef _WIN32WinSockWrapper_h_
#define _WIN32WinSockWrapper_h_

#ifdef WIN32
#ifdef _AFX
  #include <afx.h>
  #include <winsock2.h>
#endif
// tricky! afx muss vor winsock2 an den start gehen, da sonst windows.h
// includiert wird.
// winsock2 muss vor windows.h an den start gehen, damit von windows.h nicht
// winsock.h includiert wird!
#ifdef _COMMAND
  #include <winsock2.h>
  #include <windows.h>
#endif
#include <lang/Mutex.h>

/** Wrappt die WinSock-Initialisierungen in einem Singleton.
 *
 * Vor Verwendung der WinSock-Methoden muss 
 * WinSockWrapper::getInstance()->init
 * aufgerufen werden. Falls das der erste aufruf ist, wird WSAStartup
 * aufgerufen. 
 *
 * Am Ende einer Socketverwendung muss 
 * WinSockWrapper::getIntance()->deinit aufgerufen werden.
 *
 * Es wird mit einem refCount mitgezaehlt, wenn dieser 
 * auf 0 sinkt, wird WSACleanup aufgerufen.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-11-20, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.1.1.1 $, $Date: 2001/04/27 14:10:32 $
 *
 * @author cK, $Author: koestlin $
 */
class WinSockWrapper : public Mutex {

 public:

	/** Initialisiert die WinSock-Schicht. */
	static void init();

	/** Deinitialisiert die WinSock-Schicht. */
	static void deinit();

 private:

  /** Erzeugt einen neuen WinSockWrapper. */
	WinSockWrapper();

  /** Raeumt auf wsacleanup. */
  ~WinSockWrapper();

	/** Referenzcount. */
	static int refCount;

  /** Lock. */
  static Mutex m;

};

#endif //WIN32

#endif // _WIN32WinSockWrapper_h_
