#include <sgtools/Engine.h>

#include <sg/nodes/Root.h>

void Engine::quit() {
  ListIterator<KeyListener*> i2(&keyListeners);
  while (i2.hasNext() == true) {
    delete(i2.next());
  }

  ListIterator<EngineCleanUp*> i3(&cleanups);
  while (i3.hasNext() == true) {
    delete(i3.next());
  }

  std::cout << "Engine::quit releaseing root" << std::endl;
  if (root != 0) {
    root->releaseReference();
    root = 0;
  }

  ListIterator<Visitor*> i1(&visitors);
  while (i1.hasNext() == true) {
    delete(i1.next());
  }
  std::cout << "Engine::quit fertig" << std::endl;
}


void Engine::setRoot(Root* _root) {
  if (root != 0) {
    root->releaseReference();
  }
  _root->addReference();
  root = _root;
}
