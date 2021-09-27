#include <sg/nodes/Group.h>

#include <sstream>

#include <assert.h>

Group::Group() : Node() {
  childs = new UpdateObject<NodeList>();
}

Group::~Group() {
  std::cout << "~Group" << std::endl;
  childs->m->lock();

  clearParents(childs->get());
  clearParents(childs->getNew());

  childs->m->unlock();
  delete childs;
}

void Group::clearParents(NodeList* list) {
  std::cout << "Group:clearParents" << std::endl;
  if (list != 0) {
    ListIterator<Node*> i(list);
    while (i.hasNext() == true) {
      Node* help = i.next();
      help->setParent(0);
    }
    list->releaseReference();
  }
}

void Group::accept(Visitor* v) {
  v->visit(this);
}

void Group::addChild(Node* newOne) {
  if (newOne == 0) {
    throw(Exception("Group::addChild - newOne == 0", __FILE__, __LINE__));
  }
  AutoMutex(childs->m);

  NodeList* newOnes = childs->getNew();
  NodeList* current = childs->get();

  newOnes = copyAndSet(current, newOnes);

  newOne->setParent(this);
  newOne->addReference();
  newOnes->push_back(newOne);

  if (newOnes != 0) {
    newOnes->releaseReference();
  }
  if (current != 0) {
    current->releaseReference();
  }
}

void Group::setChild(Node* n, int idx) {
  AutoMutex(childs->m);

  NodeList* newOnes = childs->getNew();
  NodeList* current = childs->get();

  newOnes = copyAndSet(current, newOnes);

  newOnes->replace(idx, n);

  if (newOnes != 0) {
    newOnes->releaseReference();
  }
  if (current != 0) {
    current->releaseReference();
  }
}


void Group::removeChild(Node* n) {
  AutoMutex(childs->m);

  NodeList* newOnes = childs->getNew();

  NodeList* current = childs->get();

  newOnes = copyAndSet(current, newOnes);

  newOnes->remove(n);
  n->setParent(0);
  n->releaseReference();

  if (current != 0) {
    current->releaseReference();
  }
  if (newOnes != 0) {
    newOnes->releaseReference();
  }
}

NodeListIterator* Group::getChilds() {
  return new NodeListIterator(childs->get());
}

std::string Group::toString() {
  std::ostringstream out;
  out << "Group[" << getChildCount() << "]" << std::ends;
  std::string res(out.str());
  return(res);
}

int Group::getChildCount() {
  NodeList* childList = childs->get();
  if (childList != 0) {
    int res = childList->size();
    childList->releaseReference();
    return res;
  } else {
    return 0;
  }
}

NodeList* Group::copyAndSet(NodeList* oldOne, NodeList* newOne) {
  NodeList* res = newOne;
  if (res == 0) {
    res = new NodeList();
    if (oldOne != 0) {
      ListIterator<Node*> i(oldOne);
      while (i.hasNext() == true) {
        Node* help = i.next();
        help->addReference();
        res->push_back(help);
      }
    }
    childs->set(res);
  } else {
    res->addReference();
  }
  // damit am ende der remove oder addchild
  // releaseReference aufgerufen werden kann
  return res;
}
