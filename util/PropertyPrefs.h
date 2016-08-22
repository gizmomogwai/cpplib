#ifndef _PropertyPrefs_h_
#define _PropertyPrefs_h_

#include <util/UtilApi.h>

#include <string>

#include <io/DataInputStream.h>

#include <util/Preferences.h>
#include <util/Properties.h>
#include <util/NoSuchElementException.h>

#include <lang/Integer.h>
#include <lang/Long.h>
#include <lang/Float.h>

/** Preferences, die auf Properties beruhen.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-12-31, cK, Created.
 * </ul>
 *
 * @todo ist es ok, wenn man nie 0 zurueckgibt, 
 *       sondern statt dessen eine excpetion wirft??? 
 *       vorteil: einfachere benutzung (== 0 test entfaellt)
 *       nachteil: evtl. exception zur flusssteuerung...
 *
 * @version $Revision: 1.1 $, $Date: 2002/10/28 23:39:49 $
 *
 * @author cK, $Author: gizmo $
 */
class UTIL_API PropertyPrefs : public Preferences {
  
  public:
    /** Liest die Preferences ein. 
     *
     * @param in DataInputStream
     */
    PropertyPrefs(DataInputStream& in);

    /** Raeumt auf. */
    virtual ~PropertyPrefs();
  
    std::string getString(const std::string& key) 
			throw (NoSuchElementException) {

      return p.getProperty(key);
    }

    float getFloat(const std::string& key) 
			throw (NoSuchElementException) {

      std::string help = p.getProperty(key);
      float res = Float::parseFloat(help);
      return res;
    }
    
    int getInt(const std::string& key) 
			throw (NoSuchElementException) {

      std::string help = p.getProperty(key);
      int res = Integer::parseInt(help);
      return res;
    }
    
    long getLong(const std::string& key) 
			throw (NoSuchElementException) {

      std::string help = p.getProperty(key);
      long res = Long::parseLong(help);
      return res;
    }

  private:
    /** Properties, die die Daten halten. */
    Properties p;
  
};

#endif // _PropertyPrefs_h_
