#include <sg/BoundingSphere.h>

BoundingSphere::BoundingSphere() : center(0), radius(0) {
}

BoundingSphere::BoundingSphere(Point3f* _center, float _radius) : 
  center(new Point3f(_center)), radius(_radius) {
}


BoundingSphere::BoundingSphere(BoundingSphere *bSphere) {
  if (bSphere == 0) {
    throw(Exception("BoundingSphere::BoundingSphere - bSphere == 0", 
                    __FILE__, __LINE__));
  }

  center = new Point3f(bSphere->center);

  radius = bSphere->radius;
}


BoundingSphere::BoundingSphere(BoundingBox* bbox) {

  Point3f* lower = bbox->lower;
  Point3f* upper = bbox->upper;

  Vector3f* tmp = lower->sub(upper);
  tmp->scale(0.5);

  Point3f* c = new Point3f(lower);
  c->add(tmp);

  center = c;
  radius = tmp->getLength();

  delete(tmp);
}



BoundingSphere::~BoundingSphere() {

  if (center != 0) {
    delete(center);
    center = 0;
  }
}


void BoundingSphere::transform(Transform3D* t) {

  t->transformInplace(center);
}


//void BoundingSphere::transform(Bounds* b, Transform3D* t) {
//}


//void BoundingSphere::merge(Bounds* b) {
//}
//
//bool BoundingSphere::intersect(Bounds* b) {
//
//  return true;
//}
 
