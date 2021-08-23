#ifndef _PrintVisitor_h_
#define _PrintVisitor_h_

#include <string>

#include <sg/visitors/Visitor.h>

/** Visitor, der den Scenengraphen auf cout ausgibt.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-11-25, cK, Created.
 *   <li> 2001-03-02, cKgS, SGObserver hinzugefuegt .. 
 *        muss avber noch besser gemacht werden.
 *   <li> 2001-05-02, cK, An shape3d.addGeometry angepasst.
 * </ul>
 *
 * @version $Revision: 1.4 $, $Date: 2001/08/06 15:48:52 $
 *
 * @author cK, $Author: koestlin $
 */
class PrintVisitor : public Visitor {
   
  public:
    /** Erzeugt den Visitor. */
    PrintVisitor();

    /** Raeumt auf. */
    virtual ~PrintVisitor();

    void visit(SGObserver* observer);

    void visit(Node* n);

    void visit(Group* g);

    void visit(TGroup* g);

    void visit(Leaf* l);

    void visit(Shape3D* s3d);

    void visit(Appearance* app);

    void visit(Geometry* geom);

    void visit(Texture* texture);    

    void visit(Behavior* b);

    std::string toString() {
      return("PrintVisitor");
    }

  private:
    /** Prefix fuer eine Zeile, wird bei durchgehen durch den Graphen
		 * veraendert. 
		 */ 
    std::string prefix;

};

#endif // _PrintVisitor_h_
