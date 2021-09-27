#pragma once

#include <string>

#include <sg/SGObject.h>
#include <sg/math/RCTransform3D.h>
#include <vecmath/bounds/Bound.h>
#include <sg/visitors/Visitor.h>

class Group;

/** Oberklasse aller Elemente, die direkt in den Szenegraph gehaengt
 * werden.
 *
 * Es ist zu entscheiden, was hier alles als direktes attribut gefuehrt
 * werden sollte, und was generisch angehaengt werden soll.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-11-24, cK, Created.
 *   <li> 2001-03-08, cK, ohne Retained-Objecte.
 *   <li> 2001-04-04, cK, local2World.
 *   <li> 2001-04-05, cK, Bugs gefixed (vergessen bei get hochzuzaehlen).
 *   <li> 2001-04-16, cK, An vecmath/Transform3D problematik angepasst.
 * </ul>
 *
 * @version $Revision: 1.3 $, $Date: 2001/09/13 13:11:13 $
 *
 * @author cK, $Author: koestlin $
 */
class Node : public SGObject {

public:
    /** Erzeugt einen neuen Node.
     */
    Node();

    void accept(Visitor* v) {
      v->visit(this);
    }

    /** Setzt den Vater des Knotens.
     *
     * Der Vater darf nur einmal gesetzt werden, aussnahme ist setzen auf 0.
     *
     * @param g Vatergruppe.
     */
    virtual void setParent(Group* g);

    /** Haengt den Knoten aus dem SG aus. */
    virtual void detach();

    /** Setzt die local2World-Transformation.
     * Sollte normalerweise von einem Visitor aus verwendet werden.
     *
     * @param t3d Transformation, darf danach nicht mehr schreibend
     *        verwendet werden.
     */
    virtual void setLocal2World(RCTransform3D* t3d);

    /** Bequemlichkeitsmethode, um eine unrefgecountete
     * Transformation zu setzen.
     *
     * Vorsicht .. das ist definitiv per value.
     *
     * @param t3d Transform3D.
     */
    virtual void setLocal2World(Transform3D* t3d) {
      RCTransform3D* help = new RCTransform3D(t3d);
      setLocal2World(help);
      help->releaseReference();
    }

    /** Liefert die local2World-transformation.
     *
     * Ist sie nicht gesetzt, wird 0 geliefert.
     * Normalerweise sollte sie von einem Local2WorldVisitor gesetzt werden.
     *
     * @return Transform3D* sg-maessiges liefern.
     */
    virtual RCTransform3D* getLocal2World();

    /** Liefert eine StringRep.
     *
     * @return std::string Stringrep.
     */
    std::string toString();

    /** Vater des Knotens. */
    Group* parent;

    /** Setzt das Bound-Object.
     *
     * @param _bound Bound. Caller verliert den Besitz.
     */
    void setBound(Bound* _bound);

    /** Liefert das Bound-Object.
     *
     * @return Bound* Bound bleibt im Besitz des Nodes.
     */
    Bound* getBound() {
      return(bound);
    }

  protected:
    /** Virtueller Aufraeumer. */
    virtual ~Node();

  private:
    /** local2WorldTransformation. */
    RCTransform3D* local2World;

    /** BoundingObjekt des Knotens. */
    Bound* bound;
};
