#ifndef OglTexture_h_
#define OglTexture_h_

#include "OpenGL.h"
#include <string>
class Image;

class OglTexture {
public:
  OglTexture(const std::string fileName, bool thumb=true);
  // must be called from ogl rendering context
  ~OglTexture();
  void killBorder(Image& image);
  void activate();
  unsigned int getWidth();
  unsigned int getHeight();
private:
  std::string fFileName;
  GLuint fId;
  unsigned int fWidth;
  unsigned int fHeight;
  bool fFailed;
  bool fThumb;
};

#endif
