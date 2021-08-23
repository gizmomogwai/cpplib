#ifndef _Texture_h_
#define _Texture_h_

#include <sg/nodeComponents/NodeComponent.h>

#include <sg/nodeComponents/app/SGImage.h>

#include <util/UpdateObject.h>

/** Texturklasse im Szenegraphen.
 *
 * Klasse, die zum einen die Bilddaten verwaltet, zum anderen
 * textur-typische Parameter hat.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-12-03, cK, Created.
 *   <li> 2001-02-09, cK, Wraps, WrapT eingefuegt.
 *   <li> 2001-07-05, cK, UpdateObject nicht mehr gepointert.
 *   <li> 2001-07-06, cK, Ohne TextureListener.
 * </ul>
 *
 * @todo ..waere es besser, wenn wrap-s/t in einem updateobject waere???
 * @todo Ueberlegen, wie sinnvoll es ist, das Bild zurueckzuliefern.
 * @todo Sicherlich braucht man da eine updateData Schnittstelle.
 *
 * @version $Revision: 1.4 $, $Date: 2001/07/06 11:05:33 $
 *
 * @author cK, $Author: koestlin $
 */
class Texture : public NodeComponent {

  public:
    /** Erzeugt ein neues Texturobjekt aus einem Image.
     *
     * @param _image Bild, das als Texstur verwendet werden soll.
     */
    Texture(SGImage* _image);

    void accept(Visitor* v) {
      v->visit(this);
    }

		/** Liefert das SGImage zurueck.
		 *
		 * @return SGImage* Bild.
		 */
		virtual SGImage* getImage();

    /** Bild. */
    UpdateObject<SGImage> image;

    /** Aendert das wrapverhalten der Textur.
     *
     * @param newWrapS neues wraps.
     * @param newWrapT neues wrapt.
     */
    void setTextureWrap(bool newWrapS, bool newWrapT);

    /** Boundarymode in s-richtung. */
    bool wrapS;

    /** Boundarymode in t-richtung. */
    bool wrapT;

    /** Liefert Stringrep. */
    std::string toString() {
      return("Texture");
    }

  protected:
    /** Raeumt auf. */
    virtual ~Texture();

};

#endif // _Texture_h_
