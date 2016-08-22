#ifndef ZSlideTransformer_h_
#define ZSlideTransformer_h_

#include <fltkwidgets/cf/transformers/Transformer.h>

class ZSlideTransformer : public Transformer {
 public:
  ZSlideTransformer();
  bool isVisible(const float position);
  bool useMirror();
  Transform3D getTransformation(const float flowPosition, const float tilePosition);
  void setColors(const float position, const bool mirror, float* colors);
  Transform3D getSzeneTransformation();
 private:
  bool fZoom;
};

#endif
