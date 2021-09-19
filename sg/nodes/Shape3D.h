#ifndef _Shape3D_h_
#define _Shape3D_h_

#include <sg/nodes/Leaf.h>

class Appearance;
#include <sg/nodeComponents/geom/Geometry.h>

#include <sg/visitors/Visitor.h>

#include <util/UpdateObject.h>
#include <util/Iterator.h>
#include <vector>


/** Liste mit Geometrien. Wird benoetigt, um
 * eine RefCountedListe anzubieten, die RefCounted Objecte verwaltet.
 *
 * Um die Klasse mit noch mehr funktionalitaet anzureichern (damit sie nicht
 * so mickrig ist) koennte man hier push_back um die RefCountingSemantik
 * anreichern.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-05-02, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.4 $, $Date: 2001/08/06 16:07:20 $
 *
 * @author cK, $Author: koestlin $
 */
class GeometryList : public std::vector<Geometry*>, public RefCountedObject {

  public:
    /** Erzeugt eine neue Liste. */
    GeometryList() {
    }

  protected:
    /** Raeumt die Referencen in der Liste auf. */
    virtual ~GeometryList() {
      std::vector<Geometry*>::iterator i = begin();
      while (i != end()) {
        (*i)->releaseReference();
        i++;
      }
    }
};

/** Klasse die als Iterator fuer GeometryLsiten dient.
 *
 * Der Iterator kann mit einer GeometryList initialisiert werden
 * und uebernimmt die reference. Im Destructor gibt er sie frei.
 * Man kann also new GeometryListIterator(geom.get()); delete()
 * schreien ohne eine leak zu produzieren.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-05-02, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.4 $, $Date: 2001/08/06 16:07:20 $
 *
 * @author cK, $Author: koestlin $
 */
class GeometryListIterator : public Iterator<Geometry*> {
  public:
    /** Erzeugt einen neuen Iterator.
     *
     * @param _list Liste, ueber die iteriert werden soll.
     */
    GeometryListIterator(GeometryList* _list) {
      list = _list;
      if (list == 0) {
        throw Exception("list == 0");
      }

      i = list->begin();
    }

    /** Raeumt auf (zaehlt rteference herunter. */
    virtual ~GeometryListIterator() {
      if (list != 0) {
        list->releaseReference();
        list = 0;
      }
    }

    bool hasNext() {
      return(i != list->end());
    }

    Geometry* next() {
      return(*i++);
    }

  private:
    /** Liste. */
    GeometryList* list;

    /** stl-Iteartor. */
    GeometryList::iterator i;

};


/** Oberklasse aller Leafs, die Geometrie mit Material darstellen wollen.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-01-06, cK, Commented.
 *   <li> 2001-03-08, cK, Ohne Retained.
 *   <li> 2001-05-02, cK, addGeometry hinzugefuegt.
 * </ul>
 *
 * @version $Revision: 1.4 $, $Date: 2001/08/06 16:07:20 $
 *
 * @author cK, $Author: koestlin $
 */
class Shape3D : public Leaf {

  public:
    /** Erzeugt ein neues Shape3d mit einer Geometrie und einem Material.
     *
     * Mit dem Material und der Appearance ist SG-Objectmaessig zu
     * verfahren.
     *
     * @param geom Geometrie.
     * @param m Material.
     */
    Shape3D(Geometry* _geom, Appearance* _app);

    /** Erzeugt ein leeres Shape3d.
     */
    Shape3D();

    void accept(Visitor* v);

    /** Fuegt eine Geometrie hinzu.
     *
     * SG-maessig.
     *
     * @param geom Geometrie.
     */
    void addGeometry(Geometry* geom);

    /** Setzt die Erste Geometry.
     *
     * SG-maessiges Setzen.
     *
     * @param geom Geometry.
     */
    void setFirstGeometry(Geometry* geom);

    /** Setzt das Material.
     *
     * SG-maessiges Setzen.
     *
     * @param m Material.
     */
    void setAppearance(Appearance* m);

    /** Liefert die Appearance.
     *
     * SG-maessiges liefern.
     *
     * @return Appearance* app.
     */
    Appearance* getAppearance();

    /** Liefert die erste Geometrie.
     *
     * SG-maessiges liefern.
     *
     * @return Geometry* Die Geometry.
     */
    Geometry* getFirstGeometry();

    /** Liefert einen Iterator mit allen Geometrien.
     *
     * @return GeometryListIterator* Iterator.
     */
    GeometryListIterator* getGeometries() {
      return(new GeometryListIterator(geom.get()));
    }

    /** Liefert die Anzahl von Geometrien.
     *
     * @return int Anzahl von Geometrien.
     */
    int getGeometryCount() {
      GeometryList* list = geom.get();
      int res = list->size();
      list->releaseReference();
      return(res);
    }

    /** Liefert eine StringRep.
     *
     * @return std::string Stringrep.
     */
    std::string toString();

    /** Die Geometrie. Sollte eignetlich nur fuer Visitoren
     * und deren unterklassen sichtbar sein.
     */
    UpdateObject<GeometryList> geom;

    /** Material. Sollte eigentlich nur fuer Visitoren und
     * deren Unterklassen sichtbar sein.
     */
    UpdateObject<Appearance> app;

  protected:
    /** Raeumt auf. */
    virtual ~Shape3D();

  private:
    /** Wird beim hinzufuegen von geometrie verwendet.
     *
     * 2 Faelle:
     * Fall 1 update schon durchgefuehrt (d.h. currentOnes != 0) und newOnes == 0.
     *   alle daten werden einfach kopiert und newOnes wird dem udpateobject bekanntgegeben.
     * Fall 2 update noch nciht durchgefuehrt. newOnes enthaelt schon die Daten, und evtl. noch mehr
     *   deshalb nichts machen.
     */
    GeometryList* copyAndSet(GeometryList* currentOnes,
                             GeometryList* newOnes);

};

#endif // _Shape3D_h_
