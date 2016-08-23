#pragma once

#ifdef WIN32
  #define _mutex_
	
  #ifdef _AFX
    #include <afx.h>
  #endif
  #ifdef _COMMAND
    #include <windows.h>
  #endif
#endif // WIN32

#ifdef LINUX
  #include <pthread.h>


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern int pthread_mutexattr_setkind_np(pthread_mutexattr_t*, int);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif // LINUX


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

#ifdef LINUX
	/** Liefert das pthreadmutexobject. 
	 *
	 * @return pthread_mutex_t* die mutex.
	 */
	pthread_mutex_t* getMutex();
#endif

 private:
#ifdef WIN32

#ifdef _mutex_
	/** windows-handle fuer das mutex. */
	HANDLE mutex;	
#endif
#ifdef _criticalSection_
	/** windows sdk CRITICAL_SECTION */
	CRITICAL_SECTION criticalSection;
#endif
#ifdef _cCriticalSection_
	/** mfc CCriticalSection. */
	CCriticalSection criticalSection;
#endif

#endif // WIN32

     
#ifdef LINUX
	/** pthreadmutex. */
	pthread_mutex_t mutex;

	/** pthread mutexattribute (recursive). */
	pthread_mutexattr_t mutexAttr;

#endif // LINUX

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
