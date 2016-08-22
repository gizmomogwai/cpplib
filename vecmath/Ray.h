#ifndef _Ray_h_
#define _Ray_h_

#include <vecmath/Point3f.h>
#include <vecmath/Vector3f.h>


/** Gerade (Strahl)
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-08-13, gS, Created.
 * </ul>
 *
 * @version $Revision: 1.1 $, $Date: 2001/08/15 15:47:44 $
 *
 * @author gS, $Author: schaefer $
 */
class Ray {

 public:

    /** 
     * Erzeugt eine Gerade (vektoriell)
     * y = p + rv 
     *
     * @param _p der Aufpunkt, bleibt im Besitz des Callers
     * @param _v der Richtungsvektor, bleibt im Besitz des Callers
     */
    Ray(Point3f* _p, Vector3f* _v) 
      : p(new Point3f(_p)), 
        v(new Vector3f(_v)) {
    }
    
    		
    /** Raeumt auf. */
    virtual ~Ray() {

      delete(v);
      delete(p);
    }

    /** 
     * Liefert den Schnittpunkt 2er Geraden.
     * !!!!! Achtung es wird angenommen, dass die beiden
     * Geraden in der xz-Ebene liegen !!!!!!
     * 
     * @param ray zu schneidender Strahl
     *
     * @return Schnittpunkt, falls ex.
     */
    Point3f* intersect(Ray* ray) {

      float dx = (ray->p->x) - p->x;
      float dy = (ray->p->z) - p->z;

      float s = (dy * v->dx - dx * v->dz) / 
                ((ray->v->dx) * v->dz - v->dx * (ray->v->dz));

      Point3f* intersection = new Point3f(ray->p);
      
      Vector3f tmp(ray->v);
      tmp.scale(s);
      
      intersection->add(&tmp);

      return intersection;
    }

    /** der Aufpunkt */
    Point3f* p;

    /** der Richtungsvektor */
    Vector3f* v;
};

#endif // _Plane_h_
