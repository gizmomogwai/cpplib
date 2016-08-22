#include <fltkwidgets/cf/transformers/SlideTransformer.h>

Transform3D SlideTransformer::getTransformation(const float flowPosition, const float tilePosition) {
  Transform3D res;
  const float delta = tilePosition - flowPosition;
  Vector3f t(position2XOffset(delta), 0, 0);
  res.setTranslation(&t);
  return res;
}

float SlideTransformer::position2XOffset(const float position) const {
  if (position < -1) {
    return position - 0.2f;
  } else if (position > 1) {
    return position + 0.2f;
  } else {
    return position * 1.2f;
  }
}
