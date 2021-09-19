#ifndef _Vector3f_h_
#define _Vector3f_h_

#include <lang/Exception.h>
#include <math.h>
#include <string>
#include <sstream>

class Point3f;

/** 3-D Vector.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-04-15, cK, Aus dem Szenegraphen rausgenommen.
 *   <li> 2001-07-05, cK, Union-todo entfernt.
 * </ul>
 *
 * @todo hier ist der std.platz fuer referencen ... mal den fabian fragen,
 *       wie das bei anderen sachen und vor allem auch hier gemacht wird.
 *
 * @version $Revision: 1.7 $, $Date: 2001/08/15 15:47:44 $
 *
 * @author cK, $Author: schaefer $
 */
class Vector3f {

 public:
  /** Erzeugt einen neuen Vector _OHNE_ initialisierung.
   */
  Vector3f() {
  }

  /** Erzeugt einen neuen Vector.
   *
   * @param x X
   * @param y y
   * @param z z
   */
  Vector3f(float x, float y, float z) {
    dx = x;
    dy = y;
    dz = z;
  }

  /** Erzeugt einen neuen Vector aus einem anderen.
   *
   * (Copy constructor).
   *
   * @param toCopy Zu kopierender Vector.
   */
  Vector3f(Vector3f* toCopy) {
    dx = toCopy->dx;
    dy = toCopy->dy;
    dz = toCopy->dz;
  }

  /** Erzeugt einen Vector3f aus einem Punkt.
   *
   * @param toCopy Zu kopierender Punkt.
   */
  Vector3f(Point3f* toCopy);

  /** Raeumt auf. */
  virtual ~Vector3f() {}

  /** Zieht von b a ab und setzt this auf die Differenz.
   *
   * @param a Vector.
   * @param b Vector.
   */
  void sub(Vector3f* a, Vector3f* b) {
    dx = b->dx - a->dx;
    dy = b->dy - a->dy;
    dz = b->dz - a->dz;
  }


  /** Zieht von b a ab und setzt this auf die Differenz.
   *
   * @param a Point3f.
   * @param b Point3f.
   */
  void sub(Point3f* a, Point3f* b);


  /** Subtrahiert Vektor von this
   *
   * @param a Vector.
   */
  void sub(Vector3f* a) {

    dx -= a->dx;
    dy -= a->dy;
    dz -= a->dz;
  }

  /** Addiert 2 Vectoren.
   *
   * @param a Vector 1.
   * @param b Vector 2.
   */
  void add(Vector3f* a, Vector3f* b) {
    dx = a->dx + b->dx;
    dy = a->dy + b->dy;
    dz = a->dz + b->dz;
  }


  /** Addiert Vector auf this.
   *
   * @param a Vector 1.
   */
  void add(Vector3f* a) {
    dx += a->dx;
    dy += a->dy;
    dz += a->dz;
  }

  /** Normalisiert this.
   *
   * @todo was wenn die Laenge 0 ist.
   */
  void normalize() throw (Exception) {
    float l = (float)(sqrt(dx*dx + dy*dy + dz*dz));
    if (l == 0) {
      throw(Exception("Vector3f::normalize() - laenge 0", __FILE__, __LINE__));
    }
    scale((float)(1 / l));
  }

  /** Liefert die Laenge eines Vectors.
   *
   * @return float Laenge.
   */
  float getLength() {
      return(sqrt(dx * dx + dy*dy + dz*dz));
  }

  /** Setzt this auf das Kreuzproduke von a und b.
   *
   * @param a Vector 1.
   * @param b Vector 2.
   */
  void cross(Vector3f* a, Vector3f* b) {
      dx = a->dy * b->dz - a->dz * b->dy;
      dy = a->dx * b->dz - a->dz * b->dx;
      dz = a->dx * b->dy - a->dy * b->dx;
  }

  /** Skaliert this.
   *
   * @param f Skalierungsfactor.
   */
  void scale(float f) {
      dx *= f;
      dy *= f;
      dz *= f;
  }

  /** Setzt this mit den Werten eines anderen Vectors.
   *
   * @param v Anderer Vector.
   */
  void set(Vector3f* v) {
      //   memcpy(Vector3f::v, v->v, 12);
      dx = v->dx;
      dy = v->dy;
      dz = v->dz;
  }

  /** Setzt this mit den angegebenen Werten.
   *
   * @param x XPosition.
   * @param y YPosition.
   * @param z ZPosition.
   */
  void set(float x, float y, float z) {
    dx = x;
    dy = y;
    dz = z;
  }

  /** Vergleicht this mit einem anderen Vector bei value.
   *
   * @param v Anderer Vector.
   *
   * @return bool true falls d, dy und dz gleich sind.
   */
  bool equals(Vector3f* v) {
    return((dx == v->dx) && (dy == v->dy) && (dz == v->dz));
  }


  /** Liefert eine Stringrepraesentation von this.
   *
   * @return std::string Stringrep.
   */
  std::string toString() {
      std::ostringstream help;
      help << "Vector3f(" << dx << ", " << dy
     << ", " << dz << ")" << std::ends;
      std::string res = std::string(help.str());
      return(res);
  }


  /** x-Komponente. */
  float dx;

  /** y-Komponente. */
  float dy;

  /** z-Komponente. */
  float dz;
};

#endif // _Vector3f_h_
