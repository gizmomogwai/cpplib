#ifndef _Array2f_h_
#define _Array2f_h_

#include <sg/data/TemplateTupelArray.h>

/** Klasse fuer Daten, die 2 float pro eintrag benoetigen.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-12-07, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.1.1.1 $, $Date: 2001/04/27 14:10:36 $
 *
 * @author cK, $Author: koestlin $
 */
class Array2f : public TemplateTupelArray<float> {
  public:
    /** Erzeugt ein FloatArray mit Tupel der groesse 2.
     *
     * @param size Anbzahl von 2er Tupeln.
     */
    Array2f(int size) : TemplateTupelArray<float>(size, 2) {
    }

    /** Setzt ein Tupel.
     *
     * @param idx Index des Tupels.
     * @param v1 1. Wert.
     * @param v2 2. Wert.
     */
    virtual void set(int idx, float v1, float v2) {
      TemplateTupelArray<float>::set(idx * 2, v1);
      TemplateTupelArray<float>::set(idx * 2 +1, v2);
    }

  protected:
    /** Raeumt auf. */
    virtual ~Array2f() {
    }

};

#endif // _Array2f_h_
