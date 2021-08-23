#ifndef _PolygonAttributes_h_
#define _PolygonAttributes_h_

#include <lang/Exception.h>

#include <util/UpdateObject.h>

#include <sg/nodeComponents/NodeComponent.h>

/** Alle moeglichen PolygonAttribute.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-12-08, cK, Created.
 *   <li> 2001-03-31, cK, an linux angepasst.
 * </ul>
 *
 * @todo Die polygonattribute als enum oder zumindest irgendwie typesafe!
 *
 * @version $Revision: 1.2 $, $Date: 2001/08/06 16:08:16 $
 *
 * @author cK, $Author: koestlin $
 */
class PolygonAttributes : public NodeComponent {

 public:
  /** Erzeugt neue Polygonattribute.
   *
   * @param polyMode Mode des Polygons.
   *
   * @exception Exception falls der parameter nicht korrekt ist.
   */
  PolygonAttributes(int polyMode) throw (Exception);

  /** PolygonMode. Eigentlich private nur die Visitoren sollten das
   * lesen.
   */
  int polyMode;

  /** Polygon wird gefuellt. */
  static const int POLYGON_FILL;

  /** Nur der Rand des Polygons wird gefuellt. */
  static const int POLYGON_LINE;

  /** Nur die Eckpunkte des Polygons werden gezeichnet. */
  static const int POLYGON_POINT;

 protected:
  /** Raeumt auf. */
  virtual ~PolygonAttributes() {}

};

#endif // _PolygonAttributes_h_
