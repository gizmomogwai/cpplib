#include <fltkwidgets/cf/transformers/ZSlideTransformer.h>
#include <vecmath/Transform3D.h>
#include <lang/Math.h>

ZSlideTransformer::ZSlideTransformer() : fZoom(true) {
}
bool ZSlideTransformer::isVisible(const float position) {
  if (position < -1) {
    return false;
  }
  return true;
}

bool ZSlideTransformer::useMirror() {
  return false;
}

Transform3D ZSlideTransformer::getTransformation(const float flowPosition, const float tilePosition) {
  Transform3D res;
  float z = 0;
  const float delta = tilePosition - flowPosition;
  if (delta > 0) {
    z = -delta * 0.5f;
  } else if (delta > -1) {
    if (fZoom) {
      z = -delta * 5.0f;
    } else {
      z = -delta * 0.5f;
    }
  }

  Vector3f t(0, 0, z);
  res.setTranslation(&t);
  return res;
}

Transform3D ZSlideTransformer::getSzeneTransformation() {
    Vector3f t(0.0f, -.4f, -5.0f);
    Transform3D translation;
    translation.setTranslation(&t);

    Vector3f rot(0, Math::toRadians(-10.0f), 0);
    Transform3D rotation;
    rotation.setEulerXYZ(&rot);

    Transform3D res;
    res.mul(&translation, &rotation);
    return res;
}

void ZSlideTransformer::setColors(const float position, const bool mirror, float* colors) {
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
