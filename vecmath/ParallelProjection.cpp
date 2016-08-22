#include <vecmath/ParallelProjection.h>

Transform3D* ParallelProjection::getProjection() {
  Transform3D* res = new Transform3D();

  float tx = - (right + left) / (right - left);
  float ty = - (top + bottom) / (top - bottom);
  float tz = - (farClipping + nearClipping) / (farClipping - nearClipping);

  res->matrix.m00 = 2 / (right - left);
  res->matrix.m10 = 0;
  res->matrix.m20 = 0;
  res->matrix.m30 = tx;

  res->matrix.m01 = 0;
  res->matrix.m11 = 2 / (top - bottom);
  res->matrix.m21 = 0;
  res->matrix.m31 = ty;

  res->matrix.m02 = 0;
  res->matrix.m12 = 0;
  res->matrix.m22 = -2 / (farClipping - nearClipping);
  res->matrix.m32 = tz;

  res->matrix.m03 = 0;
  res->matrix.m13 = 0;
  res->matrix.m23 = 0;
  res->matrix.m33 = 1;

  return(res);
}
