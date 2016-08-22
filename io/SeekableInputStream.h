#ifndef SeekableInputStream_h_
#define SeekableInputStream_h_

#include <io/IoApi.h>

class ByteArrayOutputStream;
class ByteDataBuffer;
#include <io/FilterInputStream.h>

class IO_API SeekableInputStream : public FilterInputStream {

  public:

  	SeekableInputStream(InputStream* _in, 
                        int size = 2048, 
                        bool _handleStream = false);

	  virtual ~SeekableInputStream();

	  int read() throw (IOException);

      int read(DataBuffer& buffer) throw (IOException);

	  int read(DataBuffer& targetBuffer, int offset, int length) throw (IOException);

	  int seek(int mode, int offset);

	  ByteArrayOutputStream* helpStream;

	  ByteDataBuffer* data;

	  unsigned int pos;

	  static int STREAM_BEGIN;
	  static int STREAM_RELATIVE;
	  static int STREAM_END;

};

#endif // SeekableInputStream_h_
