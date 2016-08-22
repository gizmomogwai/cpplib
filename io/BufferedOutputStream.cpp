#include <io/BufferedOutputStream.h>

#include <memory.h>

BufferedOutputStream::BufferedOutputStream(OutputStream* _out, 
                                           bool _handleStream, 
                                           int _size)
      : FilterOutputStream(_out, _handleStream), count(0) {
    	
  buffer = new ByteDataBuffer(_size);
}


BufferedOutputStream::~BufferedOutputStream() {

  flushBuffer();
  
  delete(buffer);
}

void BufferedOutputStream::write(int b) throw (IOException) {
  
  if (count >= buffer->getSize()) {
    flushBuffer();
	}
  unsigned char* help = (unsigned char*)(buffer->getData(count));
  count++;
  *help = (unsigned char)(b & 0xff);

}

void BufferedOutputStream::write(DataBuffer* _buffer, 
                                 int _offset, 
                                 int _length) throw (IOException) {
	
  if (_length >= buffer->getSize()) {

  	flushBuffer();

	  out->write(_buffer, _offset, _length);

	} else {
	
    if (_length > (buffer->getSize() - count)) {
	    flushBuffer();
	  }
	  
    void* src = _buffer->getData(_offset);
    void* dst = buffer->getData(count);
    count += _length;

    memcpy(dst, src, _length);
	  
  }
}


void BufferedOutputStream::flush() throw (IOException) {
    
  flushBuffer();
  FilterOutputStream::flush();
}

void BufferedOutputStream::flushBuffer() throw (IOException) {
  if (count > 0) {
    out->write(buffer, 0, count);
	  count = 0;
  }
}
