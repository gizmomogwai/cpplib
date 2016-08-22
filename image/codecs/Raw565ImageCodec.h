#ifndef _Raw565ImageCodec_h_
#define _Raw565ImageCodec_h_

#include <image/ImageApi.h>

#include <io/IOException.h>
#include <image/codecs/ImageCodec.h>
class Image;
class OutputStream;
class InputStream;
class DataOutputStream;

/** 
 * Simpler 565-raw image codec
 * Einfaches Format:
 * 2 byte imageWidth
 * 2 byte imageHeight
 * 2 byte 565 rgb pro pixel
 *
 * Die Bilder werden Zeilenweise gespeichert.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2005-09-12, cK, Created.
 * </ul>
 */
class IMAGE_API Raw565ImageCodec : public ImageCodec {

  public:

    /** Erzeugt den Codec. 
     */
    Raw565ImageCodec() {
    }

    void write(Image* image, OutputStream* out) throw (Exception);

    Image* read(InputStream* in) throw (Exception) {
      throw(Exception("nyi"));
    }

  private:
	  void writePixel(OutputStream* out, int r, int g, int b) throw (IOException);

};

#endif // _Raw565ImageCodec_h_
