#include <sg/visitors/WGLFontManager.h>

#include <iostream>
#include <string>
#include <assert.h>

#ifdef WIN32
#include <wingdi.h>


WGLFontManager::WGLFontManager(float extrusion) {

  std::cout << "WGLFontManager {" << std::endl;

  HDC hdc = wglGetCurrentDC();

  theFont = 0;
  theFont = CreateFont(0, // default height
                       0, // closest match .. albern
                       0, // escape
                       0, // must be the same as escape in win98
                       700, // default weight (bold or not)
                       FALSE, // non italic
                       FALSE, // non underline
                       FALSE, // non strike out
                       ANSI_CHARSET, // ansicharset
                       OUT_DEFAULT_PRECIS, // passt so ungefaehr an specs
                       CLIP_DEFAULT_PRECIS, // default clipping
                       DRAFT_QUALITY, // nicht so schoen ist ok
                       DEFAULT_PITCH | FF_DONTCARE, // pitch and family on defaults
                       "Arial");

  HGDIOBJ selectRes = SelectObject(hdc, theFont);
  assert(selectRes != NULL);

  first = glGenLists(100);
  base = first - ' ';
  totalChars = 100;

  glyphs = new GLYPHMETRICSFLOAT[totalChars];

  BOOL wglRes = wglUseFontOutlines(hdc, ' ', totalChars,  first,
                                   0.5f, extrusion, WGL_FONT_POLYGONS, glyphs);

  assert(wglRes == TRUE);

  std::cout << "} WGLFontManager" << std::endl;
}


WGLFontManager::~WGLFontManager() {

  glDeleteLists(first, 100);

  if (theFont != 0) {
    DeleteObject(theFont);
  }

  delete[](glyphs);
}


void WGLFontManager::render(Text3D* text3d) {

  glPushMatrix();
  glEnable(GL_NORMALIZE);

  std::string text = text3d->text;

  float size = 0;
  for (int i=0; i<text.size(); i++) {
    char help = text[i];
    if ((help >= 0) && (help < totalChars)) {
      size += glyphs[help].gmfCellIncX;
    }
  }
  float offset = size / 2;

  glTranslatef(-offset, 0, 0);
  GLint oldBase = 0;
  glGetIntegerv(GL_LIST_BASE, &oldBase);
  assert(glGetError() == GL_NO_ERROR);

  glListBase(base);
  assert(glGetError() == GL_NO_ERROR);

  glCallLists(text.length(), GL_UNSIGNED_BYTE, text.c_str());
  assert(glGetError() == GL_NO_ERROR);

  glListBase(oldBase);
  assert(glGetError() == GL_NO_ERROR);

  glDisable(GL_NORMALIZE);
  glFrontFace(GL_CCW);

  glPopMatrix();
}

#endif
