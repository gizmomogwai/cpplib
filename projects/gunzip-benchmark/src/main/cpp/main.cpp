#include <io/ByteArrayOutputStream.h>
#include <io/file/FileInputStream.h>
#include <io/file/FileOutputStream.h>
#include <io/zip/GZIPInputStream.h>
#include <lang/ByteDataBuffer.h>
#include <lang/HPStopWatch.h>
#include <iostream>

static const uint BUFFER_SIZE = 4096*1024;

void copy(InputStream& in, OutputStream& out) {
  auto buffer = ByteDataBuffer(BUFFER_SIZE);
  auto read = in.read(buffer);
  while (read != -1) {
    out.write(&buffer, 0, read);
    read = in.read(buffer);
  }
}

int main(int argc, char** args) {
  HPStopWatch sw;
  sw.start();
  auto fin = FileInputStream("2011.json.gz");
  auto in = GZIPInputStream(&fin, false, BUFFER_SIZE);
  auto out = ByteArrayOutputStream(BUFFER_SIZE);
  copy(in, out);
  std::cout << "CPPLib: Decompressing took " << sw.stop().getDelta() << "ms to " << out.getBytesWritten() << " bytes" << std::endl;
  return 0;
}
