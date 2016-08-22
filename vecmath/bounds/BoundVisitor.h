#ifndef _BoundVisitor_h_
#define _BoundVisitor_h_

class EmptyBound;
class InfiniteBound;
class AabbBound;

class BoundVisitor {

public:
    virtual ~BoundVisitor() {}
    
	virtual void visit(EmptyBound* bound) = 0;

	virtual void visit(InfiniteBound* bound) = 0;
	
	virtual void visit(AabbBound* bound) = 0;

};

#endif // _BoundVisitor_h_
