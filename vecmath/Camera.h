#ifndef _Camera_h_
#define _Camera_h_

#include <vecmath/Transform3D.h>

/** Cameramodel.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-03-01, cKgS, Created.
 *   <li> 2001-04-27, cK, setSize (wegen problemen mit aspectratio und updates).
 * </ul>
 *
 * @version $Revision: 1.2 $, $Date: 2001/05/02 16:21:45 $
 *
 * @author cKgS, $Author: koestlin $
 */
class Camera {

  public:
    /** Erzeugt eine neue Camera.
     *
     * @param _fieldOfView Oefnungswinkel des Sichtkegels in Grad
     * @param _aspectRatio AspektRatio des Viewports.
     * @param _nearClippingPlane  Entfernung zur NearClippingPlane.
     * @param _farClippingPlane Entfernung zur FarClipping Plane.
     */
    Camera(float _fieldOfView, float _aspectRatio,
           float _nearClippingPlane, float _farClippingPlane)
      : fieldOfView(_fieldOfView),
        aspectRatio(_aspectRatio),
        nearClippingPlane(_nearClippingPlane),
        farClippingPlane(_farClippingPlane) {
    }

    /** Raeumt auf. */
    virtual ~Camera() {
    }

    /** Setzt die Aspect Ratio mittels der Breite und Hoehe des
     * Canvases.
     *
     * @param width Breite.
     * @param height Hoehe.
     */
    void setSize(int width, int height);

    /** Liefert eine Projectionsma trix zur Camera.
     *
     * @return Transform3D* Transformation geht in den Besitz
     *         des Callers ueber.
     */
    Transform3D* getProjection();

    /** Field Of View*/
    float fieldOfView;

    /** Aspect Ratio. */
    float aspectRatio;

    /** Near Clipping Distance. */
    float nearClippingPlane;

    /** Far Clipping Distance. */
    float farClippingPlane;

};

#endif // _Camera_h_
