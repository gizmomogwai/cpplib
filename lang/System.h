#ifndef _System_h_
#define _System_h_

#ifdef WIN32
  #include <windows.h>
#endif

/** Systemnahe functionen.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-03-06, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.1 $, $Date: 2002/10/28 23:27:36 $
 *
 * @author cK, $Author: gizmo $
 */
class System {
  
 public:
  /** Faehrt das System herunter. */
  static void shutdown();
  
  /** Startet das System neu. */
  static void reboot();

//  static float getCurrentTimeMicros();
  
 private:
  
#ifdef _WIN32
  /** Hilfsmethode fuer WIN32.
   *
   * @param mode exitWindowsModus (shutdown poweroff oder reboot).
   */
  static void exitWindows(UINT mode);
#endif
  
};


#endif // _System_h_
