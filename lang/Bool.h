#pragma once

#include <string>

#include <lang/Exception.h>

/** Bool
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-03-01, cKgS, Created.
 * </ul>
 *
 * @version $Revision: 1.1 $, $Date: 2002/10/28 23:27:35 $
 *
 * @author cKgS, $Author: gizmo $
 */
class Bool {

  public:
    /** Parst einen string in ein bool.
     *
     * "true" wird in true gewandelt, alles andere in false.
     *
     * @param in zu parsender String.
     *
     * @return bool true oder false.
     */
    static bool parseBool(const std::string* in) {

      if (in == 0) {
        throw Exception("Float::parseFloat in == 0", __FILE__, __LINE__);
      }

      bool res = false;
      if ((*in) == "true") {
        res = true;
      }

      return(res);
    }

};
