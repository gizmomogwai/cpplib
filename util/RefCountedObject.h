#ifndef _RefCountedObject_h_
#define _RefCountedObject_h_

#include <iostream>

#include <lang/Exception.h>

//#include <util/RefManager.h>
#include <lang/Mutex.h>

/** Object dass einen Referencezaehler verwaltet.
 *
 * Die Objekte sollten nur per releaseReference() "aufgeraeumt" werden,
 * wenn noetig wird der destructor dann von dieser methode aufgerufen.
 * Man kann sich durch ein addReference in den "Besitz" des Objekts
 * bringen.
 *
 * Das Object meldet sich auch an einem RefManager an ... dieser kann alle
 * Momentan referenzierten Objekte auflisten.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2000-12-12, cK, Created.
 *   <li> 2001-03-31, cK, im destructor erst noch das lock vor dem 
 *        zerstoehren befreit ... ob das mal gut ist???
 *   <li> 2001-06-06, cK, Im Destructor den refcounttest nicht mit excpetion bestraft.
 * </ul>
 *
 * @version $Revision: 1.1 $, $Date: 2002/10/28 23:39:49 $
 *
 * @author cK, $Author: gizmo $
 */
class RefCountedObject {
  
  public:
    /** Erzeugt ein neues Referencecounted-OIbject. Und setzt dessen 
     * Referencecount auf 1.
     */
    RefCountedObject() : refCount(1) {
      //      RefManager::getInstance()->add(this);
    }
  
    /** Fuegt dem Referenzcounter 1 hinzu.
     */
    virtual void addReference() {
      refCountLock.lock();
      refCount++;
      refCountLock.unlock();
    }

    /** Gibt eine Reference frei. */
    virtual void releaseReference() {
      refCountLock.lock();
      refCount--;
      if (getCount() == 0) {  
        delete this;
      } else {
        refCountLock.unlock();
      }
    }

    /** Liefert die Anzahl an Referencen auf das Object. 
     *
     * @return int Anzahl von Referenzen (per addReferece).
     */
    virtual int getCount() {
      return refCount;
    }

  protected:
    /** Raeumt auf, falls noetig ... das sollte nicht per delete geschehen, 
     * sondern wird intern per release Reference erledigt.
     */
    virtual ~RefCountedObject() {
      //      RefManager::getInstance()->remove(this);
      if (refCount != 0) {
//        throw(Exception("RefCountedObject::~RefCountedObject - sollte nicht aufgerufen werden"));
        std::cout << "RefCountedObject::~RefCountedObject - sollte nicht aufgerufen werden" << std::endl;
      }
      refCount = 0;
      refCountLock.unlock();
    }

  private:
    /** Der Count. */
    int refCount;
		
    /** Lock fuer den Count. */
    Mutex refCountLock;
  
};

#endif // _RefCountedObjekt_h_
