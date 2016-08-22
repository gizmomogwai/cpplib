#ifndef _GifImageCodec_h_
#define _GifImageCodec_h_

#include <image/ImageApi.h>

#include <image/codecs/ImageCodec.h>
#include <image/Image.h>


extern "C" {
  #include <gif_lib.h>
}

class GifImageCodec;

/** Hilfsklasse um die LibGifstructuren.
 *
 * Die Klasse ist 2-geteilt (Constructor und readData),
 * damit das aufraeumen im destruktor automatisch funktioniert.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *  <li> 2001-07-26, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.2 $ $Date: 2001/09/13 13:11:08 $
 *
 * @author cK $Author: koestlin $
 */
class IMAGE_API GifFileTypeWrapper {

  public:
    /** Liesst den GifHeader. 
     *
     * @param codec Der zum lesen verwendet wird.
     */
    GifFileTypeWrapper(GifImageCodec* codec);

    /** Raeumt auf. */
    virtual ~GifFileTypeWrapper();

    /** Liesst die gesamten GifDaten. */
    void readData();

    /** Anzahl von EinzelBildern im Gif.
     *
     * @return int Anzahl von Bildern.
     */
    int getNOfImages();

    /** Liefert die GifSavedImage-Struktur eines Bildes.
     *
     * @param idx Index de Bildes.
     *
     * @return SavedImage* Bild.
     */
    SavedImage* getImage(int idx);
    
    /** Liefert die Farbpaletteninformation aus dem GifFile. 
     *
     * @return ColorMapObject Farbpalette falls vorhanden oder NULL.
     */
    ColorMapObject* getColorMap() {
      return(fileType->SColorMap);
    }

  private:
    /** libungif-Handle. */
    GifFileType* fileType;
};

class GifImage : public Image {
 public:
  int fTop;
  
  int fLeft;
  
 GifImage(unsigned int width, unsigned int height, unsigned int bitPerPixel, int left, int top) : Image(width, height, bitPerPixel), fTop(top), fLeft(left) {
  }
  
  virtual ~GifImage() {
  }
  
};

/** Einfacher nicht sehr robuster GIF-Reader auf basis der
 * libungif.
 *
 * Unterstuetzt momentan gif 87 und 89, mit und ohne interlace und
 * wertet auch die transparente farbe richtig aus. Dabei 
 * im falle von Transparenz ein 32 bit bild im falle von 
 * nicht transparenz ein 24 bit bild erzeugt.
 *
 * Problematisch an gif sind natuerlich die rechte.
 * Allerdings steht bei der libungif dabei, dass nur ein dekoder 
 * kein problem macht -> nur dekoder :)).
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-07-26, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.2 $ $Date: 2001/09/13 13:11:08 $
 *
 * @author cK $Author: koestlin $
 */
class IMAGE_API GifImageCodec : public ImageCodec {

  public: 
  	GifImageCodec(int _imageIdx = 0) : imageIdx(_imageIdx) {
		}
		
		~GifImageCodec() {
		}
	
	  void write(Image* image, OutputStream* out) throw (Exception);

  	Image* read(InputStream* _in) throw (Exception);

	  /** Muss in target length Eintraege einlesen.
	   *
	   * @param userData Eigene Daten.
	   * @param target Zielspeicher.
	   * @param length Anzahl zu lesender Byte.
	   *
	   * @return int Anzahl von gelesenen Byte (sollte == Anzahl zu lesender
	   *	 Byte sein). 
	   */
	  static int gifRead(GifFileType* userData, GifByteType* target, int length);

  private:

    /** Eigentliche readfunktion. 
     * Das ganze koennte man hier noch verkuerzen, indem man den InputStream
     * als UserData verwendet.
     *
     * @param target Zielspeicher.
     * @param length Anzahl zu lesender byte.
     */
	  int read(GifByteType* target, int length);
	  
	  /** Index welches Gif z.b. aus einem animated Gif heraus geladen werden soll.
	   */
	  int imageIdx;

    /** Der Inputstream von dem gelesen werden soll. */
	  InputStream* in;

    /** Hilfszeiger auf die Gif-daten. */
    unsigned char* gifData;

    /** Hilfszeiger auf die dekodierten Bilddaten. */
    unsigned char* data;

    /** Index der transparenten Farbe. */
    unsigned char transparentIdx;

    /** Ist eine Farbe Transparent. */
    bool transparent;

    /** Breite einer Zeile. */
    int width;

    /** Farbtabelle. */
    ColorMapObject* colorMap;

    /** Kopiert eine Zeile von den Gif-Daten in die richtigen Daten. */
    void makeLine() {
      for (int i=0; i<width; i++) {
        unsigned char idx = *gifData++;
        GifColorType colors = colorMap->Colors[idx];
        *data++ = colors.Red;
        *data++ = colors.Green;
        *data++ = colors.Blue;
        if (transparent == true) {
          *data++ = (idx == transparentIdx) ? 0 : 255;
        }
      }
    }

};

#endif // _GifImageCodec_h_
