#ifndef _SGObserver_h_
#define _SGObserver_h_

#include <sg/math/RCTransform3D.h>
#include <vecmath/Transform3D.h>
#include <vecmath/Vector3f.h>

#include <sg/nodes/ProjectionGroup.h>

#include <sg/visitors/Visited.h>
#include <sg/visitors/Visitor.h>

#include <util/UpdateObject.h>
#include <vecmath/Frustum.h>


/** Betrachter einer Szene.
 *
 * Der Betrachter soll durch die Szene bewegt werden koennen.
 * Und zwar in Weltkoordinaten, aber auch mit den Koordinaten, die
 * relativ zur Blickrichtung sind (also in Richtung der Kamera gehen).
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-12-29, cK, New from Scratch.
 *   <li> 2000-12-29, cK, Das mit moveLocal und moveWorld hingekriegt???
 *   <li> 2001-03-01, cKgS, Camera integriert.
 *   <li> 2001-04-15, cK, Auf math/Vector3f angepasst.
 *   <li> 2001-04-23, gS cK, Frustum vom Gerd eingebaut.
 *   <li> 2001-04-27, cK, frustum mit Bildgroesse eingebaut.
 * </ul>
 *
 * @todo Ueberlegen, wie man alle moeglichen Projectionen zusammenfassen kann!
 *
 * @version $Revision: 1.2 $, $Date: 2001/07/05 13:27:23 $
 *
 * @author cK, $Author: koestlin $
 */
class SGObserver : public ProjectionGroup {

 public:
  /** Erzeugt einen neuen SGObserver mit Ausrichtung entlang der
   * Z-Achse.
   */
  SGObserver();

  void accept(Visitor* v) {
    v->visit(this);
  }

  /** Bewegt den Beobachter in Weltcoordinaten.
   *
   * SG-maessiges Setzen.
   *
   * @param pos Position, geht nicht in den Besitz des Observers ueber.
   */
  virtual void setTranslation(Vector3f* pos);

  /** Liefert die Transformation.
   *
   * Die Transformation sollte als readonly behandelt werden,
   * muss aber mit releaseReference befreit werden.
   *
   * @return RCTransform3D* die Transformation.
   */
  virtual RCTransform3D* getTransform() {
    return(transform.get());
  }

  /** Liefert die Translation.
   *
   * @return Vector3f* Die Translation, geht in den Besitz des Callers ueber.
   */
  virtual Vector3f* getTranslation();

  /** Berechnet die Transformation, wie sie zum rendern benoetigt wird.
   */
  virtual void calcTransform();

  /** Setzt die Transformation komplett.
   *
   * Dabei ist transformation so definiert, dass in der
   * rotationsmatrix z.b. eine eulermatrix steht und in dem
   * translationsteil die translation in weltkoordinaten .. wenn
   * es sein muss, muss man also mit calcTransform die transformation
   * berechnen, die opengl bracuht und kann das dann mit
   * getCameraTransform holen.
   *
   * SG-maessiges setzen.
   */
  virtual void setTransform(RCTransform3D* t3d);

  /** Liefert die Zusammengesetzte Transformation des Beobachters,
   * die von calcTransform gesetzt wird.
   *
   * SG-maessiges liefern.
   *
   * @return RCTransform3D* transformation.
   */
  virtual RCTransform3D* getCameraTransform();

  /** Transformation. */
  UpdateObject<RCTransform3D> transform;

  /** Berechnet das Frustum des Observers.
   *
   * @param width Breite des Bildes.
   * @param height Hohe des Bildes.
   */
  void calculateFrustum(int width, int height);

  /** Liefert das Frustum des Betrachters.
   *
   * @return Frustum bleibt im besitz des observers.
   */
  virtual Frustum* getFrustum();

  /** Frustum des Betrachters. */
  Frustum* frustum;

 protected:
  /** Raeumt auf. */
  virtual ~SGObserver();

 private:
  /** Endgueltige Transformation, sollte nur von UpdateVisitor
   * gesetzt werden.
   */
  RCTransform3D* result;

};

#endif // _SGObserver_h_
