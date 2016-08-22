#include <sg/visitors/Local2WorldCalcVisitor.h>

#include <sg/nodes/Node.h>
#include <sg/nodes/Group.h>
#include <sg/nodes/TGroup.h>


void Local2WorldCalcVisitor::visit(Root* root) {
  matrixStack.clear();
  matrixStack.pushIdentity();
  visit((Group*)root);
}

void Local2WorldCalcVisitor::visit(SGObserver* observer) {
  visit((Group*)observer);
}

void Local2WorldCalcVisitor::visit(Node* n) {
  Transform3D* t3d = matrixStack.top();
  n->setLocal2World(t3d);
}

void Local2WorldCalcVisitor::visit(Group* g) {
  visit((Node*)g);
  // kinder besuchen

  NodeListIterator* i = g->getChilds();
  while (i->hasNext() == true) {
    Node* child = i->next();
    child->accept(this);
  }
  delete(i);
}

void Local2WorldCalcVisitor::visit(TGroup* tg) {
  matrixStack.push();
  Transform3D* t3d = tg->getTransform();
  matrixStack.multMatrix(t3d);
  visit((Group*)tg);
  matrixStack.pop();
}


