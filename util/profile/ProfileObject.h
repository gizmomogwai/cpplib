#ifndef _ProfileObject_h_
#define _ProfileObject_h_

#include <util/profile/Profiler.h>
#include <string>

/** Einfaches Hilfsobjekt, dass statisch angelegt werden kann 
 * und entsprechende begins und ends ausloesst.
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
class ProfileObject {

  public:
    /** Erzeugt ein ProfileObject mit einem Namen.
     *
     * @param _key Schluessel.
     */
	  ProfileObject(std::string _key) : key(_key) {
		  Profiler::getInstance()->begin(_key);
	  }

    /** Raeumt auf. */
	  virtual ~ProfileObject() {
		  Profiler::getInstance()->end(key);
	  }

  private:
    /** Der Schluessel. */
	  std::string key;

};

#endif // _ProfileObject_h_
