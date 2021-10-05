#include <sgtools/Engine.h>

#include <sg/nodes/Root.h>

void Engine::quit() {
  {
    ListIterator<KeyListener*> i(&keyListeners);
    while (i.hasNext()) {
      delete i.next();
    }
  }

  {
    ListIterator<EngineCleanUp*> i(&cleanups);
    while (i.hasNext()) {
      delete i.next();
    }
  }

  std::cout << "Engine::quit releaseing root" << std::endl;
  if (root != nullptr) {
    root->releaseReference();
    root = nullptr;
  }

  {
    ListIterator<Visitor*> i(&visitors);
    while (i.hasNext()) {
      delete i.next();
    }
  }
  std::cout << "Engine::quit fertig" << std::endl;
}


void Engine::setRoot(Root* _root) {
  if (root != nullptr) {
    root->releaseReference();
  }
  _root->addReference();
  root = _root;
}
