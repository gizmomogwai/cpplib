#ifdef WIN32
#include <net/ServerSocket.h>

#include <lang/Exception.h>

#include <net/WIN32WinSockWrapper.h>

#include <memory.h> // memset
#include <string>

#ifdef WIN32
  #include <winsock2.h>
#endif

void ServerSocket::throwDetailedException(const char* base) {
  int fuck = WSAGetLastError();
  std::string error(base);
  error += "- ";
  switch (fuck) {
    case WSANOTINITIALISED: 
      error += "winsock not initialised"; break;
    case WSAENETDOWN:
      error += "winsocknetdown"; break;
    case WSAEFAULT:
      error += "winsockefault"; break;
    case WSAEINTR:
      error += "winsockeintr"; break;
    case WSAEINPROGRESS:
      error += "inprogress"; break;
    case WSAEINVAL:
      error += "inval"; break;
    case WSAEMFILE:
      error += "emfile"; break;
    case WSAENOBUFS:
      error += "enobufs"; break;
    case WSAENOTSOCK:
      error += "enotsock"; break;
    case WSAEOPNOTSUPP:
      error += "eopnotsupp"; break;
    case WSAEWOULDBLOCK:
      error += "wouldblock"; break;
    default:
      error += "unknown WinSOckError"; break;
  }
  Exception e(error);
  throw(e);
}

ServerSocket::ServerSocket(int port) {
  
  WinSockWrapper::init();

  serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (serverSocket == INVALID_SOCKET) {
    throwDetailedException("creating socket");
  }
  int res = 0;
  
  sockaddr_in serverSocketAddr;
  serverSocketAddr.sin_family = AF_INET;
  serverSocketAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serverSocketAddr.sin_port = htons(port);
  memset(&(serverSocketAddr.sin_zero), 0, 8);
  
  res = bind(serverSocket, (sockaddr*)(&serverSocketAddr), sizeof(sockaddr_in));
  if (res == SOCKET_ERROR) {
    throwDetailedException("binding");
  }
  
  res = listen(serverSocket, SOMAXCONN);
  if (res == SOCKET_ERROR) {
    throwDetailedException("listening");
  }
  
}


ServerSocket::~ServerSocket() {
  std::cout << "ServerSocket::~ServerSocket .... aufraeumen ... " << 
    "z.b. serversocket schliessen etc...." << std::endl;

  closesocket(serverSocket);
  WinSockWrapper::deinit();
}
		
Socket* ServerSocket::accept() {
  sockaddr_in remoteAddr;
  int addrSize = sizeof(sockaddr_in);
  SOCKET acceptedSOCKET = ::accept(serverSocket, 
                                   (sockaddr*)(&remoteAddr), 
                                   &addrSize);
  if (acceptedSOCKET == INVALID_SOCKET) {
    throwDetailedException("accepting");
  }

  std::cout << "Accepted connection from " << inet_ntoa(remoteAddr.sin_addr) << 
    ":" << ntohs(remoteAddr.sin_port) << "." << std::endl;

  std::string remoteHost(inet_ntoa(remoteAddr.sin_addr));
  Socket* res = 
    new Socket(acceptedSOCKET, remoteHost, ntohs(remoteAddr.sin_port));
  return(res);
}

#endif // WIN32
