#ifndef _Visitor_h_
#define _Visitor_h_

#include <string>

class Appearance;
class Behavior;
class Geometry;
class Group;
class SwitchGroup;
class Root;
class TGroup;
class FogGroup;
class LightGroup;
class ProjectionGroup;
class TriangleArray;
class IndexedTriangleArray;
class InterleavedTriangleArray;
class IndexedInterleavedTriangleArray;
class Leaf;
class Node;
class SGObject;
class SGObserver;
class Shape3D;
class OrientedShape3D;
class TeapotGeometry;
class Texture;
class Text3D;
class ImplicitSGNode;

/** Schnittstellt fuer NodeVisitoren (DesignPattern Visitor).
 *
 * Das sollte die Oberklasse aller Visitoren des Szenegraphen sein.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *  <li> 2000-11-24, cK, Created.
 *  <li> 2000-11-25, cK, Commented.
 *  <li> 2001-02-14, cK, OrientedShape3d.
 *  <li> 2001-04-06, cK, Defaultimplementierungen veraendert.
 *  <li> 2001-04-16, cK, Um InterleavedArrays erweitert.
 *  <li> 2001-05-02, cK, Neue defaults fuer geometrien.
 * </ul>
 *
 * @version $Revision: 1.5 $, $Date: 2001/07/05 13:27:23 $
 *
 * @author cK, $Author: koestlin $
 */
class Visitor {
  public:
    /** Virtueller Deconstructor. */
    virtual ~Visitor() {
    }

    /** Besucht einen Szenebetrachter.
     *
     * @param observer Betrachter.
     */
    virtual void visit(SGObserver* observer) {
      visit((Group*)observer);
    }

    /** Besucht ein SGObject.
     *
     * @param sgo SceneGraphObject.
     */
    virtual void visit(SGObject* sgo) {}

    /** Besucht einen Node-Knoten.
     *
     * @param node Zu besuchender Node.
     */
    virtual void visit(Node* node) {}

    /** Besucht einen Group-Knoten.
     *
     * @param g Zu besuchende Gruppe.
     */
    virtual void visit(Group* g);

    /** Besucht eine SwitchGruppe.
     */
    virtual void visit(SwitchGroup* g) {
      visit((Group*)g);
    }
    /** Besucht eine Rootgruppe.
     *
     * In der Defaultimplementierung wird der
     * Knoten wie eine normale Gruppe behandelt.
     *
     * @param r Rootgruppe.
     */
    virtual void visit(Root* r) {
      visit((Group*)r);
    }

    /** Besucht einen TGroup-Knoten.
     *
     * In der Defaultimplementierung wird der
     * Knoten wie eine normale Gruppe behandelt.
     *
     * @param TGroup g Transformationsgruppe.
     */
    virtual void visit(TGroup* tg) {
      visit((Group*)tg);
    }

    /** Besucht einen FogGroup-Knoten.
     *
     * In der Defaultimplementierung wird der
     * Knoten wie eine normale Gruppe behandelt.
     *
     * @param g Zu besuchende Gruppe.
     */
    virtual void visit(FogGroup* g) {
      visit((Group*)g);
    }

    /** Besucht eine Lichtgruppe.
     *
     * In der Defaultimplementierung wird der
     * Knoten wie eine normale Gruppe behandelt.
     *
     * @param lg Lichtgruppe.
     */
    virtual void visit(LightGroup* lg) {
      visit((Group*)lg);
    }

    /** Besucht einen ProjectionGroup-Knoten.
     *
     * In der Defaultimplementierung wird der
     * Knoten wie eine normale Gruppe behandelt.
     *
     * @param g Zu besuchende Gruppe.
     */
    virtual void visit(ProjectionGroup* g) {
      visit((Group*)g);
    }

    /** Besucht einen Leaf.
     *
     * @param l Leaf.
     */
    virtual void visit(Leaf* l) {}

    /** Besucht einen Shape3D
     *
     * @param s3d Shape3d.
     */
    virtual void visit(Shape3D* s3d);

    /** Besucht ein Oriented Shape3D.
     *
     * Die Defaultimplementierung behandelt OrientedShape3D wie Shape3D.
     *
     * @param os3d Das Shape.
     */
    virtual void visit(OrientedShape3D* os3d) {
      visit((Shape3D*)os3d);
    }

    /** Falls eine Geometrie besucht wird.
     *
     * @param geometry Die Geometry.
     */
    virtual void visit(Geometry* geometry) {}

    /** Falls eine TeapotGeometrie besucht wird.
     *
     * @param teapot Der Teapot.
     */
    virtual void visit(TeapotGeometry* teapot) {
      visit((Geometry*)teapot);
    }

    /** Falls ein TriangleArray besucht werden soll.
     *
     * @param tArray TriangleArray-Geometrie.
     */
    virtual void visit(TriangleArray* tArray) {
      visit((Geometry*)tArray);
    }


    /** Falls ein IndexedTriangleArray besucht werden soll.
     *
     * @param itArray IndexedTriangleArray.
     */
    virtual void visit(IndexedTriangleArray* itArray) {
      visit((TriangleArray*)itArray);
    }

    /** Falls ein InterleavedTriangleArray besucht werden soll.
     *
     * @param array InterleavedTriangleArray.
     */
    virtual void visit(InterleavedTriangleArray* array) {
      visit((TriangleArray*)array);
    }

    /** Falls ein IndexedInterleaedTriangleArray besucht werden soll.
     *
     * @param array IndexedInterleavedTriangleArray.
     */
    virtual void visit(IndexedInterleavedTriangleArray* array) {
      visit((InterleavedTriangleArray*)array);
    }

    /** Besucht eine 3d-schriftgeometrie
     *
     * @param text3d 3dschrift.
     */
    virtual void visit(Text3D* text3d) {}

    /** Falls eine Appearance besucht wird.
     *
     * @param Die Appearance.
     */
    virtual void visit(Appearance* app) {}

    /** Falls eine Textur besucht wird.
     *
     * @param texture Textur.
     */
    virtual void visit(Texture* texture) {}

    /** Besucht ein Behavior.
     *
     * @param b Das Behavior.
     */
    virtual void visit(Behavior* b) {}

    /** Besucht einen Impliciten Knoten.
     *
     * @param node Knoten.
     */
    virtual void visit(ImplicitSGNode* node) {}

    /** tostringmethode der Visitoren.
     *
     * @return std::string Beschreibung des Visitors.
     */
    virtual std::string toString() = 0;

};

#endif // _Visitor_h_
