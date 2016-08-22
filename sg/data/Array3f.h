#ifndef _Array3f_h_
#define _Array3f_h_

#include <pragmaincludes.h>

#include <sg/data/TemplateTupelArray.h>
         
/** Klasse fuer Daten, die 3 float pro eintrag benoetigen.
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
class Array3f : public TemplateTupelArray<float> {
  public:  
    /** Erzeugt ein FloatArray mit Tupel der groesse 3.
     *
     * @param size Anbzahl von 3er Tupeln.
     */
    Array3f(int size) : TemplateTupelArray<float>(size, 3) {
    }

    /** Alternativer Konstructor, der die Daten nciht selbst allokiert, sonder
     * fremde Daten verwaltet.
     *
     * @param size Anzahl von 3er Tupeln.
     * @param _data Daten.
     */
    Array3f(int size, float* _data) : TemplateTupelArray<float>(size, 3, _data) {
    }

    /** Setzt ein Tupel.
     *
     * @param idx Index des Tupels.
     * @param v1 1. Wert.
     * @param v2 2. Wert.
     * @param v3 3. Wert.
     */
    virtual void set(int idx, float v1, float v2, float v3) {
      int h = idx * 3;
      TemplateTupelArray<float>::set(h, v1);
      TemplateTupelArray<float>::set(h + 1, v2);
      TemplateTupelArray<float>::set(h + 2, v3);
    }

  protected:
		/** Raeumt auf. */
    virtual ~Array3f() {
    }

};

#endif // _Array3f_h_
