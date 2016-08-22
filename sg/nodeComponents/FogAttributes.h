#ifndef _FogAttributes_h_
#define _FogAttributes_h_

#include <sg/nodeComponents/NodeComponent.h>

#include <string>
#include <sstream>

/** Erstmal Linearer Fog.
 *
 * <p>
 * Curriculum Vitae:
 * <ul> 
 *   <li> 2001-03-02, cKgS, Created.
 * </ul>
 *
 * @todo richtiges farbattribut verwenden.
 *
 * @version $Revision: 1.1.1.1 $, $Date: 2001/04/27 14:10:36 $
 *
 * @author cKgS, $Author: koestlin $
 */                      
class FogAttributes : public NodeComponent {

  public:
    /** Erzeugt einen LinearenFogparametersatz. 
     *
     * @param _r, _g, _b Farbe des Nebels
     * @param _start Anfang des linearen nebels
     * @param _end Ende des linearen nebels.
     */
    FogAttributes(float _r, float _g, float _b, float _start, float _end) 
      : r(_r), g(_g), b(_b), start(_start), end(_end) {
    }

    /** Rotkomponente. */
    float r;

    /** Gruenkomponente. */
    float g;

    /** Blaukomponente. */
    float b;

    /** Startdistanz, ab der der Nebel einsetzt. */
    float start;

    /** Distanz, bei der der Nebel voll zuschlaegt. */
    float end;

    std::string toString() {
      std::ostringstream help;
      help << "FogAttributes (" << r << ", " << g << ", " << b << ", "
        << start << ", " << end << "(" << std::ends;
      std::string res(help.str());
      return(res);
    }


};

#endif // _FogAttributes_h_
