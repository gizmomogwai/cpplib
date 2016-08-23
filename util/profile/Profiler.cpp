#include <util/profile/Profiler.h>

#include <iostream>
#include <lang/CleanUpObject.h>
#include <util/ListIterator.h>
#include <util/profile/ClearProfileVisitor.h>
#include <util/profile/PrintProfileVisitor.h>
#include <util/profile/Profile.h>
#include <util/profile/ProfileVisitor.h>

Profiler Profiler::theProfiler;

Profiler::~Profiler() {}

void Profiler::begin(std::string& key) {

  Profile* profile = 0;
  Profile* parent = 0;

  if (profiles.isEmpty() == false) {
    parent = profiles.top();
  }

  if (parent == 0) {

    profile = searchRootProfile(&key);
    if (profile == 0) {
      // root erzeugen
      profile = new Profile(0, &key);

      // bei roots hinzufuegen
      roots.push_back(profile);
    }
  } else {
    // parent-profile am start .. mal schaun, ob mehr geht
    profile = parent->getProfile(&key);

    // rootprofil am start
    if (profile == 0) {
      // kein konkretes Profil am start
      profile = new Profile(parent, &key);
    }
  }

  // oben auf stack
  profiles.push(profile);

  // und los
  profile->setStart(stopper.getCurrent());
}

Profile* Profiler::searchRootProfile(std::string* key) {

  ProfileIterator* i = iterator();
  CleanUpObject<ProfileIterator> cleaner(i);
  while (i->hasNext() == true) {
    Profile* current = i->next();
    if (current->equals(key) == true) {
      return (current);
    }
  }

  return (0);
}

void Profiler::end(std::string& key) throw(Exception) {

  if (profiles.isEmpty() == true) {
    throw(Exception("So nicht", __FILE__, __LINE__));
  }

  Profile* top = profiles.top();
  if (top->equals(&key) == false) {
    std::cout << "Was soll das???" << key << " top " << *(top->getKey())
              << std::endl;
    throw(Exception("wrong begin end sequence", __FILE__, __LINE__));
  }

  top->setEnd(stopper.getCurrent());
  top->addToTotal(stopper.getRealTime(top->getStart(), top->getEnd()));

  profiles.pop();
}

void Profiler::accept(ProfileVisitor* v) { v->visit(this); }

std::string Profiler::toString() {

  PrintProfileVisitor visitor;

  applyVisitor2Childs(&visitor);

  return (visitor.toString());
}

void Profiler::clear() {
  ClearProfileVisitor visitor;

  applyVisitor2Childs(&visitor);
}

void Profiler::applyVisitor2Childs(ProfileVisitor* visitor) {
  ProfileIterator* i = iterator();
  CleanUpObject<ProfileIterator> cleaner(i);

  while (i->hasNext() == true) {
    i->next()->accept(visitor);
  }
}
