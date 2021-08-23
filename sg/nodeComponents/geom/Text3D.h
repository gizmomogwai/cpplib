#ifndef _Text3D_h_
#define _Text3D_h_

#include <string>

#include <sg/nodeComponents/geom/Geometry.h>

#include <sg/visitors/Visitor.h>

/** Geometrie einer 3d-schrift.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-02-11, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.1.1.1 $, $Date: 2001/04/27 14:10:36 $
 *
 * @author cK, $Author: koestlin $
 */
class Text3D : public Geometry {

  public:
    /** Erzeugt einen neuen 3d-text. 
     */
    Text3D(std::string _text) : text(_text) {
    }

    void accept(Visitor* v) {
      v->visit(this);
    }

    /** Text, der dargestellt werden soll.
     * Eignetlich private,  aber fuer visitoren public.
     */
    std::string text;

};


#endif // _Text3D_h_
