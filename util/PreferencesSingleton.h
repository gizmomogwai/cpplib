#ifndef _PreferencesSingleton_h_
#define _PreferencesSingleton_h_

#include <lang/Exception.h>

#include <util/Preferences.h>

/** Singleton, das ein Preferences-Object kapselt.
 *
 * So koennen potentiell alle klassen eines programmes auf ein und dasselbe
 * preferences-object abgehen.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-12-31, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.1 $, $Date: 2002/10/28 23:39:49 $
 *
 * @author cK, $Author: gizmo $
 */
class PreferencesSingleton {
  
  public:
    /** Setzt die Instance.
     *
     * @param p Preferences-object.
     *
     * @exception Exception, falls die instance schon gesetzt wurde.
     */
    void setInstance(Preferences* p) throw (Exception) {
      if (instance == 0) {
        instance = p;  
      } else {
        throw(Exception("instance schon gesetzt", __FILE__, __LINE__));
      }
    }
    
    /** Liefert die Instance.
     *
     * @return Preferences* das Prefs-Object.
     *
     * @exception Exception, falls die instance noch nciht gesetzt wurde.
     */
    Preferences* getInstance() throw (Exception) {
      if (instance == 0) {
        throw(Exception("instance noch nciht gesetzt", __FILE__, __LINE__));  
      } 
      return(instance);
    }
      
  private:
  
    /** Instance. */
    static Preferences* instance;  
  
};


#endif // _PreferencesSingleton_h_
