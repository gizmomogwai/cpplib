#include <vecmath/bounds/AabbBound.h>

#include <lang/Float.h>
#include <sstream>

AabbBound::AabbBound(AabbBound* a) {
  Point3f newMin(a->getMin());
  newMin.x -= 1;
  newMin.y -= 1;
  newMin.z -= 1;
  Point3f newMax(a->getMax());
  newMax.x += 1;
  newMax.y += 1;
  newMax.z += 1;
  minP.set(&newMin);
  maxP.set(&newMax);
}


AabbBound::AabbBound(Point3f* _minP, Point3f* _maxP) {
	minP.set(_minP);
	maxP.set(_maxP);
}


Bound* AabbBound::transform(Transform3D* t3d) {
  
  Point3f newMin(Float::MAX_VALUE, Float::MAX_VALUE, Float::MAX_VALUE);
  Point3f newMax(-Float::MAX_VALUE, -Float::MAX_VALUE, -Float::MAX_VALUE);

  integrateValues(minP.x, minP.y, minP.z, t3d, &newMin, &newMax);
  integrateValues(minP.x, minP.y, maxP.z, t3d, &newMin, &newMax);
  integrateValues(minP.x, maxP.y, minP.z, t3d, &newMin, &newMax);
  integrateValues(minP.x, maxP.y, maxP.z, t3d, &newMin, &newMax);
  integrateValues(maxP.x, minP.y, minP.z, t3d, &newMin, &newMax);
  integrateValues(maxP.x, minP.y, maxP.z, t3d, &newMin, &newMax);
  integrateValues(maxP.x, maxP.y, minP.z, t3d, &newMin, &newMax);
  integrateValues(maxP.x, maxP.y, maxP.z, t3d, &newMin, &newMax);

//  Transform3D inverse;
//  inverse.set(t3d);
//  inverse.transpose();
//  integrateValues(minP.x, minP.y, minP.z, &inverse, &newMin, &newMax);
//  integrateValues(minP.x, minP.y, maxP.z, &inverse, &newMin, &newMax);
//  integrateValues(minP.x, maxP.y, minP.z, &inverse, &newMin, &newMax);
//  integrateValues(minP.x, maxP.y, maxP.z, &inverse, &newMin, &newMax);
//  integrateValues(maxP.x, minP.y, minP.z, &inverse, &newMin, &newMax);
//  integrateValues(maxP.x, minP.y, maxP.z, &inverse, &newMin, &newMax);
//  integrateValues(maxP.x, maxP.y, minP.z, &inverse, &newMin, &newMax);
//  integrateValues(maxP.x, maxP.y, maxP.z, &inverse, &newMin, &newMax);

  return(new AabbBound(&newMin, &newMax));
}


void AabbBound::integrateValues(float x, float y, float z, 
                                Transform3D* t3d, 
                                Point3f* newMin, Point3f* newMax) {
  Point3f help;
  help.x = x;
  help.y = y;
  help.z = z;
  t3d->transformInplace(&help);

  if (help.x < newMin->x) newMin->x = help.x;
  else if (help.x > newMax->x) newMax->x = help.x;

  if (help.y < newMin->y) newMin->y = help.y;
  else if (help.y > newMax->y) newMax->y = help.y;

  if (help.z < newMin->z) newMin->z = help.z;
  else if (help.z > newMax->z) newMax->z = help.z;
}

std::string AabbBound::toString() {
  std::ostringstream help;
  help << "Aabb {\n  min: " 
       << getMin()->toString() << "\n  max: " 
       << getMax()->toString() << "\n}" << std::ends;
  std::string res(help.str());
  return(res);
}
