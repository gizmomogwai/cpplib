#ifndef _BoundingSphere_h_
#define _BoundingSphere_h_

#include <sg/Bounds.h>
#include <sg/BoundingBox.h>
#include <vecmath/Point3f.h>
#include <vecmath/Transform3D.h>


/** Eine BoundingSphere
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *  <li> 2000-03-30, gS, Created
 *  <li> 2001-04-23, cK, An vecmath angepasst ... aufgeraeumt.
 * </ul>
 *
 * @version $Revision: 1.4 $, $Date: 2001/06/28 17:08:09 $
 *
 * @author gS, $Author: schaefer $
 */
class BoundingSphere : public Bounds {

 public:

	/** Uninitialisierte BOundingSphere. */
	BoundingSphere();

	/** Initialisiert BoundingSphere mit Mittelpunkt und Radius
	 *
	 * @param center Mittelpunkt der Kugel, bleibt im Besitz des Callers.
	 * @param radius Radius der Kugel.
	 */
	BoundingSphere(Point3f* center, float radius);

  
  /** Macht eine, die BBox umschliessende BoundingSphere
	 *
	 * @param bbox die BoundingBox
	 */
	BoundingSphere(BoundingBox* bbox);

	
  /** Copy-Konstruktor
	 *
	 * @param bSphere BoundingSphere, bleibt im Besitz des Callers.
	 */
	BoundingSphere(BoundingSphere *bSphere);

	/** Raeumt auf. */
	virtual ~BoundingSphere();

	/** Transformiert this mit der angegebenen Transformation.
	 *
	 * @param t Transformation.
	 */
	void transform(Transform3D* t);


  /**
   * liefert eine StringRepraesentation der BSphere
   *
   * @return String
   */
  std::string toString() {

    std::ostringstream help;
    help << "BoundingSphere(" << center->toString() << ", " << radius << ")" << std::ends;
    std::string res = std::string(help.str());
    return(res);
  }

	//    void transform(Bounds* b, Transform3D* t);

	//	void merge(Bounds* b);

	//	bool intersect(Bounds* b);

  /** der Mittelpunkt der Kugel */
	Point3f* center;

	/** der Radius der Kugel */
	float radius;
};

#endif // _BoundingSphere_h_
