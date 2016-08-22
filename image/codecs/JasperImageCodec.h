#ifndef _JasperImageCodec_h_
#define _JasperImageCodec_h_

#include <image/ImageApi.h>


#include <image/codecs/ImageCodec.h>
#include <io/IOException.h>

#include <assert.h>

#include <jasper/jasper.h>

class Image;
class InputStream;
class OutputStream;

class IMAGE_API JasperImageCodec : public ImageCodec {

  public:

    virtual ~JasperImageCodec() {
    }

	  Image* read(InputStream* in) throw (Exception);
    
    void write(Image* image, OutputStream* out) throw (Exception) {
    }

    static int jasperRead(jas_stream_obj_t* jStream, char* buf, int cnt);

    static int jasperWrite(jas_stream_obj_t* jStream, char* buf, int cnt);

    static long jasperSeek(jas_stream_obj_t* jStream, long offset, int origin);

    static int jasperClose(jas_stream_obj_t* jStream);
    
    InputStream* in;	

    jas_stream_t *createJasperStream() {
	    jas_stream_t *stream;

	    if (!(stream = (jas_stream_t*)jas_malloc(sizeof(jas_stream_t)))) {
		    return 0;
	    }
  	  stream->openmode_ = 0;
	    stream->bufmode_ = 0;
	    stream->flags_ = 0;
	    stream->bufbase_ = 0;
	    stream->bufstart_ = 0;
	    stream->bufsize_ = 0;
	    stream->ptr_ = 0;
	    stream->cnt_ = 0;
	    stream->ops_ = 0;
	    stream->obj_ = 0;
	    stream->rwcnt_ = 0;
	    stream->rwlimit_ = -1;

      stream->ops_ = &streamOperations;
      stream->obj_ = this;

      stream->openmode_ = JAS_STREAM_READ | JAS_STREAM_BINARY;

      stream->bufstart_ = new unsigned char[1024];
      assert(stream->bufstart_ != 0);

      stream->bufsize_ = 1024;
      stream->ptr_ = stream->bufstart_;
      stream->cnt_ = 0;

	    return stream;
    }

    void deleteJasperStream(jas_stream_t *stream) {
      delete[](stream->bufstart_);

      jas_stream_close(stream);
    }


  private:
    static jas_stream_ops_t streamOperations;


};

#endif // _JasperImageCodec_h_
