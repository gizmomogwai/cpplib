#include <lang/ByteDataBuffer.h>
#include <lang/Exception.h>

#include <io/zip/InflaterInputStream.h>

InflaterInputStream::InflaterInputStream(InputStream* _in, 
					 bool _handleStream, 
					 Inflater* _inf, 
					 int _size) 
  : FilterInputStream(_in, _handleStream),
    inf(_inf), 
    sourceBuffer(new ByteDataBuffer(_size)),
    fillState(0), 
    eofReached(false) {
  inf->setInput(sourceBuffer, 0, fillState);  
}


InflaterInputStream::~InflaterInputStream() {
  delete(sourceBuffer);
  delete(inf);
}

int InflaterInputStream::read() throw (IOException) {
  unsigned char h[1];
  DataBuffer buffer(h, 1, false);
  int res = read(buffer, 0, 1);
  if (res == -1) return(res);
  return((int)(h[0]));
}

int InflaterInputStream::read(DataBuffer& _target, 
			      int _targetOffset, int _targetLength) 
  throw (IOException) {

  int n;
  n = inf->inflate(&_target, _targetOffset, _targetLength);
  while (n == 0) {
  	if ((inf->isFinished() == true) || 
	      (inf->needsDictionary() == true)) {
	  //      std::cout << "end of stream reached" << std::endl;
  	  eofReached = true;
	    return(-1);
	  }
	  if (inf->needsInput() == true) {
  	  fill();
  	}
  	n = inf->inflate(&_target, _targetOffset, _targetLength);
  }
  return(n);
}

void InflaterInputStream::fill() {
  fillState = in->read(*sourceBuffer, 0, sourceBuffer->getSize());
  if (fillState == -1) {
    throw(Exception("unexpected End of ZLIB input stream", 
                    __FILE__, __LINE__));
  }
  inf->setInput(sourceBuffer, 0, fillState);  
}

