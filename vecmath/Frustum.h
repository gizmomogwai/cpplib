#ifndef _Frustum_h_
#define _Frustum_h_

#include <vecmath/Transform3D.h>
#include <vecmath/Plane.h>

#include <sg/BoundingSphere.h>
#include <vecmath/Plane.h>

/**
 * Aus einer Projektions -und ModelViewMatrix wird ein
 * Frustum erstellt. Das Frustum wird mit 6 Ebene modelliert.
 * Man kann dieses Frustum auf Schnitt mit BoundingSpheres und
 * BoundingBoxes testen.
 * Basiert auf diesem Artikel:
 * http://www.markmorley.com/opengl/frustumculling.html
 *
 * Anmerkung: Berechnung fuer far und near clipping plane vertauscht.
 * wegen Problemen mit Abstandsberechnung ???
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-??-??, gS, kirsten, Created.
 *   <li> 2001-04-24, cK, Grosse Methoden ins cpp file.
 * </ul>
 *
 * @todo BoundingBoxTest machen
 * @todo Braucht man die Operationen wirklich???
 *
 * @author kirsten terfloth, gS, $Author: schaefer $
 *
 * @version $Revision: 1.3 $, $Date: 2001/07/17 14:22:45 $
 */
class Frustum {

  public:

    /**
     * Initialisiert Frustum mit Objekten die wiederverwendet werden.
     */
    Frustum();

    /**
     * Destruktor raeumt auf
     */
    ~Frustum();

    /**
     * Erstellt aus den beiden Matrizen das Frustum
     *
     * @param projection ProjectionsMatrix
     * @param modelView Beschreibt Betrachter (Translation, Rotation....)
     */
    void create(Transform3D* projection, Transform3D* modelView);

    /**
     * Testet, ob Sphere in Frustum und gibt Entferung zur
     * near clipping plane zurueck.
     *
     * Die Sphere ist nicht im Frustum, wenn sie weiter
     * als radius auf der Aussenseite einer Ebene liegt.
     *
     * @param bSphere Kugel.
     *
     * @return 0 wenn ausserhalb, sonst abstand zur near clipping plane
     */
    double sphereInFrustumDistance(BoundingSphere* bSphere);

    /** Testet, ob eine Kugel mit Mittelpunkt x, y, z und radius
     * im Frustum liegt.
     *
     * @param x xKoordinate.
     * @param y yKoordinate.
     * @param z zKoordinate.
     * @param radius Kugelradius.
     *
     * @return 0 wenn ausserhalb, ansonsten abstand zur near clipping plane.
     */
    double sphereInFrustumDistance(float x, float y, float z, float radius);


    /** (siehe sphereInFrustumDistance).
     *
     * @param bSphere die BoundingSphere
     *
     * @return Frustum in Kugel ja / nein
     */
    bool sphereInFrustum(BoundingSphere* bSphere);

    /** siehe speherInFrustumDistance.
     *
     * @param x xKoordinate.
     * @param y yKoordinate.
     * @param z zKoordinate.
     * @param radius Kugelradius.
     */
    bool sphereInFrustum(float x, float y, float z, float radius);


    /** gibt Koeffizienten der 6 Ebenen aus
     *
     * @return string (Koeffizienten)
     */
    std::string toString() {

      std::ostringstream help;

      for (int i=0; i<6; i++) {

        help << frustumPlanes[i].toString();
      }

      help << std::endl;
      help << std::ends;

      std::string res = std::string(help.str());
      return(res);
    }

  private:

    /** Ebenen. frustumPlanes[5] ist die nearClipping plane. */
    Plane frustumPlanes[6];

};

#endif // _Frustum_h_
