#ifndef _PixelFormat_h_
#define _PixelFormat_h_

#include <image/ImageApi.h>

/** Beschreibt ein Pixelformat.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-??-??, cK, Created.
 *   <li> 2000-12-30, cK, Commented
 * </ul>
 *
 * @todo mehr formate unterstuetzen ... evtl auch rgb, bgr, etc...
 * @todo wichtig ist auch ein 1 channel format fuer alphatexturen
 *
 * @version $Revision: 1.2 $, $Date: 2001/06/05 10:02:40 $
 *
 * @author cK, $Author: koestlin $
 */
class IMAGE_API PixelFormat {

 public:
  /** Erzeugt ein neues Format. 
   *
   * @param bitPerPixel Anzahl von Pit Pro Pixel.
   */
  PixelFormat(int bitPerPixel);

  /** Erzeugt ein Pixelformat aus einem anderen. 
   *
   * @param format Format.
   */
  PixelFormat(PixelFormat* format);
		
  /** Bit Pro Pixel. */
  unsigned int bitPerPixel;

  /** Byte Pro Pixel. */
  unsigned int bytePerPixel;

 private:
  /** Initialisierungsmethode.
   *
   * qparam _bitPerPixel Bitperpixel.
   */
  void init(int _bitPerPixel);

};

#endif // _PixelFormat_h_


