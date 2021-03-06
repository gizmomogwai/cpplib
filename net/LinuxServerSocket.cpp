#include <net/ServerSocket.h>

#include <lang/Exception.h>

#include <memory.h> // memset
#include <string>

#include <lang/SysError.h>

ServerSocket::ServerSocket(int port) throw(Exception) {
  serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (serverSocket == -1) {
    SysError::throwDetailedException("creating socket");
  }

  sockaddr_in serverSocketAddr;
  serverSocketAddr.sin_family = AF_INET;
  serverSocketAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serverSocketAddr.sin_port = htons(port);
  memset(&(serverSocketAddr.sin_zero), 0, 8);

  int enable = 1;
  int res = setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
  if (res == -1) {
    SysError::throwDetailedException("setting so_reuseaddr");
  }

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
  std::cout << "ServerSocket::~ServerSocket .... aufraeumen ... "
            << "z.b. serversocket schliessen etc...." << std::endl;
  int res = close(serverSocket);
  if (res == -1) {
    SysError::throwDetailedException("ServerSocket::~ServerSocket()");
  }
}

Socket* ServerSocket::accept() {
  sockaddr_in remoteAddr;
  socklen_t addrSize = sizeof(sockaddr_in);
  int acceptedSOCKET =
      ::accept(serverSocket, (sockaddr*)(&remoteAddr), &addrSize);
  if (acceptedSOCKET == -1) {
    SysError::throwDetailedException("accepting");
  }

  std::cout << "Accepted connection from " << inet_ntoa(remoteAddr.sin_addr)
            << ":" << ntohs(remoteAddr.sin_port) << "." << std::endl;

  return new Socket(acceptedSOCKET, inet_ntoa(remoteAddr.sin_addr),
                    ntohs(remoteAddr.sin_port));
}
