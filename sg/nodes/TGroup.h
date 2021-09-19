#ifndef _TGroup_h_
#define _TGroup_h_

#include <string>

#include <sg/nodes/Group.h>
#include <sg/visitors/Visitor.h>
#include <util/UpdateObject.h>
#include <vecmath/Transform3D.h>
#include <sg/math/RCTransform3D.h>

/** Gruppe, die transformiert werden kann.
 * Das bedeutet alle Kinder von ihr werden auch dieser Transformation
 * unterzogen. Initial ist die Transformation ID.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-11-25, cK, Created.
 *   <li> 2001-01-06, cK, Commentare korrigiert.
 *   <li> 2001-03-02, cKgS, Um toString erweitert.
 *   <li> 2001-03-08, cK, Ohne Retained.
 *   <li> 2001-04-16, cK, An vecmath/Transform3D problematik angepasst.
 * </ul>
 *
 * @version $Revision: 1.1.1.1 $, $Date: 2001/04/27 14:10:36 $
 *
 * @author cK, $Author: koestlin $
 */
class TGroup : public Group {
  public:
    /** Erzeugt einen neue Transformgruppe.
     *
     * @parm _init createRetained-Workaround.
     */
    TGroup() : Group() {
      RCTransform3D* help = new RCTransform3D();
      setTransform(help);
      help->releaseReference();
    }

    void accept(Visitor* v) {
      v->visit(this);
    }

    /** Liefert die Transform3D. Mit dieser ist so zu verfahren, wie mit
     * SG-Objecten ueblich. Readonly und releaseReference.
     *
     * @return RCTransform3D transformation.
     */
    virtual RCTransform3D* getTransform() {
      return(transform.get());
    }

    /** SG-typisches setzten.
     *
     * Die Transformation muss vom rufer per releaseReference zerstoehrt
     * werden. Einmal in den Szenegraphen gegeben, ist das Object
     * bestenfalls noch readonly, muss aber nicht mehr unbedngt etwas mit
     * dem Object im SG zu tun haben. Die Aenderungen werden erst nach
     * einem update realisiert.
     *
     * @param t3d Transformation.
     */
    virtual void setTransform(RCTransform3D* t3d) {
      transform.set(t3d);
    }

    /** Per Value setzen. nachfolgende Aenderungen an t3d sind
     * garantiert wirkungslos!
     *
     * @param t3d Transform3D.
     */
    virtual void setTransform(Transform3D* t3d) {
      RCTransform3D* help = new RCTransform3D(t3d);
      setTransform(help);
      help->releaseReference();
    }

    std::string toString() {
      std::ostringstream out;
      out << "TGroup[" << getChildCount() << "]" << std::ends;
      std::string res(out.str());
      return(res);
    }

    /** Transformation die fuer alle Kinder der Gruppe eingesetzt wird. */
    UpdateObject<RCTransform3D> transform;

  protected:
    /** Raeumt auf. */
    virtual ~TGroup() {
    }

};


#endif // _TGroup_h_
