#ifndef _WakeupOnObserverChange_h_
#define _WakeupOnObserverChange_h_

#include <sg/conditions/WakeupCondition.h>
#include <sg/math/RCTransform3D.h>
#include <vecmath/Transform3D.h>
#include <sg/nodes/SGObserver.h>
#include <util/ReleaseRefCountedObject.h>

/** Condition, die immer, wenn sich der Observer bewegt true liefert.
 * Das ist mit Vorsicht zu geniessen, da mit den 
 * UpdateObjecten gearbeitet wird. SOll heissen, wenn der UpdateVisitor
 * vor dem BehaviorVisitor ueber den graphen laeuft, liefern die 
 * hasChangedMethoden der UpdateObjecte false....
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-09-07, cKgS, Created.
 * </ul>
 *
 * @version $Revision: 1.1 $ $Date: 2001/09/07 13:37:54 $
 *
 * @author cK $Author: koestlin $
 */
class WakeupOnObserverChange : public WakeupCondition {

  public:
    /** Erzeugt eine Condition, die einen Observer "beobachtet"
     *
     * @param _observer SGObserver. Bleibt im besitz des Callers.
     */
    WakeupOnObserverChange(SGObserver* _observer) {
      observer = _observer;
      oldOne.clear();
    }

    /** Raeumt auf. */
    virtual ~WakeupOnObserverChange() {
    }

    bool evaluate() {

      RCTransform3D* current = observer->transform.get();
      ReleaseRefCountedObject<RCTransform3D> cleaner(current);

      if (current->equals(&oldOne) == true) {
        return(false);
      } else {
        oldOne.set(current);
        return(true);
      }        
    }


  private:
    /** SGObserver. */
    SGObserver* observer;

    /** Alte Transform3D. */
    Transform3D oldOne;

};

#endif // _WakeupOnObserverChange_h_
