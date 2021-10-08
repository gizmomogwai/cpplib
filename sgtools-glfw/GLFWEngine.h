#pragma once

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <sgtools/Engine.h>
#include <sg/visitors/Visitor.h>
#include <lang/HPStopWatch.h>
#include <sg/nodes/Root.h>
#include <sgtools-glfw/GLFWKeyEvent.h>

class GLFWEngine : public Engine {
public:

  GLFWEngine(int _width, int _height, const char* _windowName, Root* _root) : Engine(_root), window(nullptr), width(_width), height(_height), windowName(_windowName) {
    if (!glfwInit()) {
      throw Exception("Cannot initialize glfw");
    }
    /*
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    */
    window = glfwCreateWindow(width, height, windowName, NULL, NULL );
    if (!window) {
      glfwTerminate();
      throw Exception("Cannot create glfw window");
    }
    glfwSetWindowUserPointer(window, this);

    glfwSetFramebufferSizeCallback(window, GLFWEngine::staticSizeCallback);
    glfwSetKeyCallback(window, GLFWEngine::staticKeyCallback);

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSwapInterval(1);

    int w, h;
    glfwGetFramebufferSize(window, &w, &h);

    sizeCallback(w, h);
  }

  void setSize(int _width, int _height) {
    width = _width;
    height = _height;
    glfwSetWindowSize(window, width, height);
  }

  void sizeCallback(int _width, int _height) {
    std::cout << __FILE__ << ":" << __LINE__ << std::endl;

    std::cout << "width " << _width << ", height " << _height << std::endl;
    width = _width;
    height = _height;
    glViewport(0, 0, width, height);
    if (root != nullptr) {
      std::cout << "setting root imagewidht" << "\n";
      std::cout << "_width: " << _width << std::endl;
      std::cout << "_height: " << _height << std::endl;

      root->imageWidth = _width;
      root->imageHeight = _height;
    }
  }

  void quit() {
    std::cout << "GLGWEngine::quit - so jetzt raus" << std::endl;
    if (window != nullptr) {
      glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
  }

  static void staticSizeCallback(GLFWwindow* window, int width, int height) {
    GLFWEngine* engine = (GLFWEngine*)glfwGetWindowUserPointer(window);
    engine->sizeCallback(width, height);
  }

  void keyCallback(int key, int scancode, int action, int mods) {
    std::cout << "key: " << key << ", scancode: " << scancode << ", action: " << action << ", mods: " << mods << std::endl;

    GLFWKeyEvent event(key, scancode, action, mods);
    ListIterator<KeyListener*> i(&(keyListeners));
    while (i.hasNext()) {
      try {
        i.next()->keyPressed(&event);
      } catch (Exception& e) {
        std::cout << "Exception " << e.getMessage() << std::endl;
      } catch (...) {
        std::cout << "noch schlimmer" << std::endl;
      }
    }
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
