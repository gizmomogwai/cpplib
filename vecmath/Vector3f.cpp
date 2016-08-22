#include <vecmath/Vector3f.h>

#include <vecmath/Point3f.h>

Vector3f::Vector3f(Point3f* toCopy) {

  dx = toCopy->x;
  dy = toCopy->y;
  dz = toCopy->z;
}

void Vector3f::sub(Point3f* a, Point3f* b) {

  dx = b->x - a->x;
	dy = b->y - a->y;
	dz = b->z - a->z;
}

