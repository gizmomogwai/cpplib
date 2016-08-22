#ifndef _Bound_h_
#define _Bound_h_

#include <string>

class BoundsMerge;
class Transform3D;
class BoundVisitor;

class Bound {

public:
	Bound() {
	}

	virtual ~Bound() {
	}

	virtual void accept(BoundVisitor* visitor) = 0;

	virtual Bound* transform(Transform3D* t3d) = 0;

  virtual std::string toString() = 0;

};

#endif // _Bound_h_
