#include <sg/SGObject.h>

SGObject::SGObject() : customData(0) {
}

SGObject::~SGObject() {
  if (customData != 0) {
    std::map<void*, CustomData*>::iterator i = customData->begin();
    while (i != customData->end()) {
      delete(i->second);
      i++;
    }
    delete(customData);
  }
}

void* SGObject::getCustomData(void* key) {
  if (customData == 0) {
    return(0);
  }

  std::map<void*, CustomData*>::iterator found = customData->find(key);
  if (found == customData->end()) {
    return(0);
  } else {
    return(found->second);
  }
}

void SGObject::setCustomData(void* key, CustomData* value) {

  if (customData == 0) {
    customData = new std::map<void*, CustomData*>();
  }

  std::map<void*, CustomData*>::iterator found = customData->find(key);
  if (found != customData->end()) {
    delete(found->second);
    customData->erase(found);
  }

  customData->insert(std::make_pair(key, value));
}
