#ifndef _RleImageCodec_h_
#define _RleImageCodec_h_

#include <image/ImageApi.h>

#include <lang/Exception.h>
#include <image/codecs/ImageCodec.h>
class Image;
class OutputStream;
class InputStream;
class DataOutputStream;

/** Codec, um Bilder RLE-maessig zu kodieren.
 * Einfaches Format:
 * 4 byte imageWidth
 * 4 byte imageHeight
 * byte repeat
 * 3 byte rgb
 *
 * Die Bilder werden Zeilenweise gespeichert. Der rle kann rechts aus dem bild
 * rauslaufen und links wieder rein, wird also nicht am zeilenende beendet.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-09-13, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.1 $ $Date: 2001/09/13 13:11:09 $
 *
 * @author cK $Author: koestlin $
 */
class IMAGE_API RleImageCodec : public ImageCodec {

  public:

    /** Erzeugt den Codec. 
     *
     * @param _vFlip Soll das Bild an der Y-Achse gespiegelt werden.
     */
    RleImageCodec(bool _vFlip = false) : vFlip(_vFlip) {
    }

    void write(Image* image, OutputStream* out) throw (Exception);

    Image* read(InputStream* in) throw (Exception) {
      throw(Exception("nyi"));
    }

  private:
    /** Schreibt einen RLE-Pixel.
     *
     * @param rle Anzahl von Wiederholungen (wird in einem byte 
     *        gespeichert ... also 0..255).
     * @param r Rotwert.
     * @param g Gruenwert.
     * @param b Blauwert.
     */
    void writePixels(int rle, 
                     unsigned char r, 
                     unsigned char g,
                     unsigned char b) throw (Exception);

    /** Ausgabestrom. */
    DataOutputStream* dOut;

    /** Soll gespiegelt werden. */
    bool vFlip;
};

#endif // _RleImageCodec_h_
