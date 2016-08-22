#include <io/pipe/PipedOutputStream.h>


#include <iostream>

PipedOutputStream::PipedOutputStream(Pipe* _pipe) : pipe(_pipe) {
}

PipedOutputStream::~PipedOutputStream() {
  std::cout << "~PipedOutputStream aufraeumen" << std::endl;
  pipe->deleteOutputStream();
}

void PipedOutputStream::write(int b) throw (IOException) {
  pipe->write((unsigned char)(b &  0xff));
}

void PipedOutputStream::write(DataBuffer* b, int offset, int length) throw (IOException) {

  unsigned char* help = (unsigned char*)(b->getData(offset));
  for (int i=0; i<length; i++) {
    pipe->write(*help++);
  }
}

