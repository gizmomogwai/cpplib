#ifndef _SGObject_h_
#define _SGObject_h_

#include <string>
#include <map>

#include <sg/visitors/Visited.h>
#include <sg/visitors/Visitor.h>
#include <sg/visitors/CustomData.h>

#include <util/RefCountedObject.h>

/** Oberklasse aller Elemente die im Szenengraphen haengen, oder
 * von Leafs verwendet werden.
 *
 * Allgemein gilt fuer alle SG-Objecte folgendes:
 * <ul>
 *   <li> Set-Operationen:
 *   <ul>
 *     <li> Ab dem Setzen gehoert das Object dem SG. Dieser damit machen
 *          was er will.
 *     <li> Die Applikation sollte nicht mehr viel mit diesem Object
 *          machen, da sie nicht weiss, was mit diesem Object geschieht.
 *     <li> Die Applikation muss das Object mit releaseReference freigeben,
 *          wenn sie es nicht mehr benoetigt.
 *     <li> Auch wenn die Applikation eine reference auf das in den
 *          szenegraph hineingesetzte objekt behaelt werden aenderungen nur
 *          dann garantiert aufgenommen, wenn ein neuerliches setzen passiert.
 *   </ul>
 *   <li> Get-Operationen:
 *   <ul>
 *     <li> Alle Objecte, die aus dem Szenegraphen herausgeliefert werden,
 *          sind Referenzen auf die Originale, duerfen aber unter keinen
 *          Umstaenden veraendert werden! Lediglich ein read-only-zugriff
 *          ist erlaubt.
 *     <li> Dennoch muessen sie, wenn sie nicht mehr benoetigt werden per
 *          releaseReference freigegeben werden.
 *   </ul>
 * </ul>
 *
 * <p>
 * Es koennen CustomDaten an jedes Object gehangt werden. Diese Daten sind
 * vor allem fuer die Visitoren bestimmt. Mit dem Einhaengen der Daten
 * geht das DatenObject in den Besitz des SGObjects ueber. Die DatenObjecte
 * werden spaetestens im Destructor zerstoehrt.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-11-24, cK, Created.
 *   <li> 2001-03-08, cK, ohne retained.
 *   <li> 2001-07-05, cKgS, customData eingefuehrt.
 * </ul>
 *
 * @todo Die Objecthierarchie ist nicht gut so, wie sie momentan ist glaube ich ..
 *       bzw. benoetigt begruendung!
 *
 * @author cK, $Author: koestlin $
 *
 * @version $Revision: 1.5 $, $Date: 2001/09/13 13:11:12 $
 */
class SGObject : public Visited, public RefCountedObject {

  public:
    /** Erzeugt ein neues SGObject ohne customData. */
    SGObject();

    virtual void accept(Visitor* v) {
      v->visit(this);
    }

    /** Liefert ein StringRepraesentation von einem Knoten.
     *
     * @return std::string String.
     */
    virtual std::string toString() {
      return("SGObject");
    }

    /** Liefert customdata.
     *
     * Falls keine customData gesetzt sind 0.
     * Falls nicht gefunden werden kann 0.
     * Falls gefunden werden kann den value.
     *
     * @param key Schluessel, bleibt im Besitz des SGObjects.
     *
     * @return void* die Daten oder 0 falls nichts da.
     */
    void* getCustomData(void* key);

    /** Setzt, oder aendert die Daten fuer einen key.
     *
     * Wenn fuer den Key schon ein wert gesetzt ist, wird dieser
     * wert per delete zerstoehrt.
     *
     * @param key Key.
     * @param value Wert, geht in den Besitz des SGObjects ueber.
     */
    void setCustomData(void* key, CustomData* value);

  protected:
    /** Virtueller Deconstructor. */
    virtual ~SGObject();

    /** CustomDaten. */
    std::map<void*, CustomData*>* customData;

};

#endif // _SGObject_h_
