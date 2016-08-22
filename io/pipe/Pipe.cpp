#include <io/pipe/Pipe.h>

#include <io/pipe/PipedInputStream.h>
#include <io/pipe/PipedOutputStream.h>
#include <assert.h>
#include <iostream>

Pipe::Pipe(int _bufferSize) 
  : in(0), 
    out(0),
    bufferSize(_bufferSize),     
    buffer(0),    
    nextToRead(0), 
    nextToWrite(0), 
    empty(true) {
  
  buffer = new unsigned char[bufferSize];
  in = new PipedInputStream(this);
  out = new PipedOutputStream(this);
}

Pipe::~Pipe() {

  delete[](buffer);
}

InputStream* Pipe::getInputStream() {

  return(in);
}

OutputStream* Pipe::getOutputStream() {

  return(out);
}

int Pipe::read(unsigned char* byteVal) throw (IOException) {

  bufferLock.lock();

  int res = 0;
  if (empty == true) {
    if (out == 0) {
      res = -1;
    } else {

      bufferLock.wait();
      if (out == 0) {
        res = -1;
      }
    }
  }

  if (res != -1) {
    *byteVal = buffer[nextToRead++];
    if (nextToRead == bufferSize) {
      nextToRead = 0;
    }
    if (nextToRead == nextToWrite) empty = true;
    else empty = false;

    res = 1;

    bufferLock.notify();
  }

  bufferLock.unlock();

  return(res);
}

void Pipe::write(unsigned char value) throw (IOException) {

  bufferLock.lock();

  if (empty == true) {

    writeByteAndSignalReader(value);
  } else {

    if (nextToWrite == nextToRead) {
      
      bufferLock.wait();
    }

    writeByteAndSignalReader(value);
  }

  bufferLock.unlock();

}

void Pipe::writeByteAndSignalReader(unsigned char value) {

    buffer[nextToWrite++] = value;
    if (nextToWrite == bufferSize) {
      nextToWrite = 0;
    }
    empty = false;

    bufferLock.notify();

}

void Pipe::deleteOutputStream() {
  bufferLock.lock();

  out = 0;

  bufferLock.notify();
  
  bufferLock.unlock();
}
