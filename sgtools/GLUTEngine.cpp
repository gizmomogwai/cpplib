#include <sgtools/GLUTEngine.h>

#include <sg/visitors/Visitor.h>
#include <sg/nodes/Root.h>
#include <lang/Exception.h>
#include <lang/HPStopWatch.h>

GLUTEngine* GLUTEngine::instance = 0;
bool GLUTEngine::forceRedisplay = false;

GLUTEngine::GLUTEngine(int argc, char** args,
                       int _width, int _height,
                       std::string windowName) {
  GLUTEngine::forceRedisplay = false;
  GLUTEngine::instance = this;

  glutInit(&argc, args);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(_width, _height+20);
  glutInitWindowPosition(200, 200);
  fWindow = glutCreateWindow(windowName.c_str());
  glutDisplayFunc(staticDisplayFunc);
  glutReshapeFunc(staticReshapeFunc);

  glutKeyboardFunc(staticKeyPressed);
  glutSpecialFunc(staticSpecialPressed);
}

void GLUTEngine::setSize(int _width, int _height) {
  width = _width;
  height = _height;
  glutReshapeWindow(width, height);
  forceRedisplay = true;
}

#include <lang/HPStopWatch.h>
class Stats {
public:
  Stats() : count(0), stopWatch(new HPStopWatch()) {
  }
  ~Stats() {
    delete stopWatch;
  }
  void tick() {
    auto now = stopWatch->getCurrent();
    stats.push_back(now);
    while (stats.size() > 100) {
      stats.pop_front();
    }
    count++;
  }
  void dump() {
    if (stats.size() == 100) {
      auto i = stats.begin();
      auto startTime = *i;
      for (int idx=0; idx<99; idx++) {
        i++;
      }
      auto endTime = *i;
      std::cout << "time for 100 frames: " << (endTime - startTime) << std::endl;
      std::cout << "time per frame: " << (endTime - startTime) / 100.0 << std::endl;
    }
  }
  int count;
private:
  HPStopWatch* stopWatch;
  std::list<int64_t> stats;
};

Stats stats;
void GLUTEngine::staticDisplayFunc() {
  try {
    ListIterator<Visitor*> i(&(GLUTEngine::instance->visitors));
    while (i.hasNext() == true) {
      Visitor* visitor = i.next();

      if (GLUTEngine::instance->root != 0) {
        // hier zeitmessung einbauen
        /*
        auto stopWatch = new HPStopWatch();
        stopWatch->start();
        */
        GLUTEngine::instance->root->accept(visitor);
        /*
        stopWatch->stop();
        std::cout << "Visitor: " << visitor->toString() << " took " << stopWatch->getDelta() << std::endl;
        delete stopWatch;
        */
      }
      if (forceRedisplay == true) {
        forceRedisplay = false;
        break;
      }
    }
    glutSwapBuffers();
    glutPostRedisplay();

    stats.tick();
    if (stats.count % 50 == 0) {
      stats.dump();
    }
  }
  catch (Exception& e) {
    std::cout << "PROBLEME " << e.getMessage() << std::endl;
  } catch (...) {
    std::cout << "Noch mehr davon" << std::endl;
  }
}

void GLUTEngine::staticReshapeFunc(int _width, int _height) {
  glViewport(0, 0, _width, _height);
  assert(glGetError() == GL_NO_ERROR);

  if (GLUTEngine::instance->root != 0) {
    GLUTEngine::instance->root->imageWidth = _width;
    GLUTEngine::instance->root->imageHeight = _height;
  }
}

void GLUTEngine::staticKeyPressed(unsigned char key, int x, int y) {

  //  std::cout << "GLUTKeyPressed: " << (int)key << std::endl;

  GLUTKeyEvent event(key);
  ListIterator<KeyListener*> i(&(instance->keyListeners));
  while (i.hasNext() == true) {
    try {
      i.next()->keyPressed(&event);
    } catch (Exception& e) {
      std::cout << "Exception " << e.getMessage() << std::endl;
    } catch (...) {
      std::cout << "noch schlimmer" << std::endl;
    }
  }
}

void GLUTEngine::staticSpecialPressed(int key, int x, int y) {
  GLUTKeyEvent event(key);
  ListIterator<KeyListener*> i(&(GLUTEngine::instance->keyListeners));
  while (i.hasNext() == true) {
    i.next()->keyPressed(&event);
  }
}
