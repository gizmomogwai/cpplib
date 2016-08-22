#include <fltkwidgets/cf/transformers/DockTransformer.h>
#include <stdlib.h>

Transform3D DockTransformer::getTransformation(const float flowPosition, const float tilePosition) {
  Transform3D res;
  const float delta = tilePosition - flowPosition;
  Vector3f t(position2XOffset(tilePosition), 0, delta2ZOffset(delta));
  res.setTranslation(&t);
  return res;
}

float DockTransformer::position2XOffset(const float tilePosition) const {
  return tilePosition;  
}

float DockTransformer::delta2ZOffset(const float delta) const {
  const float absDelta = fabs(delta);
  if (absDelta < 2) {
    return (2-absDelta)*0.25f;
  }
  return 0;
}
