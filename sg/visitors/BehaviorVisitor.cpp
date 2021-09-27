#include <sg/visitors/BehaviorVisitor.h>

#include <sg/nodes/SGObserver.h>

#include <sg/nodes/Behavior.h>
#include <sg/conditions/WakeupCondition.h>

#include <util/Iterator.h>

#include <iostream>

#include <sg/nodes/Group.h>

void BehaviorVisitor::visit(SGObserver* observer) {
  visit((Group*)observer);
}


void BehaviorVisitor::visit(Group* group) {
  NodeListIterator* i = group->getChilds();
  while (i->hasNext() == true) {
    Node* child = i->next();
    child->accept(this);
  }
  delete i;
}

void BehaviorVisitor::visit(TGroup* tg) {
  visit((Group*)tg);
}

void BehaviorVisitor::visit(Behavior* b) {
  WakeupCondition* c = b->condition;
  if (c->evaluate()) {
    b->processStimulus();
  }
}
