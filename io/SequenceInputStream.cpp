#include <io/SequenceInputStream.h>

SequenceInputStream::SequenceInputStream(InputStream* in1, 
                                         InputStream* in2) : in(0) {

  streamList.push_back(in1);
  streamList.push_back(in2);
  i = streamList.begin();
  nextStream();
}


SequenceInputStream::~SequenceInputStream() {
}

void SequenceInputStream::nextStream() {
  if (i == streamList.end()) {
		in = 0;
	} else {
    in = *i;
    i++;
  }
}

		
int SequenceInputStream::read() throw (IOException) {
  if (in == 0) {
    return(-1);
  }
  int res = in->read();
  if (res == -1) {
    nextStream();
    return(read());
  }
  return(res);
}


int SequenceInputStream::read(DataBuffer& target, int offset, int length) 
  throw (IOException) {

  if (in == 0) {
    return(-1);
  }
  int res = in->read(target, offset, length);
  if (res == -1) {
    nextStream();
    return(read(target, offset, length));
  }
  return(res);
}
