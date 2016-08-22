#ifndef _Point4f_h_
#define _Point4f_h_

#include <pragmaincludes.h>

#include <lang/Exception.h>
#include <math.h>
#include <string>
#include <sstream>

/** 3-D Punkt mit homogenen Koordinaten.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-01-18, cKgS, Created.
 *   <li> 2001-04-15, cK, Aus dem SG rausgenommen.
 *   <li> 2001-04-15, cK, setMethode.
 * </ul>
 *
 * @version $Revision: 1.3 $, $Date: 2001/06/21 23:20:43 $
 *
 * @author cKgS, $Author: koestlin $
 */
class Point4f {

 public:

	/** Erzeugt einen neuen Punkt _OHNE_ initialisierung. 
	 */
	Point4f() {
	}
   
	/** Erzeugt einen neuen Vector.
	 *
	 * @param _x X
	 * @param _y y
	 * @param _z z
	 */
  Point4f(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {
	}

	/** Erzeugt einen neuen Vector aus einem anderen.
	 *
	 * (Copy constructor).
	 *
	 * @param toCopy Zu kopierender Vector.
	 */
  Point4f(Point4f* toCopy) 
    : x(toCopy->x), y(toCopy->y), z(toCopy->z), w(toCopy->w) {
	}
  

	/** Liefert eine Stringrepraesentation von this.
	 *
	 * @return std::string Stringrep.
	 */
	std::string toString() {
		std::ostringstream help;
		help << "Point4f(" << x << ", " << y 
				 << ", " << z << ", " << w << ")" << std::ends;
		std::string res = std::string(help.str());
		return(res);
	}

  /** Setzt die Daten von this auf die von p.
   *
   * @param p Anderer Punkt.
   */
  void set(Point4f* p) {
//    memcpy(v, p->v, 16);
      x = p->x;
      y = p->y;
      z = p->z;
      w = p->w;
  }

  
  /** x-Komponente. */
  float x;
		
  /** y-Komponente. */
  float y;
  
  /** z-Komponente. */
  float z;  
  
  /** w-Komponente. */
  float w;

  /** Raeumt auf. */
  virtual ~Point4f() {}
  
};

#endif // _Point4f_h_
