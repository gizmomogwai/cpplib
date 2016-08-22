#ifndef _Point3f_h_
#define _Point3f_h_

#include <pragmaincludes.h>

#include <lang/Exception.h>
#include <math.h>
#include <string>
#include <sstream>
#include <vecmath/Vector3f.h>

/** 3-D Punkt, der Referenzcounted ist und somit in den Szenegraphen
 * integriert werden kann. 
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-01-16, cKgS, Created.
 *   <li> 2001-04-15, cK, Aus sg rausgenommen, ohne RefCounting, setMethode
 *   <li> 2001-06-27, gS, Vector auf Point3d addieren
 * </ul>
 *
 * @version $Revision: 1.6 $, $Date: 2001/08/15 15:47:44 $
 *
 * @author cK, $Author: schaefer $
 */
class Point3f {

 public:
	/** Erzeugt einen neuen Punkt _OHNE_ initialisierung. 
	 */
	Point3f() {
	}

	/** Erzeugt einen neuen Punkt.
	 *
	 * @param data Floatdaten.
	 */
  Point3f(float* data) : x(*data), y(*(data+1)), z(*(data+2)) {
  }
   
	/** Erzeugt einen neuen Vector.
	 *
	 * @param _x X
	 * @param _y y
	 * @param _z z
	 */
  Point3f(float _x, float _y, float _z) : x(_x), y(_y), z(_z){
	}

	/** Erzeugt einen neuen Punkt aus einem anderen.
	 *
	 * (Copy constructor).
	 *
	 * @param toCopy Zu kopierender Vector.
	 */
	Point3f(Point3f* toCopy) {
		x = toCopy->x;
		y = toCopy->y;
		z = toCopy->z;
	}


  /** Erzeugt einen neuen Punkt aus einem Vector.
	 *
	 * (Copy constructor).
	 *
	 * @param toCopy Zu kopierender Vector.
	 */
	Point3f(Vector3f* toCopy) {
		x = toCopy->dx;
		y = toCopy->dy;
		z = toCopy->dz;
	}

	/** Raeumt auf. */
	virtual ~Point3f() {}

  
  /** addiert auf this den Vektor v auf
   *
   * @param v der Vecktor
   */
  void add(Vector3f* v) {

    x += v->dx;
    y += v->dy;
    z += v->dz;
  }


  /** Liefert den Vector von p - this.
   *
   * @param p Point3d.
   * 
   * @return Vector3f*
   */
  Vector3f* sub(Point3f* p) {
    return(new Vector3f(p->x - x, p->y - y, p->z - z));
  }
  

	/** Liefert eine Stringrepraesentation von this.
	 *
	 * @return std::string Stringrep.
	 */
	std::string toString() {
		std::ostringstream help;
		help << "Point3f(" << x << ", " << y 
				 << ", " << z << ")" << std::ends;
		std::string res = std::string(help.str());
		return(res);
	}

  /** Setzt die Koordinaten von this auf die von p.
   *
   * @param p Punkt der zu setzen ist.
   */
  void set(Point3f* p) {
//    memcpy(v, p->v, 12);
      x = p->x;
      y = p->y;
      z = p->z;
  }


  /**
   * sind punkt p und this gleich ???
   *
   * @param p ein punkt
   * @return ja oder nein
   */
  bool equals(Point3f* p) {

    if (!((p->x == x) && (p->y == y) && (p->z == z))) {

      return false;

    } else {

      return true;
    }
  }

  /** x-Komponente. */
  float x;
  
  /** y-Komponente. */
  float y;
  
  /** z-Komponente. */
  float z;  

};

#endif // _Point3f_h_
