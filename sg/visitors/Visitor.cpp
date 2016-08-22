#include <sg/visitors/Visitor.h>

#include <sg/nodes/Group.h>
#include <sg/nodes/Shape3D.h>
#include <sg/nodeComponents/app/Appearance.h>
#include <sg/nodeComponents/geom/Geometry.h>

void Visitor::visit(Group* group) {
  NodeListIterator* i = group->getChilds();
  while (i->hasNext() == true) {
    Node* child = i->next();
    child->accept(this);
  }
  delete(i);
}


void Visitor::visit(Shape3D* s3d) {

  GeometryListIterator* geoms = s3d->getGeometries();
  while (geoms->hasNext() == true) {
    geoms->next()->accept(this);
  }
  delete(geoms);

  Appearance* app = s3d->getAppearance();
  if (app != 0) {
    app->accept(this);
    app->releaseReference();
  }
}

