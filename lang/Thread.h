#pragma once

#include <pthread.h>
#include <lang/Runnable.h>
#include <lang/Exception.h>

/** Kapselt einen nativeThread.
 *
 * Konkret sollte von Thread abgeleitet werden und 
 * die run-Methode ueberschrieben werden.
 * 
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-11-15, cK, Vom Fabians Threadklasse herauskopiert und 
 *        zusammengestrichen (sorry).
 *   <li> 2001-06-02, cK, Runnable hinzugefuegt.
 * </ul>
 *
 * @todo LinuxThread.yield muss richtig gemacht werden.
 * @todo LinuxThread.~ muss richtig gemacht werden????
 *
 * @version $Revision: 1.1 $, $Date: 2002/10/28 23:27:36 $
 *
 * @author cK, $Author: gizmo $
 */
class Thread : public Runnable {
  
 public:
  /** Erzeugt einen neuen Thread. */
  Thread() 
    : runnable(0), threadHandle(0) {
	}

  static int LOW;
  static int NORMAL;
  static int HIGH;

	/** Erzeugt einen neuen Thread, der ein Runnable ausfuehrt. 
	 *
	 * @param _runnable Runnableobjekt, das ausgefuehrt werden soll. Das
	 *	 Runnable bleibt im Besitz des Callers, der Thread raeumt sich selbst
	 *	 auf, sobald das Runnable fertig abgelaufen ist.
	 */
  Thread(Runnable* _runnable) 
    : runnable(_runnable), threadHandle(0) {

    if (runnable == 0) {
      throw(Exception("Runnable == 0", __FILE__, __LINE__));
    }
	}
  
  /** Raeumt auf. */
  virtual ~Thread();
  
  /** resumed den nativeThread. -> startThread und damit run wird
	 * ausgefuehrt. 
	 */ 
  void start();
	
	/** wartet auf die beendigung des threads. 
	 */
	void join();
  
  /** Schickt den Thread eine Anzahl von Millisekunden schlafen. 
   *
   * @param millis Millisekunden.
   */
  static void sleep(unsigned long millis);


  /** Gibt die Kontrolle an einen anderen zum laufen bereiten Thread. 
   */
  static void yield();
  
  /** Muss ueberschrieben werden, um tatsaechlich etwas zu machen. */
  void run() {
  }
  
 private:
  /** Das Runnableobject, das ausgefuehrt wird, falls gesetzt. */
  Runnable* runnable;
  
  /** Threadhandle. */
  pthread_t threadHandle;
  
  /** statische hilffunktion die zum starten des pthreads verwendet wird.
   *
   * @param thread void* auf das ThreadObject.
   */
  static void* startThread(void* arg);  

  /** Statische Hilffunktion die zum Starten einer Runnable-Run-Methode im pthread
   * verwendet wird.
   *
   * @param thread void* auf das ThreadObject.
   */
  static void* startRunnable(void* arg);  

};
