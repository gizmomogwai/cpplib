#include <lang/DataBuffer.h>

#include <assert.h>
#include <iostream>

#include <string.h>

DataBuffer::DataBuffer(void* _data, int _length, bool _ownMem) {
  setData(_data, _length, _ownMem);
}

DataBuffer::~DataBuffer() {
}

void DataBuffer::setData(void* _data, int _length, bool _ownMem) {
  data = _data;
  length = _length;
  ownMem = _ownMem;
}

void* DataBuffer::getData() throw (Exception) {
  if (data == 0) {
    throw Exception("DataBuffer::getData() - data not set", 
                    __FILE__, __LINE__);
  }
  return data;
}

void* DataBuffer::getData(unsigned int offset) throw (Exception) {
  if (offset >= length) { // eignetlich >=
    throw Exception("DataBuffer::getData(int) - out of range", 
                    __FILE__, __LINE__);
  }
  unsigned char* help = (unsigned char*)getData();
  help += offset;

  return help;
}

unsigned int DataBuffer::getSize() {
  return length;
}

void DataBuffer::clear() {
  memset(getData(), 0, getSize());
  //	char* help = (char*)getData();
  //	for (int i=0; i<getSize(); i++) {
  //		*help++ = 0;
  //	}
}
