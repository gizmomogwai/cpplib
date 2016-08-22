#ifndef _ClearProfileVisitor_h_
#define _ClearProfileVisitor_h_

#include <util/UtilApi.h>

#include <util/profile/ProfileVisitor.h>

/** ProfileVisitor, der die Totalzeiten in den Profiles loescht.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-09-06, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.1 $ $Date: 2002/10/28 23:39:50 $
 *
 * @author cK $Author: gizmo $
 */
class UTIL_API ClearProfileVisitor : public ProfileVisitor {

  public:

    /** Raeumt auf. */
	  virtual ~ClearProfileVisitor() {
	  }

	  void visit(Profile* profile);

    void visit(Profiler* profiler);
};


#endif // _ClearProfileVisitor_h_
