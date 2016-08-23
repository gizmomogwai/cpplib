#include <io/InputStream.h>

#include <lang/DataBuffer.h>

int InputStream::readFully(DataBuffer& b) throw(IOException) {
  int red = read(b);
  if (red == -1) {
    return (red);
  }
  while (red < b.getSize()) {
    int help = read(b, red, b.getSize() - red);
    if (help != -1) {
      red += help;
    } else {
      return (red);
    }
  }
  return (red);
}

int InputStream::read(DataBuffer& b) throw(IOException) {
  return read(b, 0, b.getSize());
}
