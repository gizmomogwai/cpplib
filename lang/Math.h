#pragma once

#include <stdlib.h>

/** Klasse fuer einfache Mathefunktionen und Konstanten.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-??-??, cK, Craeted.
 *   <li> 2001-05-26, cK, Commented.
 * </ul>
 *
 * @version $Revision: 1.1 $, $Date: 2002/10/28 23:27:35 $
 *
 * @author cK, $Author: gizmo $
 */
class Math {

  public:
    /** PI. */
    static const float PI;

    /** Konstante die bei der Umrechnung von grad nach rad behilflich ist. */
    static const float A_PI;


    /** Rechnet grad in rad um.
     *
     * @param degree Winkel in Grad.
     *
     * @return float Winkel in Rad.
     */
    static float toRadians(float degree) {
      return(degree * Math::A_PI);
    }

    /** Erzeugt Zufallszahl zwischen 0 und max.
     *
     * @param max Maximalwert der Zufallszahl.
     *
     * @return float Zufallszahl.
     */
    static float random(float max) {
      float help = (float)rand();
      return(help / RAND_MAX * max);
    }

};
