#include <sg/nodes/Behavior.h>

Behavior::Behavior(WakeupCondition* c) : condition(c) {
}

Behavior::Behavior() : condition(0) {
}

Behavior::~Behavior() {
  if (condition != 0) {
    delete(condition);
    condition = 0;
  }
}
void Behavior::setCondition(WakeupCondition* c) throw (Exception) {
  if (condition != 0) {
    throw(Exception("Behavior::setCondition() - so nicht", __FILE__, __LINE__));
  }
  condition = c;
}



