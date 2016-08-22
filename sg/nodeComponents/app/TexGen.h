#ifndef _TexGen_h_
#define _TexGen_h_

#ifdef WIN32
  #pragma warning(disable:4786)
#endif // WIN32

#include <sg/nodeComponents/NodeComponent.h>

/** Parameter zur Texturgenerierung.
 *
 * Momentan koennen nur Ebenen fuer die s und die t 
 * Texturkoordinate angegeben werden. 
 *
 * Die Grafikkarte kann unter opengl die Texturcoordinaten automatisch
 * berechnen. Zum einen kann eye-linear gerechnet werden (ist evtl. auch
 * interessant), aber vor allem auch object-linear.
 * 
 * Die Texturkoordinate berechnet sich nun, indem man s bzw. t mit der
 * Koordinate multipliziert. 
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-12-09, cK, Created
 * </ul>
 *
 * @version $Revision: 1.1.1.1 $, $Date: 2001/04/27 14:10:36 $
 *
 * @author cK, $Author: koestlin $
 */
class TexGen : public NodeComponent {

  public:
    /** Erzeugt neue Parameter fuer die Texturgenerierung.
     *
     * @param s0 s-Texturparameter.
     * @param s1 s-Texturparameter.
     * @param s2 s-Texturparameter.
     * @param s3 s-Texturparameter.
     * @param t0 t-Texturparameter.
     * @param t1 t-Texturparameter.
     * @param t2 t-Texturparameter.
     * @param t3 t-Texturparameter.
     */
    TexGen(float s0, float s1, float s2, float s3,
           float t0, float t1, float t2, float t3/*
           float r0, float r1, float r2, float r3*/) {
      s = new float[4];
      s[0] = s0;
      s[1] = s1;
      s[2] = s2;
      s[3] = s3;

      t = new float[4];
      t[0] = t0;
      t[1] = t1;
      t[2] = t2;
      t[3] = t3;
/*
      r = new float[4];
      r[0] = r0;
      r[1] = r1;
      r[2] = r2;
      r[3] = r3;
*/
    }


    /** Parameter fuer die s-Texturkoordinate. */
    float* s;

    /** Parameter fuer die t-Texturkoordinate. */
    float* t;
//    float* r;

  protected:
    /** Raeumt auf. */
    virtual ~TexGen() {
      if (s != 0) {
        delete(s);
        s = 0;
      }
      if (t != 0) {
        delete(t);
        t = 0;
      }
  //    if (r != 0) delete(r);
    }

};

#endif // _TexGen_h_
