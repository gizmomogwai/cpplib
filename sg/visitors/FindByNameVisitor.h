#pragma once

#include <sg/nodes/Node.h>
#include <sg/nodes/Group.h>

class FindByNameVisitor : public Visitor {

  public:
    FindByNameVisitor(std::string _name) : name(_name) {}

    virtual ~FindByNameVisitor() {}

    void visit(Node* n) {
      if (n->getName() == name) {
        found = n;
      }
    }

    void visit(Group* g) {
      if (g->getName() == name) {
        found = g;
        return;
      }

      NodeListIterator* i = g->getChilds();
      while (i->hasNext() == true) {
        i->next()->accept(this);
      }
      delete i;
    }

    std::string toString() {
      return("FindByNameVisitor");
    }

    std::string name;
    SGObject* found;
};
