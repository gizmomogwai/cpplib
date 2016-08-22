#include <image/codecs/JasperImageCodec.h>

#include <io/InputStream.h>
#include <image/Image.h>

#include <iostream>
#include <lang/DataBuffer.h>
#include <image/codecs/JasperRuntime.h>

jas_stream_ops_t JasperImageCodec::streamOperations = {
  JasperImageCodec::jasperRead,
  JasperImageCodec::jasperWrite,
  JasperImageCodec::jasperSeek,
  JasperImageCodec::jasperClose
};

Image* JasperImageCodec::read(InputStream* _in) {
	assert(_in != 0);

  in = _in;

	JasperRuntime::init();

  jas_stream_t* jasperStream = createJasperStream();
  assert(jasperStream != 0);

  // -1 means autodetect format
  jas_image_t* jasperImage = jas_image_decode(jasperStream, -1, 0);
  deleteJasperStream(jasperStream);
  if (jasperImage == 0) {
    throw(Exception("cannot decode image", __FILE__, __LINE__));
  }

  // imagecomponenten checken
  int numComps = jas_image_numcmpts(jasperImage);
  if (numComps != 3) {
    throw(Exception("illegal number of components", __FILE__, __LINE__));
  }

  int width = jas_image_cmptwidth(jasperImage, 0);
  int height = jas_image_cmptheight(jasperImage, 0);
  int depth = jas_image_cmptwidth(jasperImage, 0);

  jas_matrix_t* redMatrix = jas_matrix_create(height, width);
  assert(redMatrix != 0);

  jas_matrix_t* greenMatrix = jas_matrix_create(height, width);
  assert(greenMatrix != 0);

  jas_matrix_t* blueMatrix = jas_matrix_create(height, width);
  assert(blueMatrix != 0);

  int res = jas_image_readcmpt(jasperImage, 0, 0, 0, width, height, redMatrix);
  assert(res == 0);
  register int* redData = jas_matrix_getref(redMatrix, 0, 0);

  res = jas_image_readcmpt(jasperImage, 1, 0, 0, width, height, greenMatrix);
  assert(res == 0);
  register int* greenData = jas_matrix_getref(greenMatrix, 0, 0);
  
  res = jas_image_readcmpt(jasperImage, 2, 0, 0, width, height, blueMatrix);
  assert(res == 0);
  register int* blueData = jas_matrix_getref(blueMatrix, 0, 0);

  jas_image_destroy(jasperImage);

  Image* resImage = new Image(width, height, 24);
  register unsigned char* data = resImage->getData(0, 0);

  for (register int j=height; j>0; j--) {
    for (register int i=width; i>0; i--) {
      *data++ = *redData++;
      *data++ = *greenData++;
      *data++ = *blueData++;
    }
  }

  jas_matrix_destroy(redMatrix);
  jas_matrix_destroy(greenMatrix);
  jas_matrix_destroy(blueMatrix);

  return(resImage);

}

int JasperImageCodec::jasperRead(jas_stream_obj_t* obj, char* buf, int cnt) {
  int res = 0;
  if (cnt != 0) {
    DataBuffer* buffer = new DataBuffer(buf, cnt, false);
    JasperImageCodec* codec = (JasperImageCodec*)obj;

    res = codec->in->read(buffer);
    delete(buffer);
  }
  return(res);
}

int JasperImageCodec::jasperWrite(jas_stream_obj_t* jStream, char* buf, int cnt) {
  return(0);
}

long JasperImageCodec::jasperSeek(jas_stream_obj_t* jStream, long offset, int origin) {
  return(0);
}

int JasperImageCodec::jasperClose(jas_stream_obj_t* jStream) {
  return(0);
}
