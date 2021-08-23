#ifndef _TriangleArray_h_
#define _TriangleArray_h_

#include <sstream>

#include <sg/data/Array1i.h>
#include <sg/data/Array2f.h>
#include <sg/data/Array3f.h>

#include <sg/nodeComponents/geom/Geometry.h>
#include <sg/nodeComponents/geom/TriangleArrayType.h>

#include <sg/visitors/Visitor.h>

#include <util/UpdateObject.h>

/** Klasse, die TriangleArrays speichert.
 *
 * Ein TriangleArray ist eine Menge von Punkten (und evtl.
 * deren Farben, Normalen und Texturcoordinaten). Diese werden je nach
 * Typ zu graphicprimitiven zusammengefasst. Die gelaeufigsten davon sind:
 * Triangles, Fans, Strips. Bei Triangles werden jeweils 3 Punkt zu einem
 * Dreieck zusammengefasst. Bei Fan beschreiben die 1. 3 Punkte ein Dreieck,
 * und der 1. Punkt dieses Dreiecks und der letzte beschreiben mit dem
 * naechsten Punkt zusammen das neue Dreieck.
 * Bei strips wird auch durch die 1. 3 punkte ein dreieck beschrieben, die
 * weiteren dreiecke werden immer durch die letzen 2 Punkte und einen neuen
 * beschrieben.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-12-29, cK, Created.
 *   <li> 2001-01-04, cK, Auf multitexturing erweitert.
 *   <li> 2001-01-12, cK Gs, stripVertexCounts integriert.
 * </ul>
 *
 * @todo Unbedingt noch diese Interleaved arrays antesten.
 *
 * @version $Revision: 1.2 $, $Date: 2001/05/14 12:08:30 $
 *
 * @author cK, $Author: koestlin $
 */
class TriangleArray : public Geometry {

  public:

    /** Erzeugt eine Triangle Array mit gegebenem Typ.
     *
     * @param _type Typ des Arrays.
     * @param _maxMultiTextures anzahl von multitexturelayers.
     */
    TriangleArray(const TriangleArrayType _type, int _maxMultiTextures);

    void accept(Visitor* v) {
      v->visit(this);
    }

    /** Setzt die Koordinaten des TriangleFans.
     *
		 * SG-maessiges setzen.
		 *
     * @param coords Neue Koordinaten.
     */
    virtual void setCoordinates(Array3f* coords);

    /** Setzt die Farben.
		 *
		 * SG-maessiges setzen.
     *
     * @param colors Neue Farben.
     */
    virtual void setColors(Array3f* colors);

    /** Setzt die Texturcoordinaten.
		 *
		 * SG-maessiges setzen
     *
     * @param _textureCoords Texturcoordinaten.
     * @param _texNr MultiTextureNr.
     */
    virtual void setTextureCoordinates(Array2f* _textureCoords, int _texNr);

    /** Setzt die Normalen.
		 *
		 * SG-maessiges setzen.
     *
     * @param normals Normalen.
     */
    virtual void setNormals(Array3f* normals);

    /** Setzt die stripVertexCounts.
     *
     * SG-maessiges setzen.
     *
     * @param stripVertexCounts vertexCounts.
     */
    virtual void setStripVertexCounts(Array1i* stripVertexCounts);

    /** Typ des Arrays. */
    TriangleArrayType type;

    /** Gepufferte Koordinaten. */
    UpdateObject<Array3f>* coords;

    /** Gepufferte Farbwerte. */
    UpdateObject<Array3f>* colors;

    /** Gepufferte Texturcoordinaten. */
    UpdateObject<Array2f>** textureCoords;

    /** Gepufferte Normalendaten. */
    UpdateObject<Array3f>* normals;

    /** per-strip vertex counts. */
    UpdateObject<Array1i>* stripVertexCounts;

    /** Liefert die Anzahl von gewuenschten multitexturinglevels.
     *
     * @return int Multitexturlevels.
     */
    int getMaxMultiTextures() {
      return(maxMultiTextures);
    }

    std::string toString() {
      std::ostringstream help;
      help << "TriangleArray" << std::ends;
      std::string res(help.str());
      return(res);
    }

  protected:
    /** Raumt auf. */
    virtual ~TriangleArray();

  private:
    /** untersucht ob die geforderte _texNr legal ist.
     *
     * @param _texNr Multitexturnr.
     */
    void assertMaxMultiTextures(int _texNr);

    /** Anzahl von multitextur-leveln. */
    int maxMultiTextures;

};

#endif // _TriangleArray_h_
