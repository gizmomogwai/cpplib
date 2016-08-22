#ifdef LINUX

#include <net/ServerSocket.h>

#include <lang/Exception.h>

#include <memory.h> // memset
#include <string>

#include <lang/SysError.h>


ServerSocket::ServerSocket(int port) throw (Exception) {

  serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (serverSocket == -1) {
    SysError::throwDetailedException("creating socket");
  }
  int res = 0;

  sockaddr_in serverSocketAddr;
  serverSocketAddr.sin_family = AF_INET;
  serverSocketAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serverSocketAddr.sin_port = htons(port);
  memset(&(serverSocketAddr.sin_zero), 0, 8);

  res = bind(serverSocket, (sockaddr*)(&serverSocketAddr), sizeof(sockaddr_in));
  if (res == -1) {
    SysError::throwDetailedException("binding");
  }

  res = listen(serverSocket, SOMAXCONN);
  if (res == -1) {
    SysError::throwDetailedException("listening");
  }

}


ServerSocket::~ServerSocket() {
  std::cout << "ServerSocket::~ServerSocket .... aufraeumen ... " <<
    "z.b. serversocket schliessen etc...." << std::endl;
  int res = close(serverSocket);
  if (res == -1) {
    SysError::throwDetailedException("ServerSocket::~ServerSocket()");
  }
}

Socket* ServerSocket::accept() {
  sockaddr_in remoteAddr;
  socklen_t addrSize = sizeof(sockaddr_in);
  int acceptedSOCKET = ::accept(serverSocket, (sockaddr*)(&remoteAddr), &addrSize);
  if (acceptedSOCKET == -1) {
    SysError::throwDetailedException("accepting");
  }

  std::cout << "Accepted connection from " << inet_ntoa(remoteAddr.sin_addr) <<
    ":" << ntohs(remoteAddr.sin_port) << "." << std::endl;

  std::string remoteHost(inet_ntoa(remoteAddr.sin_addr));
  Socket* res =
    new Socket(acceptedSOCKET, remoteHost, ntohs(remoteAddr.sin_port));
  return(res);
}

#endif // LINUX
