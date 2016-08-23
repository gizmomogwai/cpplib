#include <io/ByteArrayInputStream.h>

#include <lang/DataBuffer.h>
#include <lang/Exception.h>
#include <string.h>

ByteArrayInputStream::ByteArrayInputStream(DataBuffer* _buffer, int _offset,
                                           int _available) {
  buffer = (unsigned char*)(_buffer->getData(_offset));
  available = _available;
}

ByteArrayInputStream::~ByteArrayInputStream() {}

int ByteArrayInputStream::read() throw(IOException) {
  int res = -1;
  if (available > 0) {
    res = *buffer;
    buffer++;
    available--;
  }
  return res;
}
#include <iostream>
int ByteArrayInputStream::read(DataBuffer& b, int offset,
                               int length) throw(IOException) {

  unsigned char* target = (unsigned char*)(b.getData(offset));
  int max = 0;
  if (length < available) {
    max = length;
  } else {
    max = available;
  }

  // durch mem copy ersetzen
  memcpy(target, buffer, max);
  buffer += max;
  available -= max;

  if (max == 0)
    max = -1;
  return (max);
}
