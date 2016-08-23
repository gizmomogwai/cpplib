#include <util/profile/PrintProfileVisitor.h>

#include <lang/CleanUpObject.h>
#include <util/Iterator.h>
#include <util/profile/Profile.h>
#include <util/profile/Profiler.h>

#include <util/ListIterator.h>

void PrintProfileVisitor::visit(Profile* profile) {

  if (offset == 0) {
    currentRoot = profile;
  }

  print(*(profile->getKey()), profile->getTotal(), currentRoot, parent);

  offset++;
  Profile* oldParent = parent;
  parent = profile;

  double childs = 0;
  ProfileIterator* i = profile->iterator();
  CleanUpObject<ProfileIterator> cleaner(i);
  while (i->hasNext() == true) {
    Profile* current = i->next();
    childs += current->getTotal();
    current->accept(this);
  }

  print("selbern", profile->getTotal() - childs, currentRoot, parent);

  offset--;

  parent = oldParent;
}

void PrintProfileVisitor::printSpaces() {
  for (int j = 0; j < offset * 2; j++) {
    (*out) << " ";
  }
}
void PrintProfileVisitor::print(std::string profileName, double profileTotal,
                                Profile* root, Profile* parent) {
  printSpaces();
  (*out) << profileName << "\t\t\t\t\t total: " << profileTotal
         << "\t\t\t\t abs %: " << (profileTotal / root->getTotal() * 100)
         << "\t\t\t\t rel %: "
         << (((parent != 0) ? (profileTotal / parent->getTotal()) : 1) * 100)
         << std::endl;
}

void PrintProfileVisitor::visit(Profiler* profiler) {
  recurse(profiler->iterator());
}
