#ifndef _Array1i_h_
#define _Array1i_h_

#include <pragmaincludes.h>

#include <lang/Exception.h>

#include <sg/nodeComponents/NodeComponent.h>

#include <sg/data/TemplateTupelArray.h>

/** Oberklasse von Arrays mit jeweils einem int.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-12-23, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.1.1.1 $, $Date: 2001/04/27 14:10:36 $
 *
 * @author cK, $Author: koestlin $
 */
class Array1i : public TemplateTupelArray<int> {
  public:

    /** Erzeugt ein neues Array von ints.
     *
     * @param _size Anzahl von Tupel.
     * @param _tupelSize Anzahl von ints pro Tupel.
     */
    Array1i(int _size) : TemplateTupelArray<int>(_size, 1) {
    } 

  protected:
    /** Raeumt auf. */
    virtual ~Array1i() {
    }
      
};

#endif // _Array1i_h_
