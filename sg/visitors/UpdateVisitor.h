#ifndef _UpdateVisitor_h_
#define _UpdateVisitor_h_

#include <pragmaincludes.h>

#include <sg/visitors/Visitor.h>


/** Visitor, der in den Retained-Objekten vorgenommene Aenderungen in den 
 * Szenegraphen integriert.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *  <li> 2000-11-24, cK, Created.
 *  <li> 2000-11-25, cK, Commented.
 *  <li> 2001-02-27, cK, Appearance update um RenderingAttributes erweitert.
 *  <li> 2001-04-16, cK, Um InterleavedArrays erweitert.
 *  <li> 2001-04-23, cK, Gerd Frustum integriert.
 *  <li> 2001-04-27, cK, Root (mit breite und hoehe ausgewertet).
 *  <li> 2001-05-02, cK, An Shape3d.addGeometry angepasst.
 *  <li> 2001-07-05, cK, An neue Texture-schnittstelle angepasst.
 * </ul>
 *
 * @todo FogGroup richtig updaten!
 *
 * @version $Revision: 1.3 $, $Date: 2001/07/05 09:37:48 $
 *
 * @author cK, $Author: koestlin $
 */
class UpdateVisitor : public Visitor {

  public:
    /** Erzeugt einen neuen Visitor, der alles macht, was zu einem update
	 * noetig ist.
     */
    UpdateVisitor();

    /** Raeumt auf. */
    virtual ~UpdateVisitor();

    void visit(Root* root);

    void visit(SGObserver* observer);

    void visit(SGObject* sgo);
    
    void visit(Node* n);

    void visit(Group* g);

    void visit(TGroup* g);

    void visit(Leaf* leaf);

    void visit(Shape3D* shape3d);

    void visit(TriangleArray* tArray);

    void visit(IndexedTriangleArray* itArray);

    void visit(InterleavedTriangleArray* array);

    void visit(IndexedInterleavedTriangleArray* array);

    void visit(Appearance* app);

    void visit(Texture* texture);

    std::string toString() {
      return("UpdateVisitor");
    }
  private:
    /** Breite des Canvases. */
    int width;

    /** Hoehe des Canvases. */
    int height;
			
};

#endif // _UpdateVisitor_h_
