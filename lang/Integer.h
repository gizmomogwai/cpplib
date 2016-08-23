#pragma once

#include <string>
#include <sstream>

/** einige hilfsmethoden um mit ints zu arbeiten.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-12-31, cK, Created.
 *   <li> 2001-07-14, cK, MAX_VALUE richtig gemacht.
 * </ul>
 *
 * @todo fehlerbehandlung.
 *
 * @version $Revision: 1.1 $, $Date: 2002/10/28 23:27:35 $
 *
 * @author cK, $Author: gizmo $
 */
class Integer {

 public:
  /** Parst ein int.
   *
   * Zum parsen wird ein istrstream verwendet.
   *
   * @paran in zu parsender string.
   *
   * @return int integer.
   */
  static int parseInt(const std::string& in) {
    std::istringstream h(in.c_str());
    int res = 0;
    h >> res;
    return res;
  }

  /** Maximalvalues fuer integer. */
  static const int MAX_VALUE;
  
};
