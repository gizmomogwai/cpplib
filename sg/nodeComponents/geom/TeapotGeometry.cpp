#include <sg/nodeComponents/geom/TeapotGeometry.h>

TeapotGeometry::~TeapotGeometry() {
}

void TeapotGeometry::accept(Visitor* v) {
  v->visit(this);
}
