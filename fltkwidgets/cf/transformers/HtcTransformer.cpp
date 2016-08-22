#include <fltkwidgets/cf/transformers/HtcTransformer.h>
#include <lang/Math.h>

Transform3D HtcTransformer::getTransformation(const float flowPosition, const float tilePosition) {
  Transform3D res;
  Transform3D rotation;
  Transform3D translation;
  Vector3f t(.5f, 0, 0.0f);
  const float delta = tilePosition - flowPosition;
  translation.setTranslation(&t);
  rotation.rotX(position2XRotation(delta));
  res.mul(&translation, &rotation);
  return res;
}

bool HtcTransformer::isVisible(const float position) {
  return position >= -1;
}

float HtcTransformer::position2ZOffset(const float position) const {
  return -fabsf(position) * .6f;
}

float HtcTransformer::position2XRotation(const float position) const {
  return Math::toRadians(position / 10.0f * 90.0f);
}

Transform3D HtcTransformer::getSzeneTransformation() {
    Vector3f t(-.3f, -.4f, -5.0f);
    Transform3D translation;
    translation.setTranslation(&t);

    Vector3f rot(0, Math::toRadians(-45.0f), 0);
    Transform3D rotation;
    rotation.setEulerXYZ(&rot);

    Transform3D res;
    res.mul(&translation, &rotation);
    return res;

}


void HtcTransformer::setColors(const float position, const bool mirror, float* colors) {
  float alpha = 0.0f;
  if (position >= 0) {
    alpha = 1.0f;
  } else if (position > -1) {
    alpha = position + 1.0f;
  }
  colors[3] = alpha;
  colors[7] = alpha;
  colors[11] = alpha;
  colors[15] = alpha;    
}
