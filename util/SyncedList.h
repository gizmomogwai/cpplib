#ifndef _SyncedList_h_
#define _SyncedList_h_

#include <util/UtilApi.h>

#include <list>
#include <lang/Mutex.h>

/** Liste, die synchronisierbar ist.
 *
 * Nicht die einzelnen Operationen sind synbar sondern die ganze liste als
 * solches. Diese Vorgehensweise wurde gewaehlt, da man so einfacher
 * atomare operationen (aus mehreren Operationen bilden kann) empty() ->
 * front -> pop .
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *  <li> 2001-02-14, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.1 $, $Date: 2002/10/28 23:39:50 $
 *
 * @author cK, $Author: gizmo $
 */
template <class T> class UTIL_API SyncedList : public std::list<T>, public Mutex {
	
 public:
	/** Erzeugt eine neue Liste.
	 */
	SyncedList() : std::list<T>() {
	}
	
	/** Raeumt auf. */
	virtual ~SyncedList() {
	}

};

#endif // _SyncedList_h_
