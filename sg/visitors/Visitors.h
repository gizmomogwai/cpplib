#pragma once

#include <sg/SGObject.h>
#include <sg/visitors/FindByNameVisitor.h>

SGObject* findByName(SGObject* o, const std::string& name) {
  FindByNameVisitor v(name);
  o->accept(&v);
  return v.found;
}
