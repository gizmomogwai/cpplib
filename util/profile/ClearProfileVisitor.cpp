#include <util/profile/ClearProfileVisitor.h>

#include <lang/CleanUpObject.h>
#include <util/Iterator.h>
#include <util/profile/Profile.h>
#include <util/profile/Profiler.h>

#include <util/ListIterator.h>

void ClearProfileVisitor::visit(Profile* profile) {

  profile->clearTotal();

  recurse(profile->iterator());
}

void ClearProfileVisitor::visit(Profiler* profiler) {
  recurse(profiler->iterator());
}
