#ifndef _Image_h_
#define _Image_h_

#include <image/ImageApi.h>

#include <lang/DataBuffer.h>
#include <image/PixelFormat.h>

/** Bild.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-??-??, cK, Created.
 *   <li> 2000-12-30, cK, Commented.
 *   <li> 2001-03-22, cK, setAlpha eingefuehrt.
 *   <li> 2001-07-28, cK, getRect hinzugefuegt.
 * </ul>
 *
 * @todo Wahrscheinlich muss man das Pixelformat noch besser ausdefinieren
 *       koennen.
 *
 * @version $Revision: 1.3 $, $Date: 2001/09/13 13:11:08 $
 *
 * @author cK, $Author: koestlin $
 */
class IMAGE_API Image {

 public:
  /** Erzeugt ein neues Image.
   *
   * @param _width Breite.
   * @param _height Hoehe.
   * @param _bitPerPixel bpp.
   */
  Image(unsigned int _width, unsigned int _height, unsigned int _bitPerPixel);

  Image(unsigned int width, unsigned int height, unsigned int bitPerPixel, DataBuffer& buffer);

  /** Raeumt auf. */
  virtual ~Image();

  /** Liefert die Breite.
   *
   * @return int Breite.
   */
  unsigned int getWidth();

  /** Liefert die Hoehe.
   *
   * @return int Hoehe.
   */
  unsigned int getHeight();

  /** Loescht das Bild.
   */
  void clear();

  /** Liefert den Datenpuffer.
   *
   * @return DataBuffer* Datenpuffer.
   */
  DataBuffer* getBuffer();

  /** Liefert das Pixelformat.
   *
   * @return PixelFormat* format.
   */
  PixelFormat& getFormat();

  /** Liefert die Daten zu einem Pixel (und den darauffolgenden).
   *
   * @param xIdx XPositon (bei 0 beginnend).
   * @param yIdx YPosition (bei 0 beginnend).
   *
   * @return unsigned char* Pointer direkt in die Bilddaten.
   */
  unsigned char* getData(int xIdx, int yIdx) {
    return((unsigned char*)data->getData((yIdx * getWidth() + xIdx) * format.bytePerPixel));
  }

  /** Setzt die alphawerte des ganzen bildes.
   *
   * @param v Neuer alphawert.
   */
  void setAlpha(unsigned char v);

  /** Liefert einen Teil des Bildes als neues Bild.
   *
   * Es werden keine Bereichspruefungen gemacht.
   *
   * @param left Linke Koordinate.
   * @param top Obere Koordinate.
   * @param width Breite des gewuenschten Ausschnitts.
   * @param height Hoehe des gewuenschten Ausschnitts.
   *
   * @return Image* Neue Image.
   */
  Image* getRect(int left, int top, int width, int height);

  /** Liefert einen Teil des Bildes als neues Bild.
   *
   * Wird zuviel angefordert wird nichts kopiert.
   *
   * @param left Linke Koordinate.
   * @param top Obere Koordinate.
   * @param width Breite des gewuenschten Ausschnitts.
   * @param height Hoehe des gewuenschten Ausschnitts.
   *
   * @return Image* Neue Image.
   */
  Image* getClippedRect(int left, int top, int width, int height);

  /** Liefert die Anzahl von Bytes, die fuer eine Zeile benoetigt werden.
   *
   * @return int Anzahl von Bytes in einer Zeile.
   */
  unsigned int getRowStride() {
    return(width * format.bytePerPixel);
  }

 private:

  /** Breite. */
  unsigned int width;

  /** Hoehe. */
  unsigned int height;

  /** Format. */
  PixelFormat format;

  /** Die eigentlichen Bilddaten. */
  DataBuffer* data;
  bool fOwnData;

};

#endif // _Image_h_
