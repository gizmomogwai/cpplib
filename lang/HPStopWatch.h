#pragma once

#include <lang/StopWatch.h>

#if defined(LINUX) || defined(OSX)
  #include <sys/time.h>
  #include <unistd.h>
#endif // LINUX

#include <iostream>

/** Stopuhr die GetTickCount verwendet.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-11-21, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.1 $, $Date: 2002/10/28 23:27:35 $
 *
 * @author cK, $Author: gizmo $
 */
class HPStopWatch : public StopWatch {
 public:
  /** Erzeugt einen neue uninitialisierte Stoppuhr. */
  HPStopWatch();

  /** Raeumt auf. */
  virtual ~HPStopWatch();

  StopWatch& start();

  StopWatch& stop();

  double getDelta();

  /** Liefert die aktuelle Zeit.
   *
   * @return double Zeit.
   */
  double getCurrent();

  /** Berechnet die wirkliche Zeit zwischen 2 Zeitpunkten*/
  double getRealTime(double start, double end);

#if defined(WIN32)
 private:
  /** Wert eines Ticks. */
  double f;

  /** Zeit des letzten Starts. */
  double startTime;

  /** Zeit des letzten Stops. */
  double endTime;
#elif defined(LINUX) || defined(OSX)

  /** Zeit des letzten Starts. */
  struct timeval startTime;

  /** Zeit des letzten Stops. */
  struct timeval endTime;
#else
 #error "please define me"
#endif

};
