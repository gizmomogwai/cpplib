#include <sg/visitors/GLUTFontManager.h>

#ifdef OSX
  #include <GLUT/glut.h>
#else
  #include <GL/glut.h>
#endif

void GLUTFontManager::render(Text3D* text3d) {

  glPushMatrix();

  std::string help = text3d->text;
  std::string::iterator i = help.begin();
  while (i != help.end()) {

    glutStrokeCharacter(GLUT_STROKE_ROMAN, (int)(*i++));

  }
  
  glPopMatrix();
}
