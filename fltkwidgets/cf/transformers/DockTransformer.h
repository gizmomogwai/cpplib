#ifndef DockTransformer_h_
#define DockTransformer_h_

#include <fltkwidgets/cf/transformers/Transformer.h>

class DockTransformer : public Transformer {
 public:
  Transform3D getTransformation(const float flowPosition, const float tilePosition);
 private:
  float position2XOffset(const float position) const;
  float delta2ZOffset(const float delta) const;
};

#endif
