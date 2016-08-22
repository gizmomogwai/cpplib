#ifndef _ParallelProjection_h_
#define _ParallelProjection_h_

#include <vecmath/Transform3D.h>

/** Parallelprojection.
 *
 * Momentan wird die Projection so ausgewertet, dass links 
 * unten immer 0,0 istund recht oben die koordinate aktuelle
 * Fensterbreite/Fensterhoehe hat.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-03-22, cK, Created.
 * </ul>
 *
 * @todo Ueberlegen,obman nicht auchsowas  wieaspect ratio angeben
 *       sollte ... und dann immer richtig anpassen ...
 *
 * @version $Revision: 1.2 $, $Date: 2001/08/06 14:46:17 $
 *
 * @author cK, $Author: koestlin $
 */
class ParallelProjection {
            
  public:
    /** Erzeugt eine neue Parallelprojection. */
    ParallelProjection(float _factor=1.0f) : 
      left(-1), 
      right(1), 
      bottom(-1), 
      top(1), 
      nearClipping(-1), 
      farClipping(1), factor(_factor) {
    }


    /** Liefert die ProjectionMatrix einer ParallelProjection. 
     *
     * @return Transform3D* Transformation geht in den Besitz des 
     *         Callers ueber.
     */
    Transform3D* getProjection();

    /** xKoordinate die ganz links dargestellt wird. */
    float left;

    /** xKoordinate die ganz recht dargestellt wird. */
    float right;

    /** yKoordinate, die ganz unten dargestellt wird. */
    float bottom;

    /** yKoordinate, die ganz oben dargestellt wird. */
    float top;

    /** zKoordinate, die ganz vorne dargestellt wird. */
    float nearClipping;

    /** zKoordinate, die ganz hinten dargestellt wird. */
    float farClipping;

    float factor;

};

#endif // _ParallelProjection_h_
