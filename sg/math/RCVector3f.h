#ifndef _RCVector3f_h_
#define _RCVector3f_h_

#include <util/RefCountedObject.h>
#include <vecmath/Vector3f.h>


/** 3-D Vector der Referenzcounted ist und somit in den Szenegraphen
 * integriert werden kann.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-04-15, cK, Auf vecmath/Vector3f aufbauend.
 * </ul>
 *
 * @version $Revision: 1.2 $, $Date: 2001/05/28 09:40:54 $
 *
 * @author cK, $Author: koestlin $
 */
class RCVector3f : public Vector3f, public RefCountedObject {
};

#endif // _RCVector3f_h_
