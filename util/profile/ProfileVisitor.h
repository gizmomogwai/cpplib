#ifndef _ProfileVisitor_h_
#define _ProfileVisitor_h_

class Profile;
class Profiler;
#include <util/profile/Profiler.h>

/** Visitor von Profiles und Profiler.
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
class ProfileVisitor {

public:
	/** Raeumt auf. */
  virtual ~ProfileVisitor() {
  }

	/** Besucht ein Profile.
	 *
	 * @param profile Profile bleibt im Besitz des Callers.
	 */
	virtual void visit(Profile* profile) = 0;

	/** Besucht einen Profiler.
	 *
	 * @param profiler Profiler bleibt im Besitz des Callers.
	 */
	virtual void visit(Profiler* profiler) = 0;

protected:
	/** Methode, um alle Profiles eines Iterators mit this zu besuchen.
	 *
	 * @param iterator Der Iterator bleibt im Besitz des Callers.
	 */
  void recurse(ProfileIterator* iterator);

};

#endif // _ProfileVisitor_h_
