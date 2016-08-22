#ifndef _OrientedShape3D_h_
#define _OrientedShape3D_h_

#include <sg/nodes/Shape3D.h>

/** Orientiertes Shape (dreht sich immer zur aktuellen Kamera).
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-02-14, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.2 $, $Date: 2001/06/27 13:48:07 $
 *
 * @author cK, $Author: koestlin $
 */
class OrientedShape3D : public Shape3D {

 public:
	/** Erzeugt ein neues OrientedShape3D.
	 *
	 * @param geom Geometrie.
	 * @param app Appearance.
	 */
	OrientedShape3D(Geometry* geom, Appearance* app) : Shape3D(geom, app) {
	}

  /** Erzeugt ein neues unbesetzes OrientedShape3D.
   */
  OrientedShape3D() : Shape3D() {
  }

  /** Raeumt auf. */
	virtual ~OrientedShape3D() {
	}
	
	void accept(Visitor* v) {
		v->visit(this);
	}

};

#endif // _OrientedShape3D_h_
