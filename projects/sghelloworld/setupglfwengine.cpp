#include <sgtools-glfw/GLFWEngine.h>

Engine* setupEngine(int argc, char** args, int width, int height, const char* title) {
  return new GLFWEngine(width, height, title);
}
