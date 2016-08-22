#ifndef Transformer_h_
#define Transformer_h_

#include <vecmath/Transform3D.h>

class Transformer {
 public:
  virtual ~Transformer() {}
  virtual bool isVisible(const float position);
  virtual bool useMirror();
  virtual Transform3D getTransformation(const float flowPosition, const float tilePosition) = 0;
  virtual Transform3D getSzeneTransformation();
  virtual void setColors(const float position, const bool mirror, float* colors);
};

#endif
