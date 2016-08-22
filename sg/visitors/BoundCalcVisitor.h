#ifndef _BoundCalcVisitor_h_
#define _BoundCalcVisitor_h_

#include <lang/CleanUpObject.h>

#include <sg/nodes/Group.h>
#include <sg/nodes/TGroup.h>

#include <sg/visitors/Visitor.h>

#include <vecmath/bounds/Bound.h>
#include <vecmath/bounds/BoundsMerge.h>
#include <vecmath/bounds/EmptyBound.h>

/** Der Visitor ist dafuer zustaendig, vereinigungen von Bound den
 * Szenegraph hinaufzupropagieren.
 *
 * Jeder Knoten hat ein Bound oder 0.
 * 0 bedeutet dabei immer sichtbar, bzw. nie gecullt.
 *
 * <ul>
 *   <li> Gruppen bekommen die Vereinigung der Bounds all ihrer Kinder.
 *   <li> Transformgruppen bekommen die Vereinigung der Bounds aller ihrer
 *        Kinder, aber anschliessend wird noch gedreht.
 * </ul>
 *
 * Das Ergebnis der Vereinigungen wird in bound gespeichert.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-07-14, cK, Begonnen.
 * </ul>
 *
 * @version $Revision: 1.1 $ $Date: 2001/07/16 10:05:41 $
 *
 * @author cK $Author: koestlin $
 */
class BoundCalcVisitor : public Visitor {
	
public:
	/** Erzeugt den Visitor. */
	BoundCalcVisitor() {
	}

	/** Raeumt auf. */
	virtual ~BoundCalcVisitor() {
	}
	
	void visit(Group* group) {
		NodeListIterator* i = group->getChilds();
		CleanUpObject<NodeListIterator> cleaner(i);

    BoundsMerge merger;
 
		Bound* old = new EmptyBound();
    Bound* newOne = old;
		while (i->hasNext() == true) {
			Node* child = i->next();
			child->accept(this);
			
      newOne = merger.operate(old, child->getBound());
      delete(old);
      old = newOne;
		}
		group->setBound(newOne);
	}

	void visit(TGroup* tg) {
		visit((Group*)tg);
		RCTransform3D* transform = tg->getTransform();

//    Transform3D help;
//    help.set(transform);
//    Transform3D* res = help.invertAffine();
//
//		Bound* transformed = tg->getBound()->transform(res);
//    delete(res);
    Bound* transformed = tg->getBound()->transform(transform);
		tg->setBound(transformed);

		transform->releaseReference();
	}
	
	std::string toString() {
		return "BoundCalcVisitor.h";
	}

};

#endif // _BoundCalcVisitor_h_
