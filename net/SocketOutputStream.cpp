#include <io/IOException.h>

#include <net/Socket.h>
#include <net/SocketOutputStream.h>

#include <lang/DataBuffer.h>

#include <iostream>

SocketOutputStream::SocketOutputStream(Socket* s) : socket(s) {}

SocketOutputStream::~SocketOutputStream() { socket->shutdownOutput(); }

void SocketOutputStream::write(int b) throw(IOException) {
  char buffer[1];
  buffer[0] = (char)b;
  int res = send(socket->theSocket, buffer, 1, MSG_NOSIGNAL);

  if (res == -1) {
    throw IOException("SocketOutputStream::write(int) -- error while sending",
                      __FILE__, __LINE__);
  }
}

void SocketOutputStream::write(DataBuffer* b, int offset,
                               int length) throw(IOException) {

  char* help = (char*)(b->getData(offset));
  int res = send(socket->theSocket, help, length, MSG_NOSIGNAL);
  if (res == -1) {
    throw IOException(
        "SocketOutoutStream::write(DataBuffer, int, int) - error while sending",
        __FILE__, __LINE__);
  }
}
