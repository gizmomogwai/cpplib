#include <io/DataInputStream.h>

#include <lang/DataBuffer.h>

#include <assert.h>

#include <sstream>

DataInputStream::DataInputStream(InputStream* _in, bool _handleStream)

    : FilterInputStream(_in, _handleStream) {

  assert(in);

  handleStream = _handleStream;
}

DataInputStream::~DataInputStream() {}

bool DataInputStream::readBoolean() throw(IOException) {

  int h = in->read();

  if (h == -1) {

    throw(IOException("End Of File In DataInputStream::readBoolean",

                      __FILE__, __LINE__));
  }

  return (h != 0);
}

unsigned char DataInputStream::readByte() throw(IOException) {

  int h = in->read();

  if (h == -1) {

    throw(IOException("End Of File In DataInputStream::readByte",

                      __FILE__, __LINE__));
  }

  return ((unsigned char)h);
}

char DataInputStream::readChar() throw(IOException) {

  int h = in->read();

  if (h == -1) {

    throw(IOException("End Of File In DataInputStream::readByte",

                      __FILE__, __LINE__));
  }

  return ((char)h);
}

int DataInputStream::readInt() throw(IOException) {

  int a = in->read();

  int b = in->read();

  int c = in->read();

  int d = in->read();

  if ((a < 0) || (b < 0) || (c < 0) || (d < 0)) {

    throw(IOException("End Of File In DataInputStream::readInt",

                      __FILE__, __LINE__));
  }

  int res = ((a & 0xff) << 24) | ((b & 0xff) << 16) |

            ((c & 0xff) << 8) | ((d & 0xff));

  return (res);
}

void DataInputStream::readInts(int* data, int nOfInts) throw(IOException) {

  int length = nOfInts * sizeof(int);

  DataBuffer helpBuffer(data, length, false);

  int count = in->readFully(helpBuffer);

  if (count != length) {

    throw(IOException("DataInputStream::readInts - nicht genug daten",

                      __FILE__, __LINE__));
  }

  convert32bitValues((void*)data, nOfInts);
}

double DataInputStream::readDouble() throw(IOException) {

  int i[2];

  i[1] = readInt();

  i[0] = readInt();

  double res = *((double*)i);

  return (res);
}

float DataInputStream::readFloat() throw(IOException) {

  int help = readInt();

  float res = *((float*)(&help));

  return (res);
}

void DataInputStream::readFloats(float* data,
                                 int nOfFloats) throw(IOException) {

  int length = nOfFloats * sizeof(float);

  DataBuffer helpBuffer(data, length, false);

  int count = in->readFully(helpBuffer);

  if (count != length) {

    throw(IOException("DataInputStream::readFloats - nicht genug daten",

                      __FILE__, __LINE__));
  }

  convert32bitValues((void*)data, nOfFloats);
}

short int DataInputStream::readShort() throw(IOException) {

  int h1 = in->read();

  int h2 = in->read();

  if ((h1 < 0) || (h2 < 0)) {

    throw(IOException("DataInputStream::readShort() - End of file",

                      __FILE__, __LINE__));
  }

  return ((short int)((h1 << 8) | (h2 & 0xff)));
}

void DataInputStream::readShorts(short* data,
                                 int nOfShorts) throw(IOException) {

  int length = nOfShorts * sizeof(short);

  DataBuffer helpBuffer(data, length, false);

  int count = in->readFully(helpBuffer);

  if (count != length) {

    throw(IOException("DataInputStream::readShorts - nicht genug daten",

                      __FILE__, __LINE__));
  }

  convert16bitValues((void*)data, nOfShorts);
}

unsigned short int DataInputStream::readUnsignedShort() throw(IOException) {

  return ((unsigned short int)readShort());
}

std::auto_ptr<std::string> DataInputStream::readLine() throw(IOException) {

  int dataRed = 0;

  int b = in->read();

  if ((b != -1) && (b != '\r')) {

    dataRed++;
  }

  std::ostringstream help;

  while ((b != -1) && (b != '\n')) {

    if (b != '\r') {

      help << (char)(b);
    }

    b = in->read();

    if (b != '\r') {

      dataRed++;
    }
  }

  //  help << std::ends;

  if (dataRed == 0) {

    return std::auto_ptr<std::string>(0);
  }

  return std::auto_ptr<std::string>(new std::string(help.str()));
}

char* DataInputStream::readUTF() throw(IOException) {

  unsigned short stringLength = readUnsignedShort();

  char* res = 0;

  if (stringLength > 0) {

    res = new char[stringLength + 1];

    for (int i = 0; i < stringLength; i++) {

      res[i] = readChar();
    }

    res[stringLength] = '\0';
  }

  return (res);
}

std::string DataInputStream::readUTFString() throw(IOException) {

  char* help = readUTF();
  if (help == 0) {
    throw(IOException("DataInputStream::readUTFString() - readUTF", __FILE__,
                      __LINE__));
  }

  std::string res(help);

  delete[](help);

  return (res);
}
