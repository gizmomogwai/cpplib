#include <fltkwidgets/cf/transformers/CoverFlowTransformer.h>
#include <vecmath/Vector3f.h>
#include <lang/Math.h>

Transform3D CoverFlowTransformer::getTransformation(const float flowPosition, const float tilePosition) {
  Transform3D res;
  Transform3D rotation;
  Transform3D translation;
  const float delta = tilePosition - flowPosition;
  Vector3f t(position2XOffset(delta), 0, position2ZOffset(delta));
  translation.setTranslation(&t);
  rotation.rotY(position2YRotation(delta));
  res.mul(&translation, &rotation);
  return res;
}

float CoverFlowTransformer::position2XOffset(const float position) const {
  if ((position < 1) && (position > -1)) {
    return position * 1.4f;
  } 
  float p = position;
  float offset = 0;
  if (p > 0) {
    p -= 1;
    offset = 1.4f;
  } else if (p < 0) {
    p += 1;
    offset = -1.4f;
  }
  return offset + p * .4f;
}

float CoverFlowTransformer::position2ZOffset(const float position) const {
  return -fabsf(position) * .4f;
}

float CoverFlowTransformer::position2YRotation(const float position) const {
  float p = position;
  const static float maxRotation = 70;
  float res = -p * maxRotation;
  /*
    float res = 0;
    if (position < 0) {
    res = maxRotation;
    } else {
    res = -maxRotation;
    }
  */
  if (res > maxRotation) {
    res = maxRotation;
  } else if (res < -maxRotation) {
    res = -maxRotation;
  }
  return Math::toRadians(res);
}
