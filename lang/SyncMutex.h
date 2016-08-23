#pragma once

#include <lang/Event.h>

#include <lang/Mutex.h>

/** Klasse die das Synchronisationsverhalten
 * von einem Java-Object nachbilden soll.
 *
 * In Java kann man auf einem Object warten bzw. notifizieren,
 * nur, wenn man vorher das object exklusiv besitzt (man es also 
 * synchronisiert hat).
 *
 * Die semantik sollte eignetlich so sein:
 * <ul>
 *   <li> wait und notify koennen nur nach 
 *        einem lock aufgerufen werden.
 *   <li> wait muss blockieren, vorher jedoch das lock 
 *        freigeben, damit vor dem notify wieder gelockt werden kann.
 * </ul>
 *
 * <h1>Win32</h1>
 * In Windows wird versucht das Verhalten mit einem Event (autoreset)
 * und einer Mutex nachzubilden. es wird setEvent verwendet 
 * (bleibt signalisiert, bis genau ein warter befreit wird) um 
 * das problem zu vermeiden, dass zwischen dem lock und 
 * dem wait in wait ein notify verloren geht.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-01-25, cKgS, Created
 * </ul>
 *
 * @version $Revision: 1.1 $, $Date: 2002/10/28 23:27:36 $
 *
 * @author cKgS, $Author: gizmo $
 */
class SyncMutex {


  public:
    /** Erzeugt die neue Syncmutex. */
    SyncMutex();

    /** Gibt die Mutex frei. */
    virtual ~SyncMutex();

    /** Bringt einen in den Besitz der Mutex. */
    void lock();

    /** Gibt die Mutex frei. */
    void unlock();

    /** Wartet auf ein notify. 
     * Vor diesem Aufruf, muss die Mutex gelockt werden! 
     */
    void wait();

    /** Notifiziert genau einen Warter. 
     * Vor diesem Aufruf, muss die Mutex gelockt werden! 
     */
    void notify();

  private:
#ifdef WIN32
    /** Anzahl von Warter. */
//    int count;
    bool waiting;

    /** Mutex, die verwendet wird, um zu locken. */
    Mutex m;

    /** Event das verwendet wird, um zu signalisieren. */
    Event e;
#endif // WIN32
#ifdef LINUX
    /** Schutzmutex der Condition-Variable. */
    Mutex mutex;

    /** Conditionvariable. */
    pthread_cond_t condition;
#endif

};
