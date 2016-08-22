#include <fltkwidgets/cf/CoverFlowWidget.h>

#include <OpenGL.h>
#include <glu.h>

#include <math.h>
#include <iostream>

#include <lang/CleanUpObject.h>
#include <io/file/FileList.h>
#include <image/Image.h>
#include <image/JpegImage.h>
#include <vecmath/Transform3D.h>
#include <oglhelper/OglMatrixPusher.h>

#include <fltk/run.h>

#include <fltkwidgets/Approacher.h>
#include <fltkwidgets/cf/transformers/Transformer.h>
#include <fltkwidgets/cf/IndexIterator.h>
#include <fltkwidgets/OglTexture.h>

CoverFlowWidget::CoverFlowWidget(int x, int y, int w, int h) 
  : fltk::GlWindow(x, y, w, h, 0),
    fAllFiles(0) {
  fColors = new float[16] ;
  for (int i=0; i<16; i++) {
    fColors[i] = 1.0f;
  }
  fTexCoords = new float[8];
  fTexCoords[0] = 0.0f;
  fTexCoords[1] = 1.0f;
  fTexCoords[2] = 1.0f;
  fTexCoords[3] = 1.0f;
  fTexCoords[4] = 1.0f;
  fTexCoords[5] = 0.0f;
  fTexCoords[6] = 0.0f;
  fTexCoords[7] = 0.0f;
}


void CoverFlowWidget::killOldTextures() {
  VectorIterator<OglTexture*> toKill(&fTexturesToKill);
  while (toKill.hasNext()) {
    OglTexture* texture = toKill.next();
    delete texture;
  }
  fTexturesToKill.clear();
}

void CoverFlowWidget::adaptVertices(float* coords, const unsigned int width, const unsigned int height) {
  // immer von unten 0 bis benoetigte hoehe unter horizontal zentriert!
  float w = width;
  float h = height;
  if (w > h) {
    h = h / w;
    w = 1;
  } else if (h > w) {
    w = w / h;
    h = 1;
  }

  coords[0] = -w/2; coords[1] = 0;
  coords[2] = w/2;  coords[3] = 0;
  coords[4] = w/2;  coords[5] = h;
  coords[6] = -w/2; coords[7] = h;
}

void CoverFlowWidget::renderTexture(OglTexture& texture, const float flowPosition, const float tilePosition, const bool mirror) {
  if (getTransformer().isVisible(tilePosition - flowPosition)) {
    Transform3D transformation = getTransformer().getTransformation(flowPosition, tilePosition);
    getTransformer().setColors(tilePosition - flowPosition, mirror, fColors);

    OglMatrixPusher pusher;
    
    texture.activate();
     
    glMultMatrixf((GLfloat*)transformation.m);  assert(glGetError() == GL_NO_ERROR);
    
    glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);  assert(glGetError() == GL_NO_ERROR);
    
    glEnableClientState(GL_VERTEX_ARRAY);  assert(glGetError() == GL_NO_ERROR);
    glEnableClientState(GL_COLOR_ARRAY);  assert(glGetError() == GL_NO_ERROR);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);  assert(glGetError() == GL_NO_ERROR);
    
    float coords[16];
    adaptVertices(coords, texture.getWidth(), texture.getHeight());
    glVertexPointer(2, GL_FLOAT, 0, coords);  assert(glGetError() == GL_NO_ERROR);
    
    glColorPointer(4, GL_FLOAT, 0, fColors);  assert(glGetError() == GL_NO_ERROR);
    glTexCoordPointer(2, GL_FLOAT, 0, fTexCoords);  assert(glGetError() == GL_NO_ERROR);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);  assert(glGetError() == GL_NO_ERROR);
    
    glPopClientAttrib();  assert(glGetError() == GL_NO_ERROR);
  }
}

void CoverFlowWidget::renderTextureByIdx(int idx, float position, const bool mirror) {
  if (idx < 0) {
    return;
  }

  if ((unsigned int)idx >= fTextures.size()) {
    return;
  }
  
  renderTexture(*fTextures[idx], position, idx, mirror);
}

void CoverFlowWidget::drawCoverFlow(float position, const bool mirror) {
  CleanUpObject<IndexIterator> i(getIndexIteratorFactory().get(position));
  while (i->hasNext()) {
    int nextI = i->next();
    renderTextureByIdx(nextI, position, mirror);
  }
}

void CoverFlowWidget::draw() {
  killOldTextures();

  glViewport(0, 0, w(), h());
  
  glEnable(GL_FOG);
  static const float fogColor[] = {0.0f, 0.0f, 0.0f, 1.0f};
  glFogfv(GL_FOG_COLOR, fogColor);
  glFogf(GL_FOG_START, 6.0f);
  glFogf(GL_FOG_END, 8.0f);
  glFogi(GL_FOG_MODE, GL_LINEAR);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(15, static_cast<float>(w())/static_cast<float>(h()), 1, 5000);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  Transform3D szeneTransformation = getTransformer().getSzeneTransformation();
  glMultMatrixf((GLfloat*)szeneTransformation.m);  assert(glGetError() == GL_NO_ERROR);

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_TEXTURE_2D);
  drawCoverFlow(getCurrentPosition(), false);
  
  if (getTransformer().useMirror()) {
    glMatrixMode(GL_MODELVIEW);
    glScalef(1.0f, -1.0f, 1.0f);
    drawCoverFlow(getCurrentPosition(), true);
  }
}

void CoverFlowWidget::fillTextures(FileList& files) {
  VectorIterator<File*> i(&files);
  while (i.hasNext()) {
    File* f = i.next();
    fTextures.push_back(new OglTexture(f->toString()));
  }
} 

bool CoverFlowWidget::newFiles(FileList& newFiles) const {
  if (fAllFiles) {
    VectorIterator<File*> i1(&newFiles);
    VectorIterator<File*> i2(fAllFiles);
    while (i1.hasNext() && i2.hasNext()) {
      File* f1 = i1.next();
      File* f2 = i2.next();
      if (f1->getPathName() != f2->getPathName()) {
	return true;
      }
    }
    return false;
  }
  return true;
}

void CoverFlowWidget::setFiles(FileList& files) {
  if (newFiles(files)) {
    setChanged(true);

    fTexturesToKill = fTextures;
    fTextures.clear();
    delete fAllFiles;
    fAllFiles = files.duplicate();
    fillTextures(*fAllFiles);
  }
}

void CoverFlowWidget::update() {
  redraw();
}
