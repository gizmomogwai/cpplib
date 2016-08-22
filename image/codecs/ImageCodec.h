#ifndef _ImageCodec_h_
#define _ImageCodec_h_

#include <image/ImageApi.h>

class Image;
class InputStream;
class OutputStream;

#include <lang/Exception.h>

/** Oberklasse fuer Bild-file-formate.
 *
 * Momentan noch minimale Schnittstelle .. das ist auch ganz gut so.
 * 
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-??-??, cK, Created.
 *   <li> 2000-12-30, cK, Commented.
 * </ul>
 *
 * @version $Revision: 1.4 $, $Date: 2001/10/23 11:25:02 $
 *
 * @author cK, $Author: schaefer $
 */
class IMAGE_API ImageCodec {

	public:
    virtual ~ImageCodec() {
		}
		
	  /** Schreibt ein Bild in einen Ausgabestrom.
	   *
	   * @param image Bild.
	   * @param out Ausgabestrom, der wird nicht geschlossen.
	   */
		virtual void write(Image* image, OutputStream* out) throw (Exception) = 0 ;
		
		/** Liesst ein Bild von einem Eingabestrom.
		 *
		 * @param in Eingabestrom.
		 * 
		 * @return Image* Neues Bild, dass von der Applikation befreit werden
		 *		 muss.  
		 */
		virtual Image* read(InputStream* in) throw (Exception) = 0;

};

#endif // _ImageCodec_h_
