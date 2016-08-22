#ifndef _BoundingBox_h_
#define _BoundingBox_h_

#include <sg/Bounds.h>
#include <vecmath/Point3f.h>
#include <vecmath/Transform3D.h>


/** Eine BoundingSphere
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *  <li> 2001-05-29, gS, Created
 * </ul>
 *
 * @version $Revision: 1.3 $, $Date: 2001/06/28 17:08:09 $
 *
 * @author gS, $Author: schaefer $
 */
class BoundingBox : public Bounds {

  public:

    /** Uninitialisierte BOundingSphere. */
    BoundingBox();

    /** Initialisiert BoundingBox mit obere und untere Ecke
     * Ecken gehen in Besitz der BBox ueber und muessen von
     * ihr befreit werden.
     *
     * @param lower untere Ecke der BBox
     * @param upper obere Ecke der BBox
     */
    BoundingBox(Point3f* lower, Point3f* upper);

    /** Raeumt auf. */
	  virtual ~BoundingBox();

		//    void transform(Transform3D* t);
		
		//    void transform(Bounds* b, Transform3D* t);
		
		//    void merge(Bounds* b);
		
		//     bool intersect(Bounds* b);
		
    /** setzt den oberen Punkte der BBox */
    void setUpper(Point3f* _upper) {
      
      upper = _upper;
    }

    /** setzt den unteren Punkte der BBox */
    void setLower(Point3f* _lower) {
      
      lower = _lower;
    }

    /** untere Ecke der BBox */
    Point3f* lower;

    /** untere Ecke der BBox */
    Point3f* upper;
};

#endif // _BoundingBox_h_
