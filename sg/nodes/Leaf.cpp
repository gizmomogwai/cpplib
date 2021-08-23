#include <sg/nodes/Leaf.h>

Leaf::Leaf() : Node() {
}

Leaf::~Leaf() {
}

void Leaf::accept(Visitor* v) {
  v->visit(this);
}

std::string Leaf::toString() {
  return "Leaf";
}


