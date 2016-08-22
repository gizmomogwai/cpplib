#ifndef _Bounds_h_
#define _Bounds_h_

#include <sg/nodeComponents/NodeComponent.h>

#include <vecmath/Transform3D.h>

/** Oberklasse fuer alle Bounding-Objekte.
 *
 * Denkbar sind Bounding Boxes oder Bounding Spheres.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-11-24, cK, Created.
 *   <li> 2001-04-16, cK, an vecmath/Transform3D angepasst.
 * </ul>
 *
 * @todo was muessen da fuer operationen rein???
 * @todo implementieren :))
 *
 * @version $Revision: 1.2 $, $Date: 2001/06/05 10:02:41 $
 *
 * @author cK, $Author: koestlin $
 */
class Bounds : public NodeComponent {

  public:
//    /** Transformiert this. 
//     *
//     * @param t Transformation.
//     */
//    virtual void transform(Transform3D* t) = 0;

//    /** Transformiert eine Bounds und setzt sich auf das Ergebnis.
//     *
//     * @param b Bounds.
//     * @param t Transformation.
//     */
//    virtual void transform(Bounds* b, Transform3D* t) = 0;

};

#endif // _Bounds_h_
