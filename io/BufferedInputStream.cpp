#include <io/BufferedInputStream.h>

#include <io/InputStream.h>
#include <iostream>
#include <lang/ByteDataBuffer.h>
#include <lang/DataBuffer.h>
#include <math.h>
#include <string.h>

BufferedInputStream::BufferedInputStream(InputStream* _in, bool _handleStream,
                                         int _bufferSize)
    : FilterInputStream(_in, _handleStream), buffer(0), red(0), sourceData(0) {
  buffer = new ByteDataBuffer(_bufferSize);
}

BufferedInputStream::~BufferedInputStream() { delete (buffer); }

int BufferedInputStream::read() throw(IOException) {
  if (red == 0) {
    red = in->read(*buffer);
    sourceData = (unsigned char*)buffer->getData();
  }

  if (red > 0) {

    int res = *sourceData;
    sourceData++;
    red--;
    return (res);
  }

  return (-1);
}

int BufferedInputStream::read(DataBuffer& _targetBuffer, int _offset,
                              int _length) throw(IOException) {

  if (red == 0) {
    red = in->read(*buffer);
    sourceData = (unsigned char*)(buffer->getData());
  }

  if (red > 0) {
    unsigned char* _target = (unsigned char*)(_targetBuffer.getData(_offset));

    int toCopy = (red < _length) ? red : _length;

    memcpy(_target, sourceData, toCopy);
    red -= toCopy;
    sourceData += toCopy;

    return (toCopy);
  }
  return -1;
}
