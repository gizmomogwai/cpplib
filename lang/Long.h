#ifndef _Long_h_
#define _Long_h_

#include <lang/LangApi.h>

#include <string>
#include <sstream>

#include <iomanip>

/** Klasse um mit longs umzugehen.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-12-31, cK, Created.
 *   <li> 2001-02-14, cKtS, parseHex2Long eingebaut.
 * </ul>
 *
 * @todo fehlerbehandlung.
 *
 * @version $Revision: 1.1 $, $Date: 2002/10/28 23:27:35 $
 *
 * @author cK, $Author: gizmo $
 */
class LANG_API Long {

 public:
  /** Parst ein long zu einer bestimmten basis.
   *
   * Es wird ein istrstream zum parsen verwendet.
   *
   * @param in Eingabestring.
   *
   * @return long geparstes long.
   */
  static long parseLong(const std::string& in, int base = 10) {
    std::istringstream h(in.c_str());
    h >> std::setbase(base);
    long res = 0;
    h >> res;
    return res;
  }
      
};

#endif // _Long_h_
