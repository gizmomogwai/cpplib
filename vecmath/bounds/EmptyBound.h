#ifndef _EmptyBound_h_
#define _EmptyBound_h_

#include <vecmath/bounds/Bound.h>
#include <vecmath/bounds/BoundVisitor.h>
#include <vecmath/Transform3D.h>

class EmptyBound : public Bound {
public:
	EmptyBound() {
	}

	virtual ~EmptyBound() {
	}
	
	Bound* transform(Transform3D* t3d) {
		return(new EmptyBound());
	}

	void accept(BoundVisitor* visitor) {
		visitor->visit(this);
	}

  std::string toString() {
    return("EmptyBound");
  }

};

#endif // _EmptyBound_h_
