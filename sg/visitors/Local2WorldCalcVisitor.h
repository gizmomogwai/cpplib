#ifndef _Local2WorldCalcVisitor_h_
#define _Local2WorldCalcVisitor_h_

#include <sg/visitors/Visitor.h>

#include <sg/math/MatrixStack.h>

/** Visitor, der die local2World transformationen in einem 
 * Szenegraphen berechnet.
 *
 * Es werden nur Nodes besucht, NodeComponents werden 
 * logischerweise ignoriert.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-04-03, cK, Created.
 *   <li> 2001-04-16, cK, An vecmath/Transform3D problematik angepasst.
 * </ul>
 *
 * @author cK, $Author: koestlin $
 *
 * @version $Revision: 1.2 $, $Date: 2001/06/05 10:02:42 $
 */
class Local2WorldCalcVisitor : public Visitor {

 public:
	/** Erzeugt den Visitor. */
	Local2WorldCalcVisitor() {
	}
	
	/** Virtueller Deconstructor. */
	virtual ~Local2WorldCalcVisitor() {
	}

	void visit(Root* r);

	void visit(SGObserver* observer);
      
	void visit(Node* node);

	void visit(Group* g);

	void visit(TGroup* tg);
      
	void visit(FogGroup* g) {
		visit((Group*)g);
	}

	void visit(LightGroup* lg) {
		visit((Group*)lg);
	}

	void visit(ProjectionGroup* g) {
		visit((Group*)g);
	}

	void visit(Leaf* l) {
		visit((Node*)l);
	}

	void visit(Shape3D* s3d) {
		visit((Node*)s3d);
	}

	void visit(Behavior* b) {
		visit((Node*)b);
	}

	std::string toString() {
		return("Local2WorldCalcVisitor");
	}
 private:

	/** Der oglaehnliche MatrixStack. */
	MatrixStack matrixStack;

};

#endif // _Local2WorldCalcVisitor_h_
