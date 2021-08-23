#ifndef _PngImageCodec_h_
#define _PngImageCodec_h_

#include <image/ImageApi.h>

#include <png.h>
#include <image/codecs/ImageCodec.h>
class DataBuffer;

/** Codec fuer das Portable Network Graphics Fileformat.
 *
 * Basiert auf der libpng. Liesst momentan nur rgb-bilder ein.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-??-??, cK, Created.
 *   <li> 2000-12-30, cK, Commented.
 *   <li> 2001-04-12, cK, PNGCheck anhand der ersten 8 byte eingebaut.
 * </ul>
 *
 * @version $Revision: 1.3 $, $Date: 2001/09/13 13:11:09 $
 *
 * @author cK, $Author: koestlin $
 */
class IMAGE_API PngImageCodec : public ImageCodec {

 public:
   /** Konstante fuer BGR-Bildein/ausgabe. */
   const static int BGR;

   /** Konstante fuer RGB-Bildein/ausgabe. */
   const static int RGB;


  /** Erzeugt einen COdec, der das Bild oprional vertikal flippt und
   * entweder RGB oder BGR Bilder erzeugt.
   *
   * @param _byteOrder RGB oder BGR
   * @param _bFlip Vertikal Flip.
   */
  PngImageCodec(int _byteOrder=RGB, bool _vFlip=false)
    : byteOrder(_byteOrder), vFlip(_vFlip) {}

   /** Raeumt auf. */
  virtual ~PngImageCodec() {
  }

  void write(Image* _image, OutputStream* _out) throw (Exception);

  Image* read(InputStream* _in) throw (Exception);


 private:
  /** Statische Hilfsmethode, um Daten einzulesen.
   *
   * @param pngPtr PNG-Object.
   * @param data Datenpuffer, in den die Daten gelesen werden sollen.
   * @param length Platz im Puffer.
   */
  static void readFn(png_structp pngPtr, png_bytep data,
                     png_uint_32 length);

  /** Eigentliche Implementierung.
   *
   * @param data Zielpuffer.
   * @param l Laenge des Puffers.
   */
  void read(png_bytep data, png_uint_32 l);

  /** Statische Hilfsmethode, um Daten zu schreiben.
   *
   * @param pngPtr PNG-Object.
   * @param data Datenpuffer, in den geschrieben werden sollen.
   * @param length Laenge des Puffers.
   */
  static void writeFn(png_structp pngPtr, png_bytep data,
                      png_uint_32 length);

  /** Eigentlich Implementierung.
   *
   * @param data Puffer mit zu schreibenden Daten.
   * @param l Laenge des Puffers.
   */
  void write(png_bytep data, png_uint_32 l);

  /** flusht.
   *
   * @param pngPtr PNG-Object.
   */
  static void flushFn(png_structp pngPtr);

  /** Inputstream, nur bei read. */
  InputStream* in;

  /** Outputstream, nur bei write. */
  OutputStream* out;

  /** Datenpuffer, der entweder von read, oder von write
   * verwendet wird.
   */
  DataBuffer* buffer;

  /** Byteorder. */
  int byteOrder;

  /** Soll das Bild gespiegelt werdern. */
  bool vFlip;

};

#endif // _PngImageCodec_h_
