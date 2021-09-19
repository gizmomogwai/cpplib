#ifndef _Appearance_h_
#define _Appearance_h_

#include <sg/nodeComponents/NodeComponent.h>

#include <sg/nodeComponents/app/Texture.h>
#include <sg/nodeComponents/app/Material.h>
#include <sg/nodeComponents/app/TexGen.h>
#include <sg/nodeComponents/app/RenderingAttributes.h>
#include <sg/nodeComponents/app/PolygonAttributes.h>

#include <sg/visitors/Visitor.h>

#include <util/UpdateObject.h>

/** Appearance eines Shape3ds.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-12-03, cK, Created.
 *   <li> 2001-01-04, cK, Multitex integriert.
 *   <li> 2001-02-27, cK, Um RenderingAttribute erweitert.
 *   <li> 2001-04-05, cK, setColor ..
 *   <li> 2001-09-09, cK, Includes aufgeraeumt.
 * </ul>
 *
 * @todo evtl texgen und textur in einem feld zusammenfassen ..
 *       * (TexGen*, Texture*) .. weniger mutexe
 * @todo die ** fuer texturen sind nicht schoen. auch die
 *       maxanzahl ist nicht fein.
 *
 * @version $Revision: 1.5 $, $Date: 2001/09/13 13:11:13 $
 *
 * @author cK, $Author: koestlin $
 */
class Appearance : public NodeComponent {
  public:

    /** Erzeugt einen neue Appearance.
     *
     * @param _texNr Anzahl an gewuenschten multitexturelayers.
     */
    Appearance(int _texNr);

    void accept(Visitor* v) {
      v->visit(this);
    }

    /** Liefert die maximale anzahl von gesetzten texturen.
     *
     * @return int maximum an gesetzten texturen.
     */
    int getMaxMultiTextures();

    /** Setzt die Polygonattribute.
     *
     * SG-maessig
     *
     * @param pAtts PolygonAttribute.
     */
    virtual void setPolygonAttributes(PolygonAttributes* _pAtts);

    /** Setzt die RenderingAttribute.
     *
     * SG-maessig
     *
     * @param rAtts RenderingAttribute.
     */
    virtual void setRenderingAttributes(RenderingAttributes* _rAtts);

    /** Setzt die Textur.
     *
     * SG-maessig.
     *
     * @param _texture Texturdaten.
     * @param _tNr Multitexturnr.
     */
    virtual void setTexture(Texture* _texture, int _tNr);

    /** Setzt die TexGenattribute.
     *
     * SG-maessig
     *
     * @param _texGen Texturgenerierungsattribute.
     * @param _tNr Multitexturnr.
     */
    virtual void setTexGen(TexGen* _texGen, int _tNr);

    /** Liefert die PolygonAttribute.
     *
     * SG-maessig
     *
     * @return PolygonAttributes* Attribute.
     */
    virtual PolygonAttributes* getPolygonAttributes();

    /** Liefert die Rendering Attributes.
     *
     * SG-maessig.
     *
     * @return RenderinAttribute* Attribute.
     */
    virtual RenderingAttributes* getRenderingAttributes();

    /** Liefert die Textur.
     *
     * SG-maessig
     *
     * @param _texNr Multitexturnr.
     *
     * @return Texture* glaub ich nicht!
     */
    virtual Texture* getTexture(int _texNr);

    /** Setzt das Material der Appearance.
     *
     * @param _color Farbe.
     */
    virtual void setMaterial(Material* _m);

    /** Liefert das Material.
     *
     * @return Material* Das Material.
     */
    virtual Material* getMaterial();

    /** Liefert die Texturgenerierungsattribute.
     *
     * SG-maessig
     *
     * @param _texNr Multitexturnr.
     *
     * @return TexGen* Texturegenerierungsparameter.
     */
    virtual TexGen* getTexGen(int _texNr);

    std::string toString() {
      return(std::string("Appearance"));
    }

    /** Gepufferte Polygonattribute. Nur fuer die Visitoren sichtbar. */
    UpdateObject<PolygonAttributes>* polygonAttributes;

    /** Gepufferte RenderingAttribute. Nur fuer die Visitoren sichtbar. */
    UpdateObject<RenderingAttributes>* renderingAttributes;

    /** Gepufferte Textur. Nur fuer die Visitoren. */
    UpdateObject<Texture>** textures;

    /** Gepufferte Texturgenerierungsattribute. Nur fuer die Visitoren. */
    UpdateObject<TexGen>** texGens;

    /** material der Appearance. */
    UpdateObject<Material>* material;

  protected:
    /** Raeumt auf. */
    virtual ~Appearance();

  private:
    /** Testet, ob eine texturnummer auch ok ist.
     *
     * @param _texNr
     * @param where Beschreibung, wo der zugriff versucht wurde.
     *
     * @exception falls der range nicht stimmt.
     */
    void assertTexNr(int _texNr, const char* where) throw (Exception);

    /** maximale anzahl von multitextures. */
    int maxTextures;

};

#endif // _Appearance_h_
