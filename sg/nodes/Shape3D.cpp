#include <sg/nodes/Shape3D.h>

#include <util/ReleaseRefCountedObject.h>
#include <sg/nodeComponents/app/Appearance.h>

Shape3D::Shape3D(Geometry* _geom, Appearance* _app) : Leaf() {
  addGeometry(_geom);
  setAppearance(_app);
}

Shape3D::Shape3D() : Leaf() {
}

Shape3D::~Shape3D() {
}

void Shape3D::accept(Visitor* v) {
  v->visit(this);
}

void Shape3D::setFirstGeometry(Geometry* _newOne) {
  geom.m->lock();

  GeometryList* currentOnes = geom.get();
  GeometryList* newOnes = geom.get();

  newOnes = copyAndSet(currentOnes, newOnes);

  _newOne->addReference();

  if (newOnes->size() > 0) {
    if ((*newOnes)[0] != 0) {
      (*newOnes)[0]->releaseReference();
    }
  }

  if (newOnes->size() == 0) {
    newOnes->push_back(_newOne);
  } else {
    (*newOnes)[0] = _newOne;
  }

  if (currentOnes != 0) {
    currentOnes->releaseReference();
  }
  if (newOnes != 0) {
    newOnes->releaseReference();
  }

  geom.m->unlock();
}


void Shape3D::addGeometry(Geometry* _newOne) {
  geom.m->lock();

  GeometryList* currentOnes = geom.get();
  GeometryList* newOnes = geom.getNew();

  newOnes = copyAndSet(currentOnes, newOnes);

  _newOne->addReference();
  newOnes->push_back(_newOne);

  if (newOnes != 0) {
    newOnes->releaseReference();
  }

  if (currentOnes != 0) {
    currentOnes->releaseReference();
  }

  geom.m->unlock();
}

GeometryList* Shape3D::copyAndSet(GeometryList* currentOnes, 
                                  GeometryList* newOnes) {

  GeometryList* res = newOnes;

  if (res == 0) {
    res = new GeometryList();
    if (currentOnes != 0) {
      std::vector<Geometry*>::iterator i = currentOnes->begin();
      while (i != currentOnes->end()) {
        Geometry* g = *i++;
        g->addReference();
        res->push_back(g);
      }
    }
    geom.set(res);
  }

  return(res);
}


Geometry* Shape3D::getFirstGeometry() {
  GeometryList* list = geom.get();
  ReleaseRefCountedObject<GeometryList> listCleaner(list);

  if (list == 0) return(0);

  Geometry* res = *(list->begin());
  res->addReference();
  return(res);
}

void Shape3D::setAppearance(Appearance* _app) {
  app.set(_app);
}

Appearance* Shape3D::getAppearance() {
  return(app.get());
}

std::string Shape3D::toString() {
  return(std::string("Shape3D"));
}
