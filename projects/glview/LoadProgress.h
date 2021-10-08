#pragma once

#include "sgtools/nodeComponents/behavior/RotationBehavior.h"
#include <sg/nodes/SGObserver.h>

/** Szenengraphast, der dargestellt wird, wenn ein bild geladen und
 * bearbeitet wird.
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
class LoadProgress : public SGObserver {

public:
  /** Erzeugt den Szenegraphenteil. */
  LoadProgress();

  void load() {
    rot->setDelta(0.01f);
  }

  void error() {
    rot->setDelta(0.0f);
  }

protected:
  /** Raeumt auf. */
  virtual ~LoadProgress() {
    rot->releaseReference();
  }

private:
  RotationBehavior* rot;

};
