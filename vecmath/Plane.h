#ifndef _Plane_h_
#define _Plane_h_

#include <vecmath/Point3f.h>
#include <iostream>

/** Ebene.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-04-27, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.4 $, $Date: 2001/07/17 14:22:45 $
 *
 * @author cKgSkT, $Author: schaefer $
 */
class Plane {

 public:
    /** Erzeugt eine Ebene.
     * ax + by + cz + d = 0.
     *
     * @param _a a.
     * @param _b b.
     * @param _c c.
     * @param _d d.
     */
    Plane(float _a, float _b, float _c, float _d) 
//	: coefs.a(_a), coefs.b(_b), coefs.c(_c), coefs.d(_d){
	{
	    coefs.a = _a;
	    coefs.b = _b;
	    coefs.c = _c;
	    coefs.d = _d;
	    
    }
    
    /** Erzeugt uninitialisierte Ebene. */
    Plane() {
    }
		
    /** Raeumt auf. */
    virtual ~Plane() {
    }

    /** Liefert die distance eines Punktes zur Ebene 
     * (Ebene muss normalisiert sein).
     *
     * @param x xKoordinate.
     * @param y yKoordinate.
     * @param z zKoordinate.
     *
     * @return double Distanz zur ebene.
     */
    double distance(float x, float y, float z) {
	return(coefs.a*x + 
	       coefs.b*y + 
	       coefs.c*z + 
	       coefs.d);
    }

    /** Liefert die Distanz eines Punktes zur Ebene 
     * (Ebene muss normalisiert sein).
     *
     * @param p Punkt.
     *
     * @return double Distanz.
     */
    double distance(Point3f* p) {
	return(coefs.a*p->x + 
	       coefs.b*p->y + 
	       coefs.c*p->z + 
	       coefs.d);
    }
    
    /** Normalisierung der Ebene ... ob das mal so richtig ist ...
     * ist aber aus dem Frustumartikel.
     * Vermutung HesseNormalform.
     */
    void normalize() {
      double t = sqrt(coefs.a*coefs.a + 
		      coefs.b*coefs.b + 
		      coefs.c*coefs.c);

      coefs.a /= t;
      coefs.b /= t;
      coefs.c /= t;
      coefs.d /= t;
    }

    
    std::string toString() {

      std::ostringstream help;

      help << "Plane Koeffs: " << coefs.a << " " << coefs.b << " " 
                               << coefs.c << " " << coefs.d << std::endl;
      help << std::ends;
		
      std::string res = std::string(help.str());
		  return(res);
    }
    
    
    union {
	struct {
	    /** a-Komponente. */
	    float a;
	    
	    /** b-Komponente. */
	    float b;
	    
	    /** c-Komponente. */
	    float c;  
	    
	    /** d-Komponente. */
	    float d;
	} coefs;

	/// Alternativer Zugriff
	float v[4];		
	
    };
    
};

#endif // _Plane_h_
