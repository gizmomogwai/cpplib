#include <lang/ByteDataBuffer.h>

#include <string.h>

ByteDataBuffer::ByteDataBuffer(int size)
    : DataBuffer(new unsigned char[size], size, true) {}

ByteDataBuffer::ByteDataBuffer(const unsigned char* data, size_t length)
    : DataBuffer(new unsigned char[length], length, true) {
  memcpy(getData(), static_cast<const void*>(data), length);
}

ByteDataBuffer::~ByteDataBuffer() {
  if (DataBuffer::ownMem == true) {
    delete[]((unsigned char*)getData());
  }
}
