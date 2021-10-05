#pragma once

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <sgtools/Engine.h>
#include <sg/visitors/Visitor.h>
#include <lang/HPStopWatch.h>
#include <sg/nodes/Root.h>


class GLFWEngine : public Engine {
public:

  GLFWEngine(int _width, int _height, const char* _windowName) : window(nullptr), width(_width), height(_height), windowName(_windowName) {
  }

  void setSize(int _width, int _height) {
    width = _width;
    height = _height;
    glfwSetWindowSize(window, width, height);
  }

  void sizeCallback(int _width, int _height) {
    std::cout << "width " << _width << ", height " << _height << std::endl;
    width = _width;
    height = _height;
    glViewport(0, 0, width, height);
    assert(glGetError() == GL_NO_ERROR);
    if (root != nullptr) {
      root->imageWidth = _width;
      root->imageHeight = _height;
    }
  }

  static void staticSizeCallback(GLFWwindow* window, int width, int height) {
    GLFWEngine* engine = (GLFWEngine*)glfwGetWindowUserPointer(window);
    engine->sizeCallback(width, height);
  }

  void keyCallback(int key, int scancode, int action, int mods) {
    std::cout << "key: " << key << ", scancode: " << scancode << ", action: " << action << ", mods: " << mods << std::endl;
  }

  static void staticKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    GLFWEngine* engine = (GLFWEngine*)glfwGetWindowUserPointer(window);
    engine->keyCallback(key, scancode, action, mods);
  }

  void run();
private:
  GLFWwindow* window;
  int width;
  int height;
  const char* windowName;

};
