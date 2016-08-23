#pragma once

#include <string>
#include <sstream>

#include <lang/Exception.h>

/** Utilityklasse um mit Floats umzugehen.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-12-31, cK, Created.
 *   <li> 2001-02-07, cK, Exception, falls in == 0.
 *   <li> 2001-07-14, cK, MAX_VALUE richtig gemacht.
 * </ul>
 *
 * @version $Revision: 1.1 $, $Date: 2002/10/28 23:27:35 $
 *
 * @author cK, $Author: gizmo $
 */
class Float {
  
 public:
  /** Parst ein float.
   *
   * Zum parsen wird ein istrstream verwendet.
   *
   * @param in zu parsender string.
   *
   * @return float float.
   */
  static float parseFloat(const std::string& in) {
    std::istringstream h(in.c_str());
    float res = 0;
    h >> res;
		
    return res;  
  }

  /** Maximalvalues fuer Floats. */
  static const float MAX_VALUE;

  
};
