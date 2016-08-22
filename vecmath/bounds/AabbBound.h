#ifndef _AabbBound_h_
#define _AabbBound_h_

#include <vecmath/Point3f.h>
#include <vecmath/bounds/Bound.h>
#include <vecmath/bounds/BoundVisitor.h>
#include <vecmath/Transform3D.h>


class AabbBound : public Bound {

public:

  AabbBound(AabbBound* a);

	/** Erzeugt neue Aabb.
	 *
	 * @param _minP Minimalpunkt, bleibt im Besitz des Callers.
	 * @param _maxP Maximalpunkt, bleibt im Besitz des Callers.
	 */
	AabbBound(Point3f* _minP, Point3f* _maxP);


	/** Raeumt auf. */
	virtual ~AabbBound() {
	}

	void accept(BoundVisitor* visitor) {
		visitor->visit(this);
	}

	/** Liefert Minimalpunkt.
	 *
	 * @return Point3f* Punkt bleibt im Besitz von AabbBound.
	 */
	Point3f* getMin() {
		return(&minP);
	}
	
	/** Liefert Maximalpunk.
	 *
	 * @return Point3f* Punkt bleibt im Besitz von AabbBound.
	 */
	Point3f* getMax() {
		return(&maxP);
	}

	Bound* transform(Transform3D* t3d);

  std::string toString();
	
private:
	
  void integrateValues(float x, float y, float z, 
                       Transform3D* t3d, 
                       Point3f* newMin, Point3f* newMax);

	Point3f minP;
	Point3f maxP;

};

#endif
