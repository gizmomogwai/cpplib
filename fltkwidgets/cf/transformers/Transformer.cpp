#include <fltkwidgets/cf/transformers/Transformer.h>



bool Transformer::isVisible(const float position) {
  return true;
}

bool Transformer::useMirror() {
  return true;
}

void Transformer::setColors(const float position, const bool mirror, float* colors) {
  float alpha1 = 1.0f;
  float alpha2 = 1.0f;
  if (mirror) {
    alpha1 = 0.3f;
    alpha2 = 0.0f;
  }
  colors[3] = alpha1;
  colors[7] = alpha1;
  colors[11] = alpha2;
  colors[15] = alpha2;
}

Transform3D Transformer::getSzeneTransformation() {
    Vector3f t(0.0f, -.4f, -5.0f);
    Transform3D res;
    res.setTranslation(&t);
    return res;
}
