#ifndef _RCTransform3D_h_
#define _RCTransform3D_h_

#include <vecmath/Transform3D.h>
#include <util/RefCountedObject.h>

/** Transformation die im Szenegraphen verwendet werden kann.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-04-16, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.3 $, $Date: 2001/06/05 10:02:41 $
 *
 * @author cK, $Author: koestlin $
 */
class RCTransform3D : public Transform3D, public RefCountedObject {
	public:
	/** Erzeugt eine auf ID-initialisierte Transformation. */
	RCTransform3D() : Transform3D() {
	}
	
	/** Erzeugt eine RC aus einer normalen Transformation.
	 *
	 * @param t3d Zu uebernehmende Transformation.
	 */
	RCTransform3D(Transform3D* t3d) : Transform3D(t3d) {
	}
	
 protected:
	/** Raeumt auf. */
	virtual ~RCTransform3D() {
	}
	
};

#endif // _RCTransform3D_h_
