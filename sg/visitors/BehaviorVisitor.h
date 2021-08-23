#ifndef _BehaviorVisitor_h_
#define _BehaviorVisitor_h_

#include <sg/visitors/Visitor.h>

/** Besucher der alle Behaviors im Graphen evaluiert.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-01-6, cKgS, Created.
 * </ul>
 *
 * @version $Revision: 1.1.1.1 $, $Date: 2001/04/27 14:10:36 $
 *
 * @author cKgS, $Author: koestlin $
 */
class BehaviorVisitor : public Visitor {

  public:
    /** Erzeugt den Visitor. */
    BehaviorVisitor() {
    }

    /** Raeumt auf. */
    virtual ~BehaviorVisitor() {
    }

    void visit(SGObserver* s);

    void visit(Group* g);

    void visit(TGroup* tg);

    void visit(Behavior* b);

    std::string toString() {
      return("BehaviorVisitor");
    }

};

#endif // _BehaviorVisitor_h_
