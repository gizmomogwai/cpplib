#include <io/SeekableInputStream.h>

#include <io/ByteArrayOutputStream.h>
#include <io/IOTools.h>
#include <lang/DataBuffer.h>

#include <string.h>
#include <util/profile/ProfileObject.h>

int SeekableInputStream::STREAM_BEGIN = 0;
int SeekableInputStream::STREAM_RELATIVE = 0;
int SeekableInputStream::STREAM_END = 0;

SeekableInputStream::SeekableInputStream(InputStream* _in, int initialSize,
                                         bool _handleStream)
    : FilterInputStream(_in, _handleStream), pos(0) {

  helpStream = new ByteArrayOutputStream(initialSize);

  ProfileObject* profile = new ProfileObject("SeekableInputStream::IOTools");
  IOTools::copy(in, helpStream, 4096);
  delete (profile);

  data = &helpStream->getData();
}

SeekableInputStream::~SeekableInputStream() { delete (helpStream); }

int SeekableInputStream::read() throw(IOException) {
  if (pos < (helpStream->getBytesWritten())) {
    int res = *((int*)data->getData(pos));
    pos++;
    return (res);
  } else {
    return (-1);
  }
}

int SeekableInputStream::read(DataBuffer& buffer) throw(IOException) {
  return (read(buffer, 0, buffer.getSize()));
}

int SeekableInputStream::read(DataBuffer& targetBuffer, int offset,
                              int length) throw(IOException) {
  /*
    char* target = (char*)targetBuffer->getData(offset);

    int copied = 0;
    for (int i=0; i<length; i++) {
    int red = read();
    if (red == -1) {
    break;
    }
    *target++ = red;
    copied++;
    }

    return(copied);
  */

  unsigned int maxBytes = helpStream->getBytesWritten();
  int toCopy = length;
  if ((pos + length) > maxBytes) {
    toCopy = maxBytes - pos;
  }

  void* targetMem = targetBuffer.getData(offset);
  void* sourceMem = data->getData(pos);

  memcpy(targetMem, sourceMem, toCopy);
  pos += toCopy;

  return (toCopy);
}

int SeekableInputStream::seek(int mode, int offset) {
  if (mode == SeekableInputStream::STREAM_BEGIN) {
    pos = offset;
  } else if (mode == SeekableInputStream::STREAM_RELATIVE) {
    pos += offset;
  } else if (mode == SeekableInputStream::STREAM_END) {
    pos = helpStream->getBytesWritten() - offset;
  } else {
    throw(Exception("so nicht!", __FILE__, __LINE__));
  }
  return (pos);
}
