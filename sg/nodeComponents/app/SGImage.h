#ifndef _SGImage_h_
#define _SGImage_h_

#ifdef WIN32
  #pragma warning(disable:4786)
#endif // WIN32

#include <lang/Exception.h>
#include <image/Image.h>
#include <image/PixelFormat.h>

#include <sg/nodeComponents/NodeComponent.h>

    
/** Bilddaten in der Verantwortlichkeit des Szenegraphen.
 *
 * Man braucht diese Klasse um Image um Referencecounting zu erweitern.
 * Potentiell koennte man auch von Image erben, was allerdings nichts
 * bringen wuerde, da man die Codecs so nicht klarer verwenden koennte.
 * Vielleicht ist es aber moeglich per template-codec so etwas zu machen,
 * klarer wird das aber nicht.
 *
 * Die Schnittstelle nach aussen ist nicht SG-maessig. Das ist klar, da es
 * ich ja nicht um ein SGObject handelt, das man setzt oder geted.
 *
 * <p>
 * Philosophie:
 * <ul>
 *   <li> Sobald setImage aufgerufen wurde sollte man bei sich am besten
 *        das Bild sofort vergessen :))
 *   <li> getImage ist eigentlich als Private zu betrachen. Nur die
 *        Visitoren sollten das duerfen.
 * </ul>
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-12-14, cK, Created.    
 *   <li> 2001-01-03, cK, Parametercheck.
 * </ul>
 *
 * @version $Revision: 1.5 $, $Date: 2001/10/23 11:25:03 $
 *
 * @author cK, $Author: schaefer $
 */
class SGImage : public NodeComponent {
                        
 public:
	/** Erzeugt ein neues SGImage.
	 *
	 * @param _image Bild, das in des Szenegraphen uebernommen wird.
	 *
	 * @exception Exception falls _image == 0
	 */
  SGImage(Image* _image) throw (Exception) : format(0) {
		if (_image == 0) {
			throw(Exception("SGImage::SGImage(Image*) - _image == 0", __FILE__, __LINE__));
		}
		image = _image;  
    format = new PixelFormat(_image->getFormat());

    width = image->getWidth();
    height = image->getHeight();
	}            
           
	/** Liefert das Bild.
	 *
	 * Das bild darf von der Applikation nicht deleted werden.
	 * Potentiell sollte diese Methode nur Visitoren zugaenglich sein.
	 *
	 * @return Image* Bild, kann 0 sein, wenn deleteImage aufgerufen wurde.
	 */
	Image* getImage() {
		return(image);
	}

  /** Liefert die Breite.
   *
   * @return int Breite.
   */
  int getWidth() {

	  return(width);
  }

  /** Liefert die Hoehe.
   *
   * @return int Hoehe.
   */
  int getHeight() {

	  return(height);
  }


  /** Gibt den Speicher des unterliegenden Bildes frei. 
   */
  void deleteImage() {
    if (image != 0) {
      delete(image);
      image = 0;
    }

    /*if (format != 0) {
      delete(format);
      format = 0;
    }*/
  }

	/** Liefert das Format desBildes. 
	 *
	 * @return PixelFormat* Format.
	 */
  PixelFormat* getFormat() {
    return(format);
  }
  
		
 protected:

	/** Raeumt auf. */       
	virtual ~SGImage() {

    deleteImage();
    if (format != 0) {

      delete(format);
      format = 0;
    }
	}

 private:
	/** Bild. */
	Image* image;

  /** Hoehe des Bildes in Pixel */
  int height;

  /** Breite des Bildes in Pixel */
  int width;

	/** PixelFormat des Bildes. */
  PixelFormat* format;
  
};

#endif // _SGImage_h_
