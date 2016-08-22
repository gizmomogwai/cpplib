#ifndef _TiffImageCodec_h_
#define _TiffImageCodec_h_

#include <image/codecs/ImageCodec.h>
#include <assert.h>
#include <lang/DataBuffer.h>

#include <tiffio.h>

#include <io/ByteArrayOutputStream.h>

class TiffImageCodec : public ImageCodec {

  public:
    TiffImageCodec() {
    }

    Image* read(InputStream* in) throw (Exception);

    void write(Image* image, OutputStream* out) throw (Exception) {
    }

    static tsize_t tiffReadFunc(thandle_t clientData, tdata_t target, tsize_t nOfBytes) {
      if (nOfBytes > 0) {
        TiffImageCodec* codec = (TiffImageCodec*)clientData;
        DataBuffer* dataBuffer = codec->memMapping->getData();
        memcpy(target, dataBuffer->getData(), nOfBytes);
        return(nOfBytes);
      } else {
        return(0);
      }
//      if (nOfBytes > 0) {

//        TiffImageCodec* codec = (TiffImageCodec*)clientData;
//
//        DataBuffer buffer(target, nOfBytes, false);
//        return(codec->in->read(&buffer));
//      } else {
//        return(0);
//      }
    }

    static tsize_t tiffWriteFunc(thandle_t clientData, tdata_t target, tsize_t nOfBytes) {

      return(0);
    }

//    static toff_t tiffSeekFunc(thandle_t clientData, toff_t offset, int mode) {
//      TiffImageCodec* codec = (TiffImageCodec*)clientData;
//      switch (mode) {
//        case 0: // File begin
//          return(codec->in->seek(SeekableInputStream::STREAM_BEGIN, offset));
//        case 1: // file current
//          return(codec->in->seek(SeekableInputStream::STREAM_RELATIVE, offset));
//        case 2: // file end
//          return(codec->in->seek(SeekableInputStream::STREAM_END, offset));
//      }
//      return(-1);
//    }

    static toff_t tiffSizeFunc(thandle_t clientData) {
      assert(false);
      return(0);
    }

    static int tiffCloseFunc(thandle_t clientData) {
    
      return(0);
    }

    static int tiffMapFileFunc(thandle_t clientData, tdata_t* data, toff_t* size);

    static void tiffUnmapFileFunc(thandle_t clientData, tdata_t data, toff_t size) {
    }
    
    static void warningHandler(const char* module, const char* fmt, va_list ap);


  private:

    ByteArrayOutputStream* memMapping;


};

#endif // _TiffImageCodec_h_
