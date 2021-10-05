#include <sgtools-glfw/GLFWEngine.h>

void GLFWEngine::run() {
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

  while (!glfwWindowShouldClose(window)) {
    ListIterator<Visitor*> i(&visitors);
    while (i.hasNext()) {
      root->accept(i.next());
    }

    glfwSwapBuffers(window);
    glfwPollEvents();

    stats.tick();
    if (stats.count % 50 == 0) {
      stats.dump();
    }
  }

  glfwTerminate();
}
