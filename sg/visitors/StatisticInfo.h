#ifndef _StatisticInfo_h_
#define _StatisticInfo_h_

#include <string>

class Group;
class TGroup;
class FogGroup;
class LightGroup;
class ProjectionGroup;
class Shape3D;
class OrientedShape3D;
class TeapotGeometry;
#include <sg/nodeComponents/geom/TriangleArray.h>
#include <sg/nodeComponents/geom/IndexedTriangleArray.h>
class Text3D;
class Appearance;
class Behavior;

/** Klasse die vom StatisticVisitor verwendet wir, um 
 * die Statistic zu fuehren (elemente zaehlen etc).
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-03-17, cK, Created.
 *   <li> 2001-04-06, cK, Zumindest benutzbar gemacht.
 * </ul>
 *
 * @version $Revision: 1.2 $, $Date: 2001/05/14 12:08:31 $
 *
 * @author cK, $Author: koestlin $
 */
class StatisticInfo {

  public:
    
    /** Loescht die Informationen. 
     */
    void clear() {
      groupCount = 0;
      tGroupCount = 0;
      fGroupCount = 0;
      lGroupCount = 0;
      pGroupCount = 0;
      shapeCount = 0;
      orientedShapeCount = 0;
      teapotCount = 0;
      triangleArrayCount = 0;
      triangleArrayTRICount = 0;
      triangleArrayFANCount = 0;
      triangleArraySTRIPCount = 0;

      indexedTriangleArrayCount = 0;
      indexedTriangleArrayTRICount = 0;
      indexedTriangleArrayFANCount = 0;
      indexedTriangleArraySTRIPCount = 0;

      textCount = 0;
      appCount = 0;
      bhCount = 0;
    } 

    /** Updated Gruppeninfos. 
     *
     * @param g Group. 
     */
    void update(Group* g) {
      groupCount++;
    }

    /** Updates TGroupinfos
     *
     * @param tg
     */
    void update(TGroup* tg) {
      tGroupCount++;
    }

    /** Updated FogGroup.
     *
     * @param fg
     */
    void update(FogGroup* fg) {
      fGroupCount++;
    }

    /** Updated LightGroup.
     *
     * @param lg
     */
    void update(LightGroup* lg) {
      lGroupCount++;
    }
    /** Updated ProjectionGroup.
     *
     * @param pg
     */
    void update(ProjectionGroup* pg) {
      pGroupCount++;
    }
    /** Updated Shapeinfos.
     *
     * @param s shape.
     */
    void update(Shape3D* s) {
      shapeCount++;
    }

    /** Updated OrientedShapeinfos.
     *
     * @param s
     */
    void update(OrientedShape3D* s) {
      orientedShapeCount++;
    }
    /** Updated teapotinfos.
     *
     * @param teapot
     */
    void update(TeapotGeometry* teapot) {
      teapotCount++;
    }

    /** Updated TriangelArrayinfos.
     *
     * @param ta
     */
    void update(TriangleArray* ta) {
      triangleArrayCount++;
      Array3f* a = ta->coords->get();
      if (a != 0) {
        if (ta->type == TRIS) {
          triangleArrayTRICount += a->getSize();
        } else if (ta->type == FAN) {
          triangleArrayFANCount += a->getSize();
        } else if (ta->type == STRIP) {
          triangleArraySTRIPCount += a->getSize();
        }
        a->releaseReference();
      }
    }
    /** Updated IndexedTriangleArrayinfos.
     *
     * @param ita
     */
    void update(IndexedTriangleArray* ita) {
      indexedTriangleArrayCount++;
      Array1i* a = ita->indices->get();
      if (a != 0) {
        if (ita->type == TRIS) {
          indexedTriangleArrayTRICount += a->getSize();
        } else if (ita->type == FAN) {
          indexedTriangleArrayFANCount += a->getSize();
        } else if (ita->type == STRIP) {
          indexedTriangleArraySTRIPCount += a->getSize();
        }
        a->releaseReference();
      }
    }
    /** Updatet text3dinfos.
     *
     * @param t3d
     */
    void update(Text3D* t3d) {
      textCount++;
    }
    /** Updated Appearanceinfos.
     *
     * @param app 
     */
    void update(Appearance* app) {
      appCount++;
    }
    /** Updated Behaviorinfos.
     *
     * @param b
     */
    void update(Behavior* b) {
      bhCount++;
    }

    
    /** Liefert Stringrep.
     *
     * @return std::string stringrep.
     */
    std::string toString() {
      std::ostringstream help;
      help << "StatisticInfo:" << std::endl;
      append(&help, "  Groups: ", groupCount);
      append(&help, "  TGroups: ", tGroupCount);
      append(&help, "  FogGroups: ", fGroupCount);
      append(&help, "  Lightgroups: ", lGroupCount);
      append(&help, "  PGroups: ", pGroupCount);
      append(&help, "  Shapes: ", shapeCount);
      append(&help, "  OrientedShapes: ", orientedShapeCount);
      append(&help, "  Teapots: ", teapotCount);
      append(&help, "  TriangleArrays: ", triangleArrayCount);
      append(&help, "    - points in TRIS: ", triangleArrayTRICount);
      append(&help, "    - points in FANS: ", triangleArrayFANCount);
      append(&help, "    - points in STRIPS: ", triangleArraySTRIPCount);
      append(&help, "  IndexedTriangleArrayCount: ", indexedTriangleArrayCount);
      append(&help, "    - points in TRIS: ", indexedTriangleArrayTRICount);
      append(&help, "    - points in FANS: ", indexedTriangleArrayFANCount);
      append(&help, "    - points in STRIPS: ", indexedTriangleArraySTRIPCount);
      append(&help, "  Text: ", textCount);
      append(&help, "  Appearances: ", appCount);
      append(&help, "  Behaviors: ", bhCount);
      help << std::ends;
      std::string res(help.str());
      return(res);
    }

  public:
    /// Gruppenzaehler
    int groupCount;
    /// TGruppenzaehler
    int tGroupCount;
    /// FGruppenzaehler
    int fGroupCount;
    /// LGruppenzaehler
    int lGroupCount;
    /// pGruppenzaehler
    int pGroupCount;
    /// Shapezaehler
    int shapeCount;
    /// Orientedzaehler
    int orientedShapeCount;
    /// Teapotzaehler
    int teapotCount;
    /// TriangleArrayzaehler
    int triangleArrayCount;
    /// anzahl von trianglearray trispunkten
    int triangleArrayTRICount;
    /// anzahl von trianglearray fanpunkten
    int triangleArrayFANCount;
    /// anzahl von trianglearray strippunkten
    int triangleArraySTRIPCount;
    /// anzahl von indexedtrianglearrays
    int indexedTriangleArrayCount;
    /// anzahl von indexedtrianglearray trispunkten
    int indexedTriangleArrayTRICount;
    /// anzahl von indexedtrianglearray fanpunkten
    int indexedTriangleArrayFANCount;
    /// anzahl von indexedtrianglearray strippunkten
    int indexedTriangleArraySTRIPCount;
    /// anzahl von text3dknoten
    int textCount;
    /// anzahl von appearances
    int appCount;
    /// anzahl von behaviors
    int bhCount;
  
  private:
    /** Haengt an einen oststream einen beschriebenen wert an, wenn der 
     * wert > 0 ist.
     *
     * @param help strstream
     * @param dsc Beschreibung.
     * @param value Wert.
     */
    void append(std::ostringstream* help, std::string dsc, int value) {
      if (value > 0) {
        (*help) << dsc << value << std::endl;
      }
    }

};


#endif // _StatisticInfo_h_
