#include <image/codecs/JpegImageCodec.h>

#include <string>
#include <sstream>
#include <iostream>

#include <lang/ByteDataBuffer.h>
#include <lang/CleanUpObject.h>
#include <io/InputStream.h>
#include <image/Image.h>

class JpegDecompressor {
  public:
    JpegDecompressor(struct jpeg_decompress_struct* _jpegInfo)
      : jpegInfo(_jpegInfo), decompressStarted(false) {
      jpeg_create_decompress(jpegInfo);
    }

    void startDecompress() {
      jpeg_start_decompress(jpegInfo);
      decompressStarted = true;
    }

    int readScanlines(unsigned char** data) {
      return jpeg_read_scanlines(jpegInfo, data, 1);
    }

    virtual ~JpegDecompressor() {
      if (decompressStarted == true) {
        jpeg_finish_decompress(jpegInfo);
      }
      jpeg_destroy_decompress(jpegInfo);
    }

  private:
    struct jpeg_decompress_struct* jpegInfo;
    bool decompressStarted;
};

Image* JpegImageCodec::read(InputStream* _in) throw (Exception) {
  in = _in;
  out = 0;
  Image* res = 0;

  // create internal buffer
  buffer = new ByteDataBuffer(1024);
  CleanUpObject<DataBuffer> cleanUpBuffer(buffer);
  struct jpeg_decompress_struct cInfo;

  // setup errorhandling nur output wird "ueberschrieben"
  struct jpeg_error_mgr jErr;
  initErrorHandler(&jErr);
  cInfo.err = &jErr;

  JpegDecompressor decompressor(&cInfo);

  // setup clientdata
  cInfo.client_data = this;

  // setup datasource
  struct jpeg_source_mgr dataSource;
  dataSource.next_input_byte = 0;
  dataSource.bytes_in_buffer = 0;
  dataSource.init_source = JpegImageCodec::initSourceFN;
  dataSource.fill_input_buffer = JpegImageCodec::fillInputBufferFN;
  dataSource.skip_input_data = JpegImageCodec::skipInputDataFN;
  dataSource.resync_to_restart = JpegImageCodec::resyncToRestartFN;
  dataSource.term_source = JpegImageCodec::termSourceFN;
  cInfo.src = &dataSource;

  // read header
  int headerOk = jpeg_read_header(&cInfo, TRUE);
  if (headerOk != 1) {
    throw Exception("header not ok", __FILE__, __LINE__);
  }

  decompressor.startDecompress();

  // bild anlegen
  res = new Image((unsigned int)cInfo.output_width,
                  (unsigned int)cInfo.output_height,
      (unsigned int)8 * cInfo.out_color_components);
  try {
    int rowStride = res->getRowStride();
    unsigned char* data = 0;
    if (vFlip == false) {
      data = (unsigned char*)res->getData(0, 0);
    } else {
      data = (unsigned char*)res->getData(0, cInfo.image_height-1);
      rowStride = -rowStride;
    }

    // alle zeilen lesen.

    while (cInfo.output_scanline < cInfo.output_height) {
      int red = decompressor.readScanlines(&data);
      if (red != 1) {
        throw Exception("was soll das", __FILE__, __LINE__);
      } else {
        data += rowStride;
      }
    }
  } catch (...) {
    delete(res);
    throw;
  }


  if (jErr.num_warnings != 0) {
    // std::cout << "jpeg-warnings: " << jErr.num_warnings << std::endl;
  } else {
    // std::cout << "keine warnings" << std::endl;
  }
  return res;
}


void JpegImageCodec::write(Image* _image, OutputStream* _out)
  throw (Exception) {
  out = _out;
  if (_image->getFormat().bitPerPixel != 24) {
    throw(Exception("only 24 bit images supported", __FILE__, __LINE__));
  }

  buffer = new ByteDataBuffer(1024);
  CleanUpObject<DataBuffer> cleanUpBuffer(buffer);

  struct jpeg_compress_struct cInfo;

  // setup errorhandling nur output wird "ueberschrieben"
  struct jpeg_error_mgr jErr;
  initErrorHandler(&jErr);
  cInfo.err = &jErr;

  // erzeugt den compressor
  jpeg_create_compress(&cInfo);

  // setup clientdata
  cInfo.client_data = this;

  struct jpeg_destination_mgr dataOutput;
  dataOutput.next_output_byte = 0;
  dataOutput.free_in_buffer = 0;
  dataOutput.init_destination = JpegImageCodec::initDestinationFN;
  dataOutput.empty_output_buffer = JpegImageCodec::emptyOutputBufferFN;
  dataOutput.term_destination = JpegImageCodec::termDestinationFN;
  cInfo.dest = &dataOutput;

  // daten setzen
  cInfo.image_width = _image->getWidth();
  cInfo.image_height = _image->getHeight();
  cInfo.input_components = 3;
  cInfo.in_color_space = JCS_RGB;

  jpeg_set_defaults(&cInfo);
  jpeg_set_quality(&cInfo, quality, FALSE);

  // startet die compression
  jpeg_start_compress(&cInfo, TRUE);

  int rowStride = _image->getWidth() * _image->getFormat().bytePerPixel;
  unsigned char* data = 0;
  if (vFlip == false) {
    data = (unsigned char*)_image->getBuffer()->getData();
  } else {
    data = (unsigned char*)_image->getBuffer()->getData((cInfo.image_height-1)*rowStride);
    rowStride = -rowStride;
  }

  while (cInfo.next_scanline < cInfo.image_height) {
    int lines = jpeg_write_scanlines(&cInfo, &data, 1);
    if (lines != 1) {
      throw(Exception("was soll das", __FILE__, __LINE__));
    } else {
      data += rowStride;
    }
  }


  // finish compression
  jpeg_finish_compress(&cInfo);

  // aufraeumen
  jpeg_destroy_compress(&cInfo);

  out = 0;
}


boolean JpegImageCodec::fillInputBuffer(j_decompress_ptr cInfo) {
  int red = in->read(*buffer);
  if (red == -1) {
    return FALSE;
  }
  unsigned char* help = (unsigned char*)(buffer->getData());
  cInfo->src->next_input_byte = help;
  cInfo->src->bytes_in_buffer = red;
  return TRUE;
}


void JpegImageCodec::outputMessageFN(j_common_ptr cInfo) {
  char help[JMSG_LENGTH_MAX];

  (*cInfo->err->format_message)(cInfo, help);
  std::cout << "JpegImageCodec::outputMessageFN - " << help << std::endl;
}

void JpegImageCodec::errorExitFN(j_common_ptr cInfo) {
/*  std::cout << "JpegImageCodec::errorExitFn" << std::endl;

  char help[JMSG_LENGTH_MAX];
  (cInfo->err->format_message)(cInfo, help);
  std::ostringstream outHelp;
  outHelp << "JPEGImageCodec::errorExitFN - " << help << std::ends;
  std::string errMessage(outHelp.str());
  std::cout << "errmessage " << errMessage << std::endl;

  throw Exception("pech im jpeg teil", __FILE__, __LINE__);
*/
}

void JpegImageCodec::initErrorHandler(struct jpeg_error_mgr* jErr) {
  jpeg_std_error(jErr);
  jErr->error_exit = JpegImageCodec::errorExitFN; // else System.exit is called
  //jErr->output_message = JpegImageCodec::outputMessageFN;
}
