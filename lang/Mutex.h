#pragma once

#include <pthread.h>


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern int pthread_mutexattr_setkind_np(pthread_mutexattr_t*, int);

#ifdef __cplusplus
}
#endif /* __cplusplus */


/** Mutex aka Critical Section oder so ...
 *
 * <h2>Linux</h2>
 * Unter linux lockt sich auch ein thread, bzw. der hauptprozess selbst
 * (siehe mutexCheck)
 *
 * <h2>WIN32</h2>
 * das jdk verwendet CRITICAL_SECTION.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-11-20, cK, Created.
 * </ul>
 *
 * @todo errorhandling verbessern gibt aber teils beim system keine
 *       fehlercodes.
 *
 * @version $Revision: 1.1 $, $Date: 2002/10/28 23:27:35 $
 *
 * @author cK, $Author: gizmo $
 */
class Mutex {

 public:
  /** Erzeugt eine neue Mutex. */
  Mutex();

  /** Loescht die Mutex. */
  virtual ~Mutex();

  /** Versucht das Lock zu holen. */
  void lock();

  /** Gibt das Lock frei. */
  void unlock();

  /** Liefert das pthreadmutexobject.
   *
   * @return pthread_mutex_t* die mutex.
   */
  pthread_mutex_t* getMutex();

 private:
  /** pthreadmutex. */
  pthread_mutex_t mutex;

  /** pthread mutexattribute (recursive). */
  pthread_mutexattr_t mutexAttr;

};

class AutoMutex {
  public:
    AutoMutex(Mutex* mutex) : fMutex(mutex) {
      fMutex->lock();
    }

    virtual~ AutoMutex() {
      fMutex->unlock();
    }
  private:
    Mutex* fMutex;
};
