#ifndef _BoundsMerge_h_
#define _BoundsMerge_h_

#include <vecmath/bounds/BoundVisitor.h>

class Bound;

/** Mergeoperation auf bounds.
 */
class BoundsMerge : public BoundVisitor {
	
public:
	
	BoundsMerge() {
		boundTypes = new BoundType[2];
	}
	
	virtual ~BoundsMerge() {
		delete[](boundTypes);
	}
	
	void visit(InfiniteBound* _infiniteBound);

	void visit(AabbBound* _aabb);

	void visit(EmptyBound* _empty);
	
	virtual Bound* operate(Bound* b1, Bound* b2);

  virtual Bound* operate(EmptyBound* b1, EmptyBound* b2);
  virtual Bound* operate(EmptyBound* b1, InfiniteBound* b2);
  virtual Bound* operate(EmptyBound* b1, AabbBound* b2);

	virtual Bound* operate(InfiniteBound* b1, InfiniteBound* b2);
	virtual Bound* operate(InfiniteBound* b1, AabbBound* b2);

  virtual Bound* operate(AabbBound* b1, AabbBound* b2);

	
private:

	int convertBoundTypes() {
		int res = 0;
		int fac = 1;
		for (int i=0; i<2; i++) {
			res += fac * boundTypes[i];
			fac *= 3;
		}
		return(res);
	}
	
	enum BoundType { UNDEF=0, EMPTY=1, INF=2, AABB=3 };

	BoundType* boundTypes;
	int idx;
};


#endif // _BoundsMerge_h_
