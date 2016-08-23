#include <io/ByteArrayOutputStream.h>

#include <memory.h>

ByteArrayOutputStream::ByteArrayOutputStream(long _initialSize, bool clear)
    : written(0) {
  output = new ByteDataBuffer(_initialSize);
  if (clear) {
    output->clear();
  }
}

ByteArrayOutputStream::~ByteArrayOutputStream() { delete (output); }

void ByteArrayOutputStream::write(int b) throw(IOException) {
  if (b < 0) {
    throw(IOException("ByteArrayOutputStream::write(int) - das ist nicht nett",
                      __FILE__, __LINE__));
  }

  assertSpace(1);
  char* help = (char*)output->getData();
  help[written] = (char)b;
  written++;
}

void ByteArrayOutputStream::write(DataBuffer* b, int offset,
                                  int length) throw(IOException) {

  if (length < 0) {
    throw(IOException("ByteArrayOutputStream::write(DataBuffer, int, int)",
                      __FILE__, __LINE__));
  }

  assertSpace(length);
  char* helpDst = (char*)(output->getData(written));
  char* helpSrc = (char*)(b->getData(offset));

  memcpy(helpDst, helpSrc, length);
  written += length;
}

void ByteArrayOutputStream::assertSpace(unsigned int size) {
  unsigned int bufferSize = output->getSize();

  // written = 0 size = 1000 bufferSize = 1000 -> ok
  while (written + size > bufferSize) {
    bufferSize *= 2;
    ByteDataBuffer* newOutput = new ByteDataBuffer(bufferSize);

    // daten kopieren
    memcpy(newOutput->getData(), output->getData(), written);

    delete (output);

    output = newOutput;
  }
}

unsigned int ByteArrayOutputStream::getBytesWritten() { return written; }

ByteDataBuffer& ByteArrayOutputStream::getData() { return *output; }
