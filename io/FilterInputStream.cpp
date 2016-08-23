#include <io/FilterInputStream.h>

#include <lang/DataBuffer.h>

FilterInputStream::FilterInputStream(InputStream* _in, bool _handleStream) {
  in = _in;
  handleStream = _handleStream;
}

FilterInputStream::~FilterInputStream() {
  if (handleStream == true) {
    if (in != 0) {
      delete (in);
      in = 0;
    }
  }
}

int FilterInputStream::read() throw(IOException) { return (in->read()); }

int FilterInputStream::read(DataBuffer& b, int offset,
                            int length) throw(IOException) {
  return in->read(b, offset, length);
}

int FilterInputStream::read(DataBuffer& b) throw(IOException) {
  return read(b, 0, b.getSize());
}
