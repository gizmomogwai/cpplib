#include <io/pipe/PipedInputStream.h>

#include <iostream>

PipedInputStream::PipedInputStream(Pipe* _pipe) : pipe(_pipe) {
}

PipedInputStream::~PipedInputStream() {
  std::cout << "~PipedInputStream aufraument" << std::endl;
}

int PipedInputStream::read() throw (IOException) {

  unsigned char help;
  int res = pipe->read(&help);

  if (res == -1) {
    return(res);
  } else {
    return(help);
  }
}

int PipedInputStream::read(DataBuffer& target, int offset, int length) 
  throw (IOException) {

  return(pipe->read((unsigned char*)target.getData(offset)));
}
