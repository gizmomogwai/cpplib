#ifndef _RotationBehavior_h_
#define _RotationBehavior_h_

#include <sg/nodes/Behavior.h>
class TGroup;

/** Dreht eine Transformgruppe jedes Frame ein wenig weiter.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-09-04, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.1 $ $Date: 2001/09/13 13:11:12 $
 *
 * @author cK $Author: koestlin $
 */
class RotationBehavior : public Behavior {

public:
  /** Erzeugt das Behavior.
   *
   * @param tg TransformGruppe, die manipuliert werden soll.
   */
  RotationBehavior(TGroup* tg, float delta=0.0f);

  void processStimulus();

  RotationBehavior* setDelta(float newDelta) {
    delta = newDelta;
    return this;
  }

protected:
  /** Raeumt auf. */
  virtual ~RotationBehavior() {
  }

  /** Transformationsgruppe, die geaendert werden soll. */
  TGroup* tg;

  /** Aktueller Winkel. */
  float angle;

  /** Delta-Winkel. */
  float delta;

};

#endif // _RotationBehavior_h_
