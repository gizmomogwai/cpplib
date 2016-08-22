#ifndef CoverFlowTransformer_h_
#define CoverFlowTransformer_h_

#include <fltkwidgets/cf/transformers/Transformer.h>

class CoverFlowTransformer : public Transformer {
 public:
  Transform3D getTransformation(const float flowPosition, const float tilePosition);
 private:
  float position2XOffset(const float position) const;
  float position2ZOffset(const float position) const;
  float position2YRotation(const float position) const;
};

#endif
