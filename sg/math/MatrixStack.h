#ifndef _MatrixStack_h_
#define _MatrixStack_h_

#include <vecmath/Transform3D.h>
#include <stack>

/** Stack mit Matrizen, der aehnlich wie der OGLMatrixstack funktioniert.
 *
 * Nicht threadsafe!
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-04-04, cK, Created.
 *   <li> 2001-04-16, cK, An vecmath/Transform3D problematik angepasst.
 * </ul>
 *
 * @version $Revision: 1.2 $, $Date: 2001/08/06 16:08:52 $
 *
 * @author cK, $Author: koestlin $
 */
class MatrixStack {

	public:
		/** Erzeugt einen neuen Matrixstack. */
    MatrixStack() {
    }
		
		/** Raumt auf. */
		virtual ~MatrixStack() {
      clear();
		}

    /** Loescht den ganzen stack. */
    void clear() {
			while (stack.empty() == false) {
        pop();
			}
    }

    /** Bequeme Methode um die ID au´f den Stack zu pushen.
     */
    void pushIdentity() {
      Transform3D* t3d = new Transform3D();
      t3d->setID();
      
      stack.push(t3d);
    }

    /** Liefert das oberste Stackelement.
     *
     * @return Transform3D* Direct, bleibt im Besitz des Stacks.
     *
     * @exception Exception falls der Stack leer ist.
     */
    Transform3D* top() throw (Exception) {
      if (stack.empty() == true) {
        throw(Exception("MatrixStack::top - stack leer", __FILE__, __LINE__));
      }

      Transform3D* t3d = stack.top();
      return(t3d);
    }

    /** Verdoppelt den obersten Stackeintrag.
     *
     * @exception Exception, falls der stack leer ist, 
     *            und somit kein eintrag zum verdoppeln da.
     */
    void push() throw (Exception) {
      if (stack.empty() == true) {
        throw(Exception("MatrixStack::push - stack leer", __FILE__, __LINE__));
      }
      Transform3D* current = top();
      Transform3D* newOne = new Transform3D();
      
      newOne->set(current);

      stack.push(newOne);
    }

    /** Multipliziert den obersten Eintrag mit t3d. Wie in OGL top * t3d.
     *
     * @param t3d Transformation.
     *
     * @exception Exception falls der Stack leer ist.
     */
    void multMatrix(Transform3D* t3d) throw (Exception) {
      Transform3D* current = top();
      stack.pop();

      Transform3D* newOne = new Transform3D();

      newOne->mul(current, t3d);

      stack.push(newOne);
    }

    /** Entfernt das oberste Stackelement.
     *
     * @exception Exception falls kein Element auf dem stack liegt.
     */
    void pop() {
      Transform3D* current = top();
      stack.pop();
      delete(current);
    }

		
	private:
		/** stack mit Transform3Ds. */		
    std::stack<Transform3D*> stack;

};


#endif // _MatrixStack_h_
