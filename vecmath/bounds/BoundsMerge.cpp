#include <vecmath/bounds/BoundsMerge.h>

#include <assert.h>

#include <vecmath/bounds/EmptyBound.h>
#include <vecmath/bounds/InfiniteBound.h>
#include <vecmath/bounds/Bound.h>
#include <vecmath/bounds/AabbBound.h>

#define BoundsMergeMin(a, b) (a < b ? a : b)
#define BoundsMergeMax(a, b) (a > b ? a : b)

void BoundsMerge::visit(InfiniteBound* _infiniteBound) {
	boundTypes[idx++] = INF;
}

void BoundsMerge::visit(AabbBound* _aabb) {
	boundTypes[idx++] = AABB;
}

void BoundsMerge::visit(EmptyBound* _aabb) {
	boundTypes[idx++] = EMPTY;
}


Bound* BoundsMerge::operate(Bound* b1, Bound* b2) {
  idx = 0;
	if (b1 == 0) {
		boundTypes[idx++] = INF;
	} else {
		b1->accept(this);
	}

	if (b2 == 0) {
		boundTypes[idx++] = INF;
	} else {
		b2->accept(this);
	}

	assert(boundTypes[0] != UNDEF);
	assert(boundTypes[1] != UNDEF);
		
	// jetzt tabelle allerdings nur dreieck da reigenfolge des merges egal
	// sein sollte
	//          1     2    3
 	//   b2\b1 EMPTY INF  AABB
  //  EMPTY   4    5    6
	//  INF     7    8    9
	//  AABB    10   11   12
 	int tab = convertBoundTypes();
		
  Bound* res = 0;
	switch (tab) {
		case 4:
			res = operate((EmptyBound*)b1, (EmptyBound*)b2);
			break;
		case 7:
			res = operate((EmptyBound*)b1, (InfiniteBound*)b2);
			break;
		case 10:
			res = operate((EmptyBound*)b1, (AabbBound*)b2);
			break;

		case 5:
			res = operate((EmptyBound*)b2, (InfiniteBound*)b1);
			break;
		case 8:
			res = operate((InfiniteBound*)b1, (InfiniteBound*)b2);
			break;
		case 11:
			res = operate((InfiniteBound*)b1, (AabbBound*)b2);
			break;

    
 		case 6:
			res = operate((EmptyBound*)b2, (AabbBound*)b1);
			break;
 		case 9:
			res = operate((InfiniteBound*)b2, (AabbBound*)b1);
			break;
 		case 12:
			res = operate((AabbBound*)b2, (AabbBound*)b1);
			break;

    default:
			throw(Exception("schmogg", __FILE__, __LINE__));
	}
  return(res);
}

Bound* BoundsMerge::operate(EmptyBound* b1, EmptyBound* b2) {
  return(new EmptyBound());
}

Bound* BoundsMerge::operate(EmptyBound* b1, InfiniteBound* b2) {
  return(new InfiniteBound());
}

Bound* BoundsMerge::operate(EmptyBound* b1, AabbBound* b2) {
  return(new AabbBound(b2));
}

Bound* BoundsMerge::operate(InfiniteBound* b1, InfiniteBound* b2) {
	return(new InfiniteBound());
}

Bound* BoundsMerge::operate(InfiniteBound* b1, AabbBound* b2) {
	return(new InfiniteBound());
}

Bound* BoundsMerge::operate(AabbBound* b1, AabbBound* b2) {
	Point3f minP;
	Point3f* b1p = b1->getMin();
	Point3f* b2p = b2->getMin();
	minP.x = BoundsMergeMin(b1p->x, b2p->x) - 1;
	minP.y = BoundsMergeMin(b1p->y, b2p->y) - 1;
	minP.z = BoundsMergeMin(b1p->z, b2p->z) - 1;
	
	Point3f maxP;
	b1p = b1->getMax();
	b2p = b2->getMax();
	maxP.x = BoundsMergeMax(b1p->x, b2p->x) + 1;
	maxP.y = BoundsMergeMax(b1p->y, b2p->y) + 1;
	maxP.z = BoundsMergeMax(b1p->z, b2p->z) + 1;
	
	return(new AabbBound(&minP, &maxP));
}

