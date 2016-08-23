#include <net/Socket.h>
#include <net/SocketInputStream.h>

#if defined(WIN32)
#include <winsock2.h>
#elif defined(LINUX) || defined(OSX)
#include <sys/socket.h>
#include <sys/types.h>
#else
#error "problems ahead"
#endif

#include <iostream>

SocketInputStream::SocketInputStream(Socket* _s) { s = _s; }

SocketInputStream::~SocketInputStream() {
  /*
    int red = read();
    while (red != -1) {
    red = read();
    }
  */
  s->shutdownInput();
}

int SocketInputStream::read() throw(IOException) {
  char buffer[1];
  int newBytes = ::recv(s->theSocket, buffer, 1, 0);
  if (newBytes == 0) {
    return -1;
  } else if (newBytes == -1) {
    throw IOException("socket error");
  } else {
    return (int)(buffer[0] & 0xff);
  }
}

int SocketInputStream::read(DataBuffer& _targetBuffer, int _targetOffset,
                            int _targetLength) throw(IOException) {

  char* help = (char*)(_targetBuffer.getData(_targetOffset));
  int newBytes = ::recv(s->theSocket, help, _targetLength, 0);
  if (newBytes == 0) {
    newBytes = -1;
  } else if (newBytes == -1) {
    throw IOException("socket error");
  }
  return newBytes;
}
