#include <util/profile/ProfileList.h>

#include <lang/CleanUpObject.h>

ProfileIterator::ProfileIterator(ProfileList* list) 
  : ListIterator<Profile*>(list) {
}

ProfileList::~ProfileList() {

  ProfileIterator* i = iterator();
  CleanUpObject<ProfileIterator> cleaner(i);

  while (i->hasNext() == true) {
    delete(i->next());
  }

}

Profile* ProfileList::getProfile(std::string* key) {
	ListIterator<Profile*> i(this);
		
	while (i.hasNext() == true) {
		Profile* current = i.next();
			
		if (current->equals(key) == true) {
			return(current);
		}
	}
	return(0);
}

