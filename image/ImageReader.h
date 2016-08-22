#ifndef _ImageReader_h_
#define _ImageReader_h_

#include <image/ImageApi.h>

#include <lang/Exception.h>
#include <lang/Strings.h>
#include <string>

class File;
class Image;

/** Einfache Klasse, die abhangig von einer Endung einen ImageCodec
 * waehlt und damit ein bild einliesst.
 * 
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-09-04, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.2 $ $Date: 2001/09/13 13:11:12 $
 *
 * @author cK $Author: koestlin $
 */
class IMAGE_API ImageReader {

public:

	/** Liesst ein Bild ein.
	 *
	 * Ein Codec wird automatisch abhaengig von der angegebenen Endung
	 * gewaehlt.
	 *
	 * @param fileName FileName.
	 *
	 * @return Image* Neues Bild geht in den Besitz des Callers ueber.
	 */
	static Image* readImage(std::string fileName) throw (Exception);

	/** Liesst ein Bild von einem File ein.
	 * Siehe readImage(std::string&amp; fileName).
	 *
	 * @param file File, bleibt im Besitz des Callers.
	 *
	 * @return Image* Neues Bild, geht in den Besitz des Callers ueber.
	 */
	static Image* readImage(File* file) throw (Exception);
	
	static bool matches(std::string filename, std::string pattern);

};

#endif // _ImageReader_h_
