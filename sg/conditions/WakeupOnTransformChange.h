#ifndef _WakeupOnTransformChange_h_
#define _WakeupOnTransformChange_h_

#include <sg/conditions/WakeupCondition.h>
#include <sg/math/RCTransform3D.h>
#include <vecmath/Transform3D.h>
#include <util/ReleaseRefCountedObject.h>
#include <sg/nodes/TGroup.h>

/** Condition, die immer, wenn sich eine Transformation in einer
 * TGroup aendert true liefert.
 * Das ist mit Vorsicht zu geniessen, da mit den 
 * UpdateObjecten gearbeitet wird. SOll heissen, wenn der UpdateVisitor
 * vor dem BehaviorVisitor ueber den graphen laeuft, liefern die 
 * hasChangedMethoden der UpdateObjecte false....
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-01-18, cKgS, Created.
 *   <li> 2001-03-04, cKgS, Vergleich nicht mehr mit hasChanged, 
 *                    sondern auch per Value.
 *   <li> 2001-04-16, cK, an vecmath/Transform3D angepasst.
 *   <li> 2001-09-05, cK, Statt SGObserver TGroup
 * </ul>
 *
 * @version $Revision: 1.3 $, $Date: 2001/09/07 13:37:54 $
 *
 * @author cKgS, $Author: koestlin $
 */
class WakeupOnTransformChange : public WakeupCondition {

  public:
    /** Erzeugt eine Condition, die eine TGroup "beobachtet"
     *
     * @param _tg Transformgruppe, die beobachtet werden soll. 
     *        Bleibt im Besitz des Callers.
     */
    WakeupOnTransformChange(TGroup* _tg) {
      tg = _tg;
      oldOne.clear();
    }

    /** Raeumt auf. */
    virtual ~WakeupOnTransformChange() {
    }

    bool evaluate() {

      RCTransform3D* current = tg->getTransform();
      ReleaseRefCountedObject<RCTransform3D> cleaner(current);

      if (current->equals(&oldOne) == true) {
        return(false);
      } else {
        oldOne.set(current);
        return(true);
      }        
    }


  private:
    /** Transformgruppe. */
    TGroup* tg;

    /** Alte Transform3D. */
    Transform3D oldOne;

};

#endif // _WakeupOnTransformChange_h_
