#include <io/zip/CheckedInputStream.h>


CheckedInputStream::CheckedInputStream(InputStream* _in, 
				       bool _handleStream, 
				       Checksum* _check) 
  : FilterInputStream(_in, _handleStream) {
  
  check = _check;
}

CheckedInputStream::~CheckedInputStream() {
}

int CheckedInputStream::read() 
  throw (IOException) {

//  int res = FilterInputStream::read();
  int res = in->read();
  if (res != -1) {
    check->update(res);
  }
  return(res);
}

int CheckedInputStream::read(DataBuffer& b, int offset, int length) 
  throw (IOException) {
  
//  int res = FilterInputStream::read(b, offset, length);
  int res = in->read(b, offset, length);
  if (res != -1) {
    check->update(&b, offset, res);
  }
  return(res);
}

unsigned long CheckedInputStream::getChecksum() {
  return(check->getChecksum());	
}
