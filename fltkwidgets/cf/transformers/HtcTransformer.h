#ifndef HtcTransformer_h_
#define HtcTransformer_h_

#include <fltkwidgets/cf/transformers/Transformer.h>

class HtcTransformer : public Transformer {
 public:
  Transform3D getTransformation(const float flowPosition, const float tilePosition);
  bool isVisible(const float position);
  bool useMirror() {return false;}
  Transform3D getSzeneTransformation();
  void setColors(const float position, const bool mirror, float* colors);
 private:
  float position2ZOffset(const float position) const;
  float position2XRotation(const float position) const;
};

#endif
