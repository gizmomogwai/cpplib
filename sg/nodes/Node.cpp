#include <sg/nodes/Node.h>

#include <sg/nodes/Group.h>
#include <lang/Exception.h>

Node::Node() 
  : SGObject(), parent(0), local2World(0), bound(0) {
}

Node::~Node() {
  if (parent != 0) {
    detach();
  }

  if (local2World != 0) {
    local2World->releaseReference();
    local2World = 0;
  }

	if (bound != 0) {
		delete(bound);
		bound = 0;
	}
}

void Node::setParent(Group* g) {
  if (g != 0) {
    if (parent != 0) {
//      throw(Exception("Node::setParent - parent already set"));
      std::cout << "Hat schon einen parent ... wird das ein leak" << std::endl;
    }
  }
  parent = g;
}

void Node::detach() {
  if (parent == 0) {
//    throw(Exception("Node::detach - nicht im SG"));
  } else {
    Group* g = parent;
    parent = 0;
    g->removeChild(this);
  }
}

void Node::setLocal2World(RCTransform3D* t3d) {

  if (t3d != 0) {
    if (local2World != 0) {
      local2World->releaseReference();
      local2World = 0;
    }

    t3d->addReference();
    local2World = t3d;
  } else {
    std::cout << "ohje17" << std::endl;
  }
}

RCTransform3D* Node::getLocal2World() {
  local2World->addReference();
  return(local2World);
}

std::string Node::toString() {
  return(std::string("Node"));
}

void Node::setBound(Bound* _bound) {
	if (bound != 0) {
		delete(bound);
	}
  bound = _bound;
}
