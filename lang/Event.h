#pragma once

#ifdef WIN32
  #ifdef _AFX
    #include <afx.h>
  #endif
  #ifdef _COMMAND
    #include <windows.h>
  #endif
#endif // WIN32

#ifdef LINUX
  #include <pthread.h>
  #include <lang/Mutex.h>
  #include <errno.h>
#endif // LINUX

/** Klasse um einen Signalisierungsmechanismus anzubieten.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-12-??, cK, Created.
 *   <li> 2000-12-29, cK, Commented.
 * </ul>
 *
 * @version $Revision: 1.1 $, $Date: 2002/10/28 23:27:35 $
 *
 * @author cK, $Author: gizmo $
 */
class Event {

 public:
  /** Erzeugt ein neues Event. Warteanfragen blockieren. */
  Event();
  
  /** Raeumt auf. */
  virtual ~Event();
  
  /** Wartet auf ein Event. */
  virtual void wait();
  
  /** Wartet eine zeitlang auf ein event.
   *
   * @param millis anzahl von zu wartenden millis.
   * 
   * @return bool true falls singal erhalten.
   */
  virtual bool wait(unsigned long millis);
  
  /** Signalisiert das Event. */
  virtual void notify();  

  /** Signalisiert das Event, aber so, dass auch ein wait nach einem 
   * notify noch signalisiert wird.
   */
  virtual void setEvent();
	
	void reset();

  
 private:
#ifdef WIN32    
  /** Windows Handle :) */
  HANDLE event;    
#endif // WIN32
  
#ifdef LINUX
  /** Mutex um die condition zu schuetzen. */
  Mutex* mutex;

  /** pthread condition. */
  pthread_cond_t condition;

  /** Event gesetzt. */
  bool eventSet;
#endif

};
