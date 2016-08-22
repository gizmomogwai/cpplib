#include <io/FilterOutputStream.h>
#include <lang/DataBuffer.h>

#include <iostream>

FilterOutputStream::FilterOutputStream(OutputStream* _out, bool _handleStream) 
  throw (Exception)
  : out(_out), handleStream(_handleStream) {

  if (out == 0) {
    throw(Exception("FilterOutputStream::FilterOutputStream - out ist 0", 
                    __FILE__, __LINE__));
  }

}

FilterOutputStream::~FilterOutputStream() {
  out->flush();
  
  if (handleStream == true) {
    if (out != 0) {
      delete(out);	
      out = 0;
    }
  }
}

void FilterOutputStream::write(int v) throw (IOException) {
  out->write(v);
}

void FilterOutputStream::write(DataBuffer* b, int offset, int length) 
  throw (IOException) {

  out->write(b, offset, length);
}
 
void FilterOutputStream::flush() throw (IOException) {
  out->flush();
}
