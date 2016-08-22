#ifndef CoverFlowWidget_h_
#define CoverFlowWidget_h_

#include <fltk/GlWindow.h>
#include <vector>
#include <lang/Mutex.h>
#include <fltkwidgets/Animator.h>

class FileList;
class OglTexture;
class Approacher;
class Transformer;
class IndexIteratorFactory;

/**
 * TODO
 * * sync issues
 * * wirklich multithreaded laden
 * * sternen hintergrund
 * * stage boden
 */
class CoverFlowWidget : public fltk::GlWindow, public Animatable {
 public:
  CoverFlowWidget(int x, int y, int w, int h);
  void setFiles(FileList& files);

 protected:
  virtual Approacher& getApproacher() = 0;
  virtual IndexIteratorFactory& getIndexIteratorFactory() = 0;
  virtual Transformer& getTransformer() = 0;
  virtual Animator& getAnimator() = 0;

 private:
  void killOldTextures();
  void adaptVertices(float* coords, const unsigned int width, const unsigned int height);
  void renderTexture(OglTexture& texture, const float flowPosition, const float tilePosition, const bool mirror);
  void renderTextureByIdx(int idx, float position, const bool mirror);
  void drawCoverFlow(float position, const bool mirror);
  void draw();
  void fillTextures(FileList& files);
  bool newFiles(FileList& newFiles) const;
  void update();
  typedef std::vector<OglTexture*> OglTextures;
  OglTextures fTextures;
  OglTextures fTexturesToKill;
  FileList* fAllFiles;
  float* fColors;
  float* fTexCoords;
};

template<typename A, typename I, typename T>
class CoverFlowWidgetFor : public CoverFlowWidget { 
  
 public:
  CoverFlowWidgetFor(int x, int y, int w, int h) 
    : CoverFlowWidget(x, y, w, h), fAnimator(getApproacher(), *this) {
  }

  Approacher& getApproacher() {
    return fApproacher;
  }
  IndexIteratorFactory& getIndexIteratorFactory() {
    return fIndexIteratorFactory;
  }
  Transformer& getTransformer() {
    return fTransformer;
  }
  Animator& getAnimator() {
    return fAnimator;
  }
  
 private:
  A fApproacher;
  I fIndexIteratorFactory;
  T fTransformer;
  Animator fAnimator;
};

#endif
