#include <io/zip/GZIPInputStream.h>
#include <io/ByteArrayInputStream.h>
#include <io/SequenceInputStream.h>

#include <io/zip/Inflater.h>
#include <io/zip/CheckedInputStream.h>
#include <lang/Exception.h>

#include <assert.h>

const int GZIPInputStream::GZIP_MAGIC = 0x8b1f;

const int GZIPInputStream::FTEXT = 1;	// Extra text
const int GZIPInputStream::FHCRC = 2;	// Header CRC
const int GZIPInputStream::FEXTRA = 4;	// Extra field
const int GZIPInputStream::FNAME = 8;	// File name
const int GZIPInputStream::FCOMMENT = 16;	// File comment

GZIPInputStream::GZIPInputStream(InputStream* _in, 
                                 bool _handleStream, 
                                 int _size) 
  : InflaterInputStream(_in, 
                        _handleStream, 
                        new Inflater(true), 
                        _size), 
    crc(new CRC32()), eos(false) {

  readHeader();
  crc->reset();
}

GZIPInputStream::~GZIPInputStream() {
  delete(crc);
}


unsigned short GZIPInputStream::readUShort(InputStream* _in) {
  int b = _in->read();
  return((unsigned short)(_in->read() << 8 | b));
}

long GZIPInputStream::readUInt(InputStream* _in) {
  long s = readUShort(_in);
  return(readUShort(_in) << 16 | s);
}

void GZIPInputStream::skipBytes(InputStream* _in, int bytes) {
  for (int i=0; i<bytes; i++) {
    _in->read();
  }
}


void GZIPInputStream::readHeader() {
  CheckedInputStream* cIn = new CheckedInputStream(in, false, crc);
  assert(cIn != 0);
  crc->reset();
  
  // Check header magic (2 byte) ushort
  int h = readUShort(cIn);
  if (h != GZIP_MAGIC) {
    throw(Exception("Not in GZIP format", __FILE__, __LINE__));
  }
  
  
  // Check compression method
  h = cIn->read();
  if (h != 8) {
    throw Exception("Unsupported compression method", __FILE__, __LINE__);
  }
  
  // Read flags
  int flg = cIn->read();
  // Skip MTIME, XFL, and OS fields
  skipBytes(cIn, 6);
  
  // Skip optional extra field
  if ((flg & FEXTRA) == FEXTRA) {
    skipBytes(cIn, readUShort(cIn));
  }
  // Skip optional file name
  if ((flg & FNAME) == FNAME) {
    while (cIn->read() != 0) ;
  }
  // Skip optional file comment
  if ((flg & FCOMMENT) == FCOMMENT) {
    while (cIn->read() != 0) ;
  }
  // Check optional header CRC
  if ((flg & FHCRC) == FHCRC) {
    
    int v = (int)(crc->getChecksum() & 0xffff);
    if (readUShort(cIn) != v) {
      throw(Exception("Corrupt GZIP header", __FILE__, __LINE__));
    }
  }
  
  delete(cIn);
}


int GZIPInputStream::read() throw (IOException) {
  if (eos == true) return(-1);
  unsigned char data[1];
  DataBuffer _b(data, 1, false);
  int res = read(_b, 0, 1);
  if (res != -1) {
    res = data[0]; 
  }
  return(res);
}

int GZIPInputStream::read(DataBuffer& _b, int _offset, int _length) 
  throw (IOException) {

  if (eos == true) return(-1);
  _length = InflaterInputStream::read(_b, _offset, _length);
  if (_length == -1) {
    readTrailer();
    eos = true;
  } else {
    crc->update(&_b, _offset, _length);
  }

  return(_length);
}

void GZIPInputStream::readTrailer() {

/*
    private void readTrailer() throws IOException {
	InputStream in = this.in;
	int n = inf.getRemaining();
	if (n > 0) {
	    in = new SequenceInputStream(
			new ByteArrayInputStream(buf, len - n, n), in);
	}
	long v = crc.getValue();
	if (readUInt(in) != v || readUInt(in) != inf.getTotalOut()) {
	    throw new IOException("Corrupt GZIP trailer");
	}
    }
*/
  
  InputStream* _in = in;
  int n = inf->getRemaining();
  if (n > 0) {
    ByteArrayInputStream* byteIn = 
      new ByteArrayInputStream(sourceBuffer, fillState - n, n);
    _in = new SequenceInputStream(byteIn, _in);
    handleRest(_in);    
    delete(_in);
    delete(byteIn);
  } else {
    handleRest(_in);
  }

}

void GZIPInputStream::handleRest(InputStream* _in) {
  long v = crc->getChecksum();
  long l = readUInt(_in);
  if (l != v) {
    throw(Exception("GZIPInputStream::readTrailer: Corrupt GZIP Trailer 1", 
                    __FILE__, __LINE__));
  }
  
  l = readUInt(_in);
  if (l != inf->getTotalOut()) {
    throw(Exception("GZIPInputStream::readTrailer: Corrupt GZIP Trailer 2", 
                    __FILE__, __LINE__));
  }

}


