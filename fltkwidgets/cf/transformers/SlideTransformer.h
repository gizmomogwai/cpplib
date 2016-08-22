#ifndef SlideTransformer_h_
#define SlideTransformer_h_

#include <fltkwidgets/cf/transformers/Transformer.h>

class SlideTransformer : public Transformer {
 public:
  Transform3D getTransformation(const float flowPosition, const float tilePosition);
 private:
  float position2XOffset(const float position) const;
};

#endif
