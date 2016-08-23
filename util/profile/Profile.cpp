#include <util/profile/Profile.h>

#include <lang/CleanUpObject.h>
#include <util/ListIterator.h>
#include <util/profile/ProfileList.h>
#include <util/profile/ProfileVisitor.h>

Profile::Profile(Profile* parent, std::string* _key)
    : key(*_key), total(0.0), start(0.0), end(0.0), childs(new ProfileList()) {
  if (parent != 0) {
    parent->addChild(this);
  }
}

Profile::~Profile() { delete (childs); }

void Profile::accept(ProfileVisitor* visitor) { visitor->visit(this); }

void Profile::addChild(Profile* profile) { childs->push_back(profile); }

void Profile::setStart(double theTime) { start = theTime; }

void Profile::setEnd(double theTime) { end = theTime; }

double Profile::getStart() { return (start); }

double Profile::getEnd() { return (end); }

void Profile::addToTotal(double v) { total += v; }

Profile* Profile::getProfile(std::string* key) {
  return (childs->getProfile(key));
}

bool Profile::equals(const std::string* _key) { return ((key == (*_key))); }

ProfileIterator* Profile::iterator() { return (childs->iterator()); }
