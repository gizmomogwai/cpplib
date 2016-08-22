#ifndef _StringTools_h_
#define _StringTools_h_

#include <util/UtilApi.h>

#include <string>

/** Da systemunabhaengig abgegangen werden soll muessen
 * std::string - Objecte verwendet werden.
 * Hier sind nun noch einige Methoden, die einem das Leben
 * noch weiter erleichertern sollen.
 * 
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-01-03, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.1 $, $Date: 2002/10/28 23:39:50 $
 *
 * @author cK, $Author: gizmo $
 */
class UTIL_API StringTools {

 public:
  /** schneidet spaces und tabs vom anfang und end ab!
   *
   * @param src Sourcestring.
   * @param what menge von einzelzeichen die entfernt werden soll.
   *
   * @return std::string* neuer string.
   */
  static std::string* trim(std::string* src, std::string* what);

  /** testet, ob der string src einen character enthaelt.
   *
   * @param src string.
   * @param v gesuchter charakter.
   *
   * @return bool true falls der character enthalten ist.
   */
  static bool contains(std::string* src, char v);
  
};

#endif // _StringTools_h_
