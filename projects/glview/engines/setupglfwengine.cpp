#include <sgtools-glfw/GLFWEngine.h>

Engine* setupEngine(int argc, char** args, int width, int height, const char* title, Root* root) {
  return new GLFWEngine(width, height, title, root);
}
