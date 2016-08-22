#ifndef _IJLImageCodec_h_
#define _IJLImageCodec_h_

#include <image/ImageApi.h>

#include <pragmaincludes.h>

#include <lang/Exception.h>

#include <io/InputStream.h>
#include <io/OutputStream.h>

#include <image/Image.h>
#include <image/codecs/ImageCodec.h>

/** JPEGImageCodec auf der IntelPerforamceLib basierend.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-0?-??, cK, Created.
 *   <li> 2001-06-02, cK, Commented.
 * </ul>
 *
 * @version $Revision: 1.2 $ $Date: 2001/06/05 10:02:40 $
 *
 * @author cK, $Author: koestlin $
 */
class IMAGE_API IJLImageCodec : public ImageCodec {
  
 public:
	/** Liesst das Bild ein.
	 *
	 * @param in InputStream.
	 */
  Image* read(InputStream* in) throw (Exception);
  
	/** Schreibt das Bild (nicht implementiert.
	 *
	 * @parma image Bild
	 * @param out OutputStream.
	 */
  void write(Image* image, OutputStream* out) throw (Exception) {
  }
  
};

#endif // _IJLImageCodec_h_
