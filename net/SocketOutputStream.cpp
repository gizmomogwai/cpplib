#include <lang/Exception.h>

#include <net/Socket.h>
#include <net/SocketOutputStream.h>

#include <lang/DataBuffer.h>

#include <iostream>

#if defined(WIN32)
#include <winsock2.h>
#endif

SocketOutputStream::SocketOutputStream(Socket* s) { SocketOutputStream::s = s; }

SocketOutputStream::~SocketOutputStream() { s->shutdownOutput(); }

void SocketOutputStream::write(int b) throw(IOException) {

  char buffer[1];
  buffer[0] = (char)b;
  int res = send(s->theSocket, buffer, 1, 0);

#if defined(WIN32)
  if (res == SOCKET_ERROR) {
#elif defined(LINUX) || defined(OSX)
  if (res == -1) {
#else
#error "gefahr"
#endif
    throw(Exception("SocketOutputStream::write(int) -- error while sending",
                    __FILE__, __LINE__));
  }
}

void SocketOutputStream::write(DataBuffer* b, int offset,
                               int length) throw(IOException) {

  char* help = (char*)(b->getData(offset));
  int res = send(s->theSocket, help, length, 0);
#if defined(WIN32)
  if (res == SOCKET_ERROR) {
#elif defined(LINUX) || defined(OSX)
  if (res == -1) {
#else
#error "so nicht"
#endif
    throw(Exception(
        "SocketOutoutStream::write(DataBuffer, int, int) - error while sending",
        __FILE__, __LINE__));
  }
}
