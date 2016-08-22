#ifndef _Light_h_
#define _Light_h_

#include <vecmath/Color3f.h>
#include <vecmath/Point4f.h>

#include <sg/nodeComponents/NodeComponent.h>

/** Kapselt Lichtdaten.
 *
 * <p>
 * Curriculum Vitae:
 * <ul> 
 *   <li> 2001-03-08, cKgS, Created.
 *   <li> 2001-03-10, cK, Kommentare.
 * </ul>                            
 *
 * @version $Revision: 1.2 $, $Date: 2001/05/28 09:40:54 $
 *
 * @author cKgS, $Author: koestlin $
 */                     
class Light : public NodeComponent {
                                    
  public:
    /** Erzeugt ein Licht.
     *
     * @param _ambientColor Ambiente Farbe des Lichtes. Geht in den Besitz des lichts ueber.
     * @param _diffuseColor Diffuse Farbe. Geht in den Besitz des lichts ueber.
     * @param _specularColor Specularteil. Geht in den Besitz des lichts ueber.
     * @param _posDir Homogene Koordinate des Lichts. Bleibt im Besitz des Callers.
     */
    Light(Color3f* _ambientColor, 
          Color3f* _diffuseColor, 
          Color3f* _specularColor,
          Point4f* _homogenPosition) {
      ambientColor = _ambientColor;
      diffuseColor = _diffuseColor;
      specularColor = _specularColor;
      homogenPosition.set(_homogenPosition);
    }
    
    /** Ambiente Farbe. */
    Color3f* ambientColor;

    /** Diffuse Farbe. */
    Color3f* diffuseColor;

    /** Speculare farbe. */
    Color3f* specularColor;

    /** Homogene Koordinaten des Lichts. */
    Point4f homogenPosition;

    /** Liefert Stringrep.
     *
     * @return std::string Beschreibung.
     */
    std::string toString() {
      return("Light");
    }

  protected:
    /** Raeumt auf. */
    virtual ~Light() {
      delete(ambientColor);
      delete(diffuseColor);
      delete(specularColor);
    }

};

#endif // _Light_h_
