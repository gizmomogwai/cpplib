#include <io/DataOutputStream.h>

DataOutputStream::DataOutputStream(OutputStream* _out, bool _handleStream)
  : FilterOutputStream(_out, _handleStream) {
}

DataOutputStream::~DataOutputStream() {
}

void DataOutputStream::writeBoolean(bool v) throw (IOException) {
  if (v == true) {
    out->write(1);
  } else {
    out->write(0);
  }
}

void DataOutputStream::writeByte(unsigned char v) throw (IOException) {
  out->write((int)v);
}

void DataOutputStream::writeBytes(unsigned char* data, int nOfBytes) throw (IOException) {
  for (int i=0; i<nOfBytes; i++) {
    writeByte(*data++);
  }
}


void DataOutputStream::writeInt(int v) throw (IOException) {
  int a = (v >> 24) & 0xff;
  int b = (v >> 16) & 0xff;
  int c = (v >> 8) & 0xff;
  int d = (v     ) & 0xff;

  out->write(a);
  out->write(b);
  out->write(c);
  out->write(d);
}

void DataOutputStream::writeInts(int* data, int nOfInts) throw (IOException) {
  for (int i=0; i<nOfInts; i++) {
    writeInt(*data++);
  }
}

void DataOutputStream::writeShort(short v) throw (IOException) {
  int a = (v >> 8) & 0xff;
  int b = (v     ) & 0xff;

  out->write(a);
  out->write(b);
}

void DataOutputStream::writeShorts(short* data, int nOfShorts) throw (IOException) {
  for (int i=0; i<nOfShorts; i++) {
    writeShort(*data++);
  }
}


void DataOutputStream::writeUnsignedShort(unsigned short v) throw (IOException) {
  writeShort((short)v);
}

void DataOutputStream::writeUnsignedShorts(unsigned short* data,
                                           int nOfUnsignedShorts) throw (IOException) {
  writeShorts((short*)data, nOfUnsignedShorts);
}

void DataOutputStream::writeDouble(double d) throw (IOException) {
  int* i = (int*)(&d);
  writeInt(i[1]);
  writeInt(i[0]);
}

void DataOutputStream::writeDoubles(double* data,
                                    int nOfDoubles) throw (IOException) {
  for (int i=0; i<nOfDoubles; i++) {
    writeDouble(*data++);
  }
}


void DataOutputStream::writeFloat(float f) throw (IOException) {
  int* i = (int*)(&f);
  writeInt(*i);
}

void DataOutputStream::writeFloats(float* data,
                                   int nOfFloats) throw (IOException) {
  for (int i=0; i<nOfFloats; i++) {
    writeFloat(*data++);
  }
}

void DataOutputStream::writeString(std::string* s) throw (IOException) {
  DataBuffer b((void*)s->c_str(), s->length(), false);
  write(&b, 0, b.getSize());
}

void DataOutputStream::writeLine() throw (IOException) {
  write('\n');
}

void DataOutputStream::writeUTFString(std::string* str) throw (IOException) {
  unsigned short length = (unsigned short)str->length();
  writeUnsignedShort(length);
  DataBuffer buffer((void*)str->c_str(), length, false);
  write(&buffer, 0, length);
}
