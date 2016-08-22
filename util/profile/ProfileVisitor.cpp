#include <util/profile/ProfileVisitor.h>


#include <util/profile/Profiler.h>
#include <lang/CleanUpObject.h>
#include <util/profile/Profile.h>

void ProfileVisitor::recurse(ProfileIterator* i) {
  CleanUpObject<ProfileIterator> cleaner(i);
  while (i->hasNext() == true) {
    i->next()->accept(this);
  }
}