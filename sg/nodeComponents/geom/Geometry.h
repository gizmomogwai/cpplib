#ifndef _Geometry_h_
#define _Geometry_h_

#include <sg/nodeComponents/NodeComponent.h>
#include <sg/visitors/Visited.h>
#include <sg/visitors/Visitor.h>

/** Oberklasse aller Geometrien.
 *
 * Hierbei bezeichnet Geometrie zumindest Coordinaten mit potentiell
 * texturcoordinaten/farben/normalen. 
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-11-28, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.2 $, $Date: 2001/08/08 14:32:20 $
 *
 * @author cK, $Author: schaefer $
 */
class Geometry : public NodeComponent  {

 public:
	void accept(Visitor* v) = 0;

 protected:

	/** Raumt mit der Geometrie auf. */
	virtual ~Geometry() {}
};

#endif // _Geometry_h_

