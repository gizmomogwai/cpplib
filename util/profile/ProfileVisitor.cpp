#include <util/profile/ProfileVisitor.h>

#include <lang/CleanUpObject.h>
#include <util/profile/Profile.h>
#include <util/profile/Profiler.h>

void ProfileVisitor::recurse(ProfileIterator* i) {
  CleanUpObject<ProfileIterator> cleaner(i);
  while (i->hasNext() == true) {
    i->next()->accept(this);
  }
}