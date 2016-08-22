#include <sg/BoundingBox.h>

BoundingBox::BoundingBox() : lower(0), upper(0) {
}

BoundingBox::BoundingBox(Point3f* _lower, Point3f* _upper) : 
  lower(_lower), upper(_upper) {
}


BoundingBox::~BoundingBox() {

  if (lower != 0) {
    delete(lower);
    lower = 0;
  }

  if (upper != 0) {
    delete(upper);
    upper = 0;
  }
}


// void BoundingBox::transform(Transform3D* t) {
// 
//   t->transformInplace(lower);
//   t->transformInplace(upper);
// }

// void BoundingBox::merge(Bounds* b) {
// }
// 
// bool BoundingBox::intersect(Bounds* b) {
// 
//   return true;
// }
