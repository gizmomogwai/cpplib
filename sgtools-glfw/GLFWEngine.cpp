#include <sgtools-glfw/GLFWEngine.h>

void GLFWEngine::run() {
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
