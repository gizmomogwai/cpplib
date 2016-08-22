#ifndef _ProfileStack_h_
#define _ProfileStack_h_

#include <util/UtilApi.h>

#include <stack>
class Profile;

/** Stack, der einen CallStack repraesentiert.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-09-05, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.1 $ $Date: 2002/10/28 23:39:50 $
 *
 * @author cK $Author: gizmo $
 */
class UTIL_API ProfileStack {

  public:
	/** Erzeugt einen neuen Stack. */
    ProfileStack() {
    }

		/** Raeumt auf. */
    virtual ~ProfileStack() {
    }

		/** Schiebt ein Profile oben auf den Stack.
		 *
		 * @param profile Profile bleibt im Besitz des Callers.
		 */
    void push(Profile* profile) {
      profiles.push(profile);
    }

		/** Liefert das oberste Profile.
		 *
		 * @return Profile* Oberstes Profile. Caller darf das Profile nicht
		 *		 freigeben, da es dem stack nich gehoert.
		 */
    Profile* top() {
      return(profiles.top());
    }

		/** Entfernt den obersten stackeintrag.
		 */
    void pop() {
      profiles.pop();
    }

		/** Testet, ob der Stack leer ist.
		 *
		 * @return bool true falls der Stack leer ist.
		 */
    bool isEmpty() {
      return(profiles.empty());
    }

		/** Liefert die Anzahl von Elementen auf dem Stack.
		 *
		 * @return int Stackelemente.
		 */
    int size() {
      return(profiles.size());
    }

  private:
		/** Eigentlicher stack mit den Profiles. */
    std::stack<Profile*> profiles;

};

#endif // _ProfileStack_h_
