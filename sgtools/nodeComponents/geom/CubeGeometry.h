#ifndef _CubeGeometry_h_
#define _CubeGeometry_h_

#include <sg/nodeComponents/geom/IndexedTriangleArray.h>

/** Einfache Wuerfelgeometrie, ohne normalen etc.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-09-04, cK, Craeted.
 * </ul>
 *
 * @@version $Revision$ $Date$
 *
 * @@author cK $Author$
 */
class CubeGeometry : public IndexedTriangleArray {

public:
  /** Erzeugt einen Wuerfel am Ursprung mit einer gewissen Kantenlaenge.
   *
   * @@param size Kantenlaenge.
   * @@param maxMultiTextures Anzahl von Texturen.
   */
  CubeGeometry(float size, int maxMultiTextures);

};

#endif // _CubeGeometry_h_
