#ifndef _InfiniteBound_h_
#define _InfiniteBound_h_

#include <vecmath/bounds/Bound.h>
#include <vecmath/bounds/BoundVisitor.h>
#include <vecmath/Transform3D.h>

class InfiniteBound : public Bound {
public:
	InfiniteBound() {
	}

	virtual ~InfiniteBound() {
	}
	
	Bound* transform(Transform3D* t3d) {
		return(new InfiniteBound());
	}

	void accept(BoundVisitor* visitor) {
		visitor->visit(this);
	}

  std::string toString() {
    return("InfiniteBound");
  }

};

#endif // _InfiniteBound_h_
