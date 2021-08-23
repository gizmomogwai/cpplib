#include "RotationBehavior.h"

#include <lang/Math.h>
#include <sg/conditions/WakeupOnElapsedFrames.h>
#include <sg/nodes/TGroup.h>
#include <vecmath/Transform3D.h>

RotationBehavior::RotationBehavior(TGroup* _tg) 
  : tg(_tg), angle(0), delta(0.0f) {

  setCondition(new WakeupOnElapsedFrames(1));
}

void RotationBehavior::processStimulus() {
  if (delta != 0.0f) {
    angle += delta;
    if (angle > Math::PI * 2.0f) {
      angle -= Math::PI * 2.0f;
    }

    Transform3D t3d;
    t3d.rotY(angle);

    tg->setTransform(&t3d);
  }
}
   
