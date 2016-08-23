#ifdef WIN32

#include <lang/Exception.h>

#include <net/Socket.h>

#include <io/InputStream.h>
#include <io/OutputStream.h>

#include <net/SocketInputStream.h>
#include <net/SocketOutputStream.h>

#ifdef WIN32
#ifdef _AFX
#include <afx.h>
#include <winsock2.h>
#endif
#ifdef _COMMAND
#include <windows.h>
#include <winsock2.h>
#endif
#include <net/WIN32WinSockWrapper.h>
#endif // WIN32

Socket::Socket(std::string _remoteHost, int _port) throw(Exception) {
  init(_remoteHost.c_str(), _port);
}

Socket::Socket(const char* _remoteHost, int _port) throw(Exception) {
  init(_remoteHost, _port);
}

void Socket::init(const char* _remoteHost, int _port) throw(Exception) {

  is = 0;
  os = 0;

#ifdef WIN32
  WinSockWrapper::init();
#endif // WIN 32

  unsigned long iAddr = inet_addr(_remoteHost);
  hostent* host;
  u_long nRemoteAddr;
  if (iAddr == INADDR_NONE) {

    // try name
    host = ::gethostbyname(_remoteHost);

    // fraglich ob das so korrekt ist ???????????????
    if (host == 0) {

      throw(Exception("unknown Host", __FILE__, __LINE__));
    }

    nRemoteAddr = *((u_long*)host->h_addr_list[0]);

  } else {

    nRemoteAddr = iAddr;

    /*
    // is ipaddress
    struct in_addr help;
    help.s_addr = iAddr;
    host = ::gethostbyaddr((const char*)&help, sizeof(struct in_addr), AF_INET);
    */
  }

  /*
  if (host == NULL) {
    throw(Exception("Unknown Host", __FILE__, __LINE__));
  }*/

  // baue socket
  theSocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (theSocket == INVALID_SOCKET) {
    throw(Exception("Could not create socket", __FILE__, __LINE__));
  }

  // initialisiere socket mit dem port und dem restlichen zeug
  sockaddr_in sinRemote;
  sinRemote.sin_family = AF_INET;
  sinRemote.sin_addr.s_addr = nRemoteAddr;
  sinRemote.sin_port = htons(_port);

  // connect
  int res = ::connect(theSocket, (sockaddr*)&sinRemote, sizeof(sockaddr_in));
  if (res == SOCKET_ERROR) {
    throw(Exception("could not connect", __FILE__, __LINE__));
  }

  hostName = std::string(_remoteHost);
  port = _port;

  createStreams();
}

Socket::Socket(SOCKET _theSocket, std::string _hostName, int _port) {

  is = 0;
  os = 0;
#ifdef WIN32
  WinSockWrapper::init();
#endif // WIN32

  theSocket = _theSocket;
  hostName = _hostName;
  port = _port;

  createStreams();
}

void Socket::shutdownInput() {
  if (shutdown(theSocket, SD_RECEIVE) == SOCKET_ERROR) {
    throw(
        Exception("Socket::~Socket end send not possible", __FILE__, __LINE__));
  }
  is = 0;
}

void Socket::shutdownOutput() {
  if (shutdown(theSocket, SD_SEND) == SOCKET_ERROR) {
    throw(
        Exception("Socket::~Socket end send not possible", __FILE__, __LINE__));
  }
  os = 0;
}

Socket::~Socket() {

  if (os != 0) {
    delete (os);
    os = 0;
  }

  if (is != 0) {
    delete (is);
    is = 0;
  }

  if (closesocket(theSocket) == SOCKET_ERROR) {
    throw(Exception("Socket::~Socket - could not close socket", __FILE__,
                    __LINE__));
  }

#ifdef WIN32
  WinSockWrapper::deinit();
#endif // WIN32
}

void Socket::createStreams() {
  if (is == 0) {
    is = new SocketInputStream(this);
  }
  if (os == 0) {
    os = new SocketOutputStream(this);
  }
}

InputStream* Socket::getInputStream() throw(Exception) {
  if (is == NULL) {
    throw(Exception("Socket::getInputStream - InputStream already closed",
                    __FILE__, __LINE__));
  }
  return (is);
}

OutputStream* Socket::getOutputStream() throw(Exception) {
  if (os == NULL) {
    throw(Exception("Socket::getOutputStream - OutputStream already closed",
                    __FILE__, __LINE__));
  }
  return (os);
}

#endif // WIN32
