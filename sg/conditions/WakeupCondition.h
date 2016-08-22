#ifndef _WakeupCondition_h_
#define _WakeupCondition_h_

/** Interface fuer alle Conditions.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-01-16, gScK, Created.
 * </ul>
 *
 * @version $Revision: 1.1.1.1 $, $Date: 2001/04/27 14:10:36 $
 *
 * @author gScK, $Author: koestlin $
 */
class WakeupCondition {

	public:
		/** Raeumt auf. */
		virtual ~WakeupCondition() {}

		/** Testet, ob die Bedingung erfuellt ist.
     *
     * @return bool true und false.
     */
		virtual bool evaluate() = 0;

};

#endif // _WakeupCondition_h_
