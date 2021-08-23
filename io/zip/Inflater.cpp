#include <io/zip/Inflater.h>
#include <lang/Exception.h>
#include <stdlib.h>

Inflater::Inflater(bool _noWrap) {
  init(_noWrap);
}

Inflater::Inflater() {
  init(false);
}

Inflater::~Inflater() throw (Exception) {

  if (::inflateEnd(stream) != Z_OK) {
    throw(Exception("Inflater::~Inflater", __FILE__, __LINE__));
  }

  free(stream);
}

void Inflater::init(bool _noWrap) {

  stream = (z_stream*)calloc(1, sizeof(z_stream));

  sourceBuffer = 0;
  sourceLength = 0;
  sourceOffset = 0;

  finished = false;
  needDict = false;

  switch (::inflateInit2(stream, _noWrap ? -MAX_WBITS : MAX_WBITS)) {
    case Z_OK:
      return;
    case Z_MEM_ERROR:
      throw(Exception("Out of Mem", __FILE__, __LINE__));
    default:
      throw(Exception("Inflater::init(bool)", __FILE__, __LINE__));
  }
}


int Inflater::inflate(DataBuffer* _targetBuffer, int _targetOffset, int _targetLength) {
  if (sourceLength <= 0) {
    return(0);
  }

  // evtl syncen
  stream->avail_in  = sourceLength;
  stream->avail_out = _targetLength;
  stream->next_in = (Bytef*)(sourceBuffer->getData(sourceOffset));
  stream->next_out = (Bytef*)(_targetBuffer->getData(_targetOffset));

  int res = ::inflate(stream, Z_PARTIAL_FLUSH);
  switch (res) {
  	case Z_STREAM_END:
	    finished = true;
	    //      std::cout << "Inflater::inflate() : Fertig mit decompression" << std::endl;
	  case Z_OK:
      // berechne wieviel sourcebytes noch da sind
      sourceOffset += sourceLength - stream->avail_in; 
      sourceLength = stream->avail_in;
      // berechne wieviele bytes decomprimiert wurden
      return(_targetLength - stream->avail_out);
	  case Z_NEED_DICT:
      needDict = true;
      /* Might have consumed some input here! */
      sourceOffset += sourceLength - stream->avail_in;
      sourceLength = stream->avail_in;
	  case Z_BUF_ERROR:
	    //      std::cout << "Z_BUF_ERROR" << std::endl;
      return 0;
  	case Z_DATA_ERROR:
      throw(Exception("Inflator::inflateBytes(): DataFormatException", 
                      __FILE__, __LINE__));
	  case Z_MEM_ERROR:
  	  throw(Exception("Out of Mem Inflator::infalteBytes", 
                      __FILE__, __LINE__));
    case Z_STREAM_ERROR:
      throw(Exception("Inflater::inflateBytes() - Z_STREAM_ERROR", 
                      __FILE__, __LINE__));
  	default:
	    throw(Exception("internalerror Inflator::inflateBytes", 
                      __FILE__, __LINE__));
   }

}

bool Inflater::needsInput() {
  return(sourceLength<=0);
}

void Inflater::setInput(DataBuffer* _sourceBuffer, int _sourceOffset, int _sourceLength) {
  sourceBuffer = _sourceBuffer;
  sourceOffset = _sourceOffset;
  sourceLength = _sourceLength;
}

long Inflater::getTotalOut() {
  return(stream->total_out);
}
