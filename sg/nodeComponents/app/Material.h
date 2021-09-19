#ifndef _Material_h_
#define _Material_h_

#include <sg/nodeComponents/NodeComponent.h>

#include <util/UpdateObject.h>

#include <vecmath/Color3f.h>
#include <sg/math/RCColor3f.h>

/** Kapselt die Materialeinstellungen in eine Klasse.
 *
 * Hier sollte wohl sowas wie ambientes Licht etc. rein!
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-11-28, cK, Created.
 *   <li> 2001-04-05, cK, etwsa weitergemacht.
 *   <li> 2001-04-11, cK, Lighting flag hinzugefuegt.
 *   <li> 2001-05-26, cK, Colof3f/RCColor3f eingebaut.
 * </ul>
 *
 * @todo Den Fabian fragen, was da reinsollte. J3D hat Ambientcolor,
 *       DiffuseColor, SpecularColor, EmissiveColor und Shininess drin.
 *
 * @version $Revision: 1.2 $, $Date: 2001/05/28 09:40:54 $
 *
 * @author cK, $Author: koestlin $
 */
class Material : public NodeComponent {

  public:
    /** Erzeugt ein neues Material. ohne farbe und ohne beleuctung.
     */
    Material() : color(0), lighted(false) {
    }

    /** Setzt die Farbe des Materials.
     *
     * @param _color3f Neue Farbe.
     */
    void setColor(Color3f* _color3f) {
      RCColor3f* c = new RCColor3f(_color3f);
      if (color == 0) {
        color = new UpdateObject<RCColor3f>();
      }
      color->set(c);
      c->releaseReference();
    }

    /** Setzt die Farbe des Materials.
     *
     * @param rcColor3f Neue Farbe.
     */
    void setColor(RCColor3f* rcColor3f) {
      if (color == 0) {
        color = new UpdateObject<RCColor3f>();
      }
      color->set(rcColor3f);
    }

    /** Liefert die Farbe des Materials (sgmaessig).
     *
     * @return RCColor3f* Farbe (sgmaessig).
     */
    RCColor3f* getColor() {
      if (color == 0) return(0);
      return(color->get());
    }

    /** Soll das Material beleuchtet werden oder nicht.
     *
     * @param flag Licht an oder aus.
     */
    void setLighting(bool flag) {
      lighted = flag;
    }

    /** Farbe des Materials. */
    UpdateObject<RCColor3f>* color;

    /** Ist das Material beleuchtet. */
    bool lighted;

  protected:
    /** Raeumt auf. */
    virtual ~Material() {
      if (color != 0) {
        delete(color);
        color = 0;
      }
    }

};

#endif // _Material_h_
