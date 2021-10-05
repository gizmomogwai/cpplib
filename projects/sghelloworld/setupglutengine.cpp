#include <sgtools-glut/GLUTEngine.h>

Engine* setupEngine(int argc, char** args, int width, int height, const char* title) {
  return new GLUTEngine(argc, args, width, height, title);
}
