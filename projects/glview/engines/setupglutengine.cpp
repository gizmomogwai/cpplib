#include <sgtools-glut/GLUTEngine.h>

Engine* setupEngine(int argc, char** args, int width, int height, const char* title, Root* root) {
  return new GLUTEngine(argc, args, width, height, title, root);
}
