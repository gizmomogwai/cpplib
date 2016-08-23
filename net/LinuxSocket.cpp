#include <lang/Exception.h>

#include <net/Socket.h>

#include <io/InputStream.h>
#include <io/OutputStream.h>

#include <lang/SysError.h>
#include <net/SocketInputStream.h>
#include <net/SocketOutputStream.h>

Socket::Socket(const std::string& host, int _port) throw(Exception)
    : hostName(host), port(_port) {
  init();
}

Socket::Socket(const char* host, int _port) throw(Exception)
    : hostName(host), port(_port) {
  init();
}

class AddrInfo {
public:
  AddrInfo(const std::string& host) : fInfo(0) {
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = PF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(host.c_str(), "20000", &hints, &fInfo) != 0) {
      throw Exception("getaddrinfo failed");
    }
  }

  int connectToFirst() {
    if (fInfo == 0) {
      throw Exception("host not found");
    }

    int theSocket =
        socket(fInfo->ai_family, fInfo->ai_socktype, fInfo->ai_protocol);
    if (theSocket == -1) {
      throw Exception("could not create socket", __FILE__, __LINE__);
    }
    if (connect(theSocket, fInfo->ai_addr, fInfo->ai_addrlen) != 0) {
      close(theSocket);
      throw Exception("could not connect", __FILE__, __LINE__);
    }
    return theSocket;
  }

  ~AddrInfo() { freeaddrinfo(fInfo); }

private:
  struct addrinfo* fInfo;
};

void Socket::init() throw(Exception) {
  is = 0;
  os = 0;

  AddrInfo info(hostName);
  /*
  hostent* host;
  unsigned long iAddr = inet_addr(hostName.c_str());
  if (iAddr == INADDR_NONE) {
    // try name
    std::cout << "name " << std::endl;
    host = ::gethostbyname(hostName.c_str());
  } else {
    std::cout << "ip" << std::endl;
    // is ipaddress
    struct in_addr help;
    if (!inet_aton(hostName.c_str(), &help)) {
      throw Exception("could not parse ip");
    }
    host = ::gethostbyaddr(&help, sizeof(struct in_addr), AF_INET);
  }
  if (host == NULL) {
    std::cout << hstrerror(h_errno);
    throw Exception("Unknown Host", __FILE__, __LINE__);
  }


  u_long nRemoteAddr = *((u_long*)host->h_addr_list[0]);

  // baue socket
  theSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (theSocket == -1) {
    SysError::throwDetailedException("could not create socket");
  }

  // initialisiere socket mit dem port und dem restlichen zeug
  sockaddr_in sinRemote;
  sinRemote.sin_family = AF_INET;
  sinRemote.sin_addr.s_addr = nRemoteAddr;
  std::cout << port << std::endl;
  sinRemote.sin_port = htons(port);

  // connect
*/
  theSocket = info.connectToFirst();
  createStreams();
}

Socket::Socket(int _theSocket, std::string _hostName,
               int _port) throw(Exception)
    : is(0), os(0), hostName(_hostName), theSocket(_theSocket), port(_port) {
  createStreams();
}

#include <iostream>
void Socket::shutdownInput() {
  if (shutdown(theSocket, SHUT_RD) == -1) {
    std::cout << "shutdown input hat nicht gefunkt" << std::endl;
    //    SysError::throwDetailedException("Socket::shutdownInput");
  }
  is = 0;
}

void Socket::shutdownOutput() {
  if (shutdown(theSocket, SHUT_WR) == -1) {
    std::cout << "shutdown output hat nicht gefunkt" << std::endl;
    // SysError::throw(Exception("Socket::shutdownOutput end send not
    // possible"));
  }
  os = 0;
}

Socket::~Socket() {
  if (os != 0) {
    delete os;
    os = 0;
  }

  if (is != 0) {
    delete is;
    is = 0;
  }

  if (close(theSocket) == -1) {
    SysError::throwDetailedException("Socket::~Socket - could not close");
  }
}

void Socket::createStreams() {
  // disable sigpipe, otherwise a server gets the signal if a client disconnects
  const int set = 1;
  setsockopt(theSocket, SOL_SOCKET, SO_NOSIGPIPE, &set, sizeof(set));

  if (is == 0) {
    is = new SocketInputStream(this);
  }
  if (os == 0) {
    os = new SocketOutputStream(this);
  }
}

InputStream& Socket::getInputStream() throw(Exception) {
  if (is == 0) {
    throw Exception("Socket::getInputStream - InputStream already closed",
                    __FILE__, __LINE__);
  }
  return *is;
}

OutputStream& Socket::getOutputStream() throw(Exception) {
  if (os == 0) {
    throw Exception("Socket::getOutputStream - OutputStream already closed",
                    __FILE__, __LINE__);
  }
  return *os;
}
