#include <sg/nodes/SwitchGroup.h>

SwitchGroup::SwitchGroup() : fSwitchedIndex(0) {
}

void SwitchGroup::accept(Visitor* v) {
	v->visit(this);
}

int SwitchGroup::getSwitchedIndex() {
	return fSwitchedIndex;
}

void SwitchGroup::setSwitchedIndex(int index) {
	fSwitchedIndex = index;
}

