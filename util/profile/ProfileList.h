#ifndef _ProfileList_h_
#define _ProfileList_h_

#include <list>
#include <util/profile/Profile.h>
#include <util/ListIterator.h>
#include <util/Iterator.h>


class ProfileList;

/** Iterator ueber profiles.
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
class ProfileIterator : public ListIterator<Profile*> {

  public:
	/** Erzeugt einen neuen ProfileIterator.
	 *
	 * @param list Liste ueber die Iteriert werden soll bleibt im Besitz des
	 *	 Callers.
	 */
    ProfileIterator(ProfileList* list);

};

/** Liste mit allen vom Profiler angelegten Profiles.
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
class ProfileList : public std::list<Profile*> {

 public:
	/** Raeutm auf. */
	virtual ~ProfileList();

	/** Liefert ein Profile zu einem String.
	 *
	 * @param key Name des gesuchten Profiles.
	 *
	 * @return Profile* Bleibt im Besitz der Liste.
	 */
	Profile* getProfile(std::string* key);

	/** Liefert einen ProfileIterator ueber alle Listenelemente.
	 *
	 * @return ProfileIterator* Iterator muss vom Caller befreit werden.
	 */
  ProfileIterator* iterator() {
    return(new ProfileIterator(this));
  }

};

#endif // _ProfileList_h_
