#include <image/codecs/PngImageCodec.h>

#include <lang/CleanUpObject.h>
#include <lang/CleanUpArray.h>
#include <lang/DataBuffer.h>
#include <lang/ByteDataBuffer.h>

#include <assert.h>
#include <iostream>

#include <image/Image.h>
#include <io/InputStream.h>
#include <io/OutputStream.h>


const int PngImageCodec::RGB = 0;
const int PngImageCodec::BGR = 1;

class PngStruct {
  public:
    PngStruct() : pngPtr(0), infoPtr(0) {
    }

    void setInfoPtr(png_infop _infoPtr) {
      assert(_infoPtr);
      infoPtr = _infoPtr;
    }

    png_infop getInfoPtr() {
      assert(infoPtr);
      return infoPtr;
    }

    void setPngPtr(png_structp _pngPtr) {
      assert(_pngPtr);
      pngPtr = _pngPtr;
    }

    void setBgr() {
      png_set_bgr(getPngPtr());
    }

    png_structp getPngPtr() {
      assert(pngPtr);
      return pngPtr;
    }

    virtual ~PngStruct() {
    }

  protected:
    void initInfoPtr() {
      setInfoPtr(png_create_info_struct(getPngPtr()));
    }

    png_structp pngPtr;
    png_infop infoPtr;
};

class PngReadStruct : public PngStruct {
  public:
    PngReadStruct() {
      setPngPtr(png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0));
      initInfoPtr();
    }

    void readInfo() {
      png_read_info(getPngPtr(), getInfoPtr());
    }

    png_byte getColorType() {
      return getInfoPtr()->color_type;
    }


    png_uint_32 getWidth() {
      return getInfoPtr()->width;
    }

    png_uint_32 getHeight() {
      return getInfoPtr()->height;
    }
    
    int getBitPerPixel() throw (Exception) {
      png_byte colorType = getColorType();
      switch (colorType) {
        case PNG_COLOR_TYPE_RGB:
          return 24;
        case PNG_COLOR_TYPE_RGB_ALPHA:
          return 32;
        case PNG_COLOR_TYPE_GRAY:
          png_set_gray_to_rgb(getPngPtr());
          return 24;
        case PNG_COLOR_TYPE_GRAY_ALPHA:
          png_set_gray_to_rgb(getPngPtr());
          return 32;
        case PNG_COLOR_TYPE_PALETTE:
          png_set_packing(getPngPtr()); 
          png_set_palette_to_rgb(getPngPtr());
          return 32;
        default:
          throw Exception("unsupported color_type", __FILE__, __LINE__);
      }
      // 16bit pngs
    }

    void readImage(png_bytep* rowPointers) {
      png_read_image(getPngPtr(), rowPointers);
      png_read_end(getPngPtr(), getInfoPtr());
    }

    virtual ~PngReadStruct() {
      png_destroy_read_struct(&pngPtr, &infoPtr, (png_infopp)0);
    }
};

class PngWriteStruct : public PngStruct {
  public:
    PngWriteStruct() {
      setPngPtr(png_create_write_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0));
      initInfoPtr();
    }
    virtual ~PngWriteStruct() {
      png_destroy_write_struct(&pngPtr, &infoPtr);
    }

    void setImageHeader(Image* image) {
      int bytePerPixel = image->getFormat().bytePerPixel;
      int colorType;
      if (bytePerPixel == 3) {
        colorType = PNG_COLOR_TYPE_RGB;
      } else if (bytePerPixel == 4) {
        colorType = PNG_COLOR_TYPE_RGB_ALPHA;
      } else {
        throw Exception("only 3 and 4 byte pp supported", __FILE__, __LINE__);
      }

      png_set_IHDR(getPngPtr(), getInfoPtr(), 
                   image->getWidth(), 
                   image->getHeight(), 
                   8,
                   colorType, 
                   PNG_INTERLACE_NONE,
                   PNG_COMPRESSION_TYPE_DEFAULT,
                   PNG_FILTER_TYPE_DEFAULT);
    }

    void writeInfo() {
      png_write_info(pngPtr, infoPtr);
    }

    void writeImage(png_bytep* rowPointers) {
      png_write_image(getPngPtr(), rowPointers);
      png_write_end(getPngPtr(), getInfoPtr());
    }

};


Image* PngImageCodec::read(InputStream* _in) throw (Exception) {
  out = 0;
  in = _in;  
  buffer = new DataBuffer(0, 0, false);
  CleanUpObject<DataBuffer> bufferCleaner(buffer);

  // std png init
  PngReadStruct readStruct;

  if (byteOrder == BGR) {
    readStruct.setBgr();
  }

  // check png signature
  ByteDataBuffer checkBytes(8);
  int red = _in->read(checkBytes);
  while (red < 8) {
    red += _in->read(checkBytes, red, 8-red);
  }

  if (png_sig_cmp((unsigned char*)checkBytes.getData(), 0, 8) != 0) {
    throw(Exception("no png", __FILE__, __LINE__));
  }
  png_set_sig_bytes(readStruct.getPngPtr(), 8);

  // check for png finished
  
  png_set_read_fn(readStruct.getPngPtr(), (voidp)this, (png_rw_ptr)readFn);
  
  readStruct.readInfo();

  Image* res = new Image((unsigned int)readStruct.getWidth(), 
                         (unsigned int)readStruct.getHeight(), 
                         (unsigned int)readStruct.getBitPerPixel());
  png_bytep data = (png_bytep)(res->getBuffer()->getData());
  int height = res->getHeight();
  png_bytep* rowPointers = new png_bytep[height];
  CleanUpArray<png_bytep> rowPointersCleaner(rowPointers);

  for (int i=0; i<height; i++) {
    rowPointers[i] = data;
    data += res->getRowStride();
  }
  readStruct.readImage(rowPointers);
  
  in = 0;

  return(res);
}

void PngImageCodec::write(Image* image, OutputStream* _out) 
	throw (Exception) {
  in = 0;
  out = _out;  
  buffer = new DataBuffer(0, 0, false);
  CleanUpObject<DataBuffer> bufferCleaner(buffer);
  
  PngWriteStruct writeStruct;

  assert(!setjmp(writeStruct.getPngPtr()->jmpbuf));

  png_set_write_fn(writeStruct.getPngPtr(), (voidp)this, (png_rw_ptr)writeFn, (png_flush_ptr)flushFn);

  writeStruct.setImageHeader(image);

  writeStruct.writeInfo();

  png_bytep data = 0;

  int height = image->getHeight();
  png_bytep* rowPointers = new png_bytep[height];
  CleanUpArray<png_bytep> rowPointersCleaner(rowPointers);

  int rowStride = image->getWidth() * image->getFormat().bytePerPixel;
  if (vFlip == false) {
    data = (png_bytep)image->getBuffer()->getData();
  } else {
    data = (png_bytep)image->getBuffer()->getData((height-1) * rowStride);
    rowStride = -rowStride;
  }

  for (int k=0; k<height; k++) {
    rowPointers[k] = data;
    data += rowStride;
  }

  writeStruct.writeImage(rowPointers);

  out = 0;
}

void PngImageCodec::readFn(png_structp png, png_bytep data, png_uint_32 l) {
  PngImageCodec* codec = (PngImageCodec*)png_get_io_ptr(png);
  codec->read(data, l);
}

void PngImageCodec::writeFn(png_structp png, png_bytep data, png_uint_32 l) {
  PngImageCodec* codec = (PngImageCodec*)png_get_io_ptr(png);
  codec->write(data, l);
}

void PngImageCodec::flushFn(png_structp png) {
//  PNGImageCodec* codec = (PNGImageCodec*)png_get_io_ptr(png);
//  codec->flush();
}

void PngImageCodec::read(png_bytep data, png_uint_32 l) {
  png_bytep help = data;
  buffer->setData(help, l, false);

  int toDo = l;
  int red = in->read(*buffer);
  assert(red != -1);
  
  toDo -= red;
  while (toDo > 0) {
    help += red;
    buffer->setData(help, toDo, false);
    
    red = in->read(*buffer);
    assert(red != -1);

    toDo -= red;
  }  
}

void PngImageCodec::write(png_bytep data, png_uint_32 l) {
  buffer->setData(data, l, false);
  out->write(buffer);
}
