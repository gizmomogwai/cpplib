#include <vecmath/Camera.h>

#include <lang/Math.h>

Transform3D* Camera::getProjection() {

  Transform3D* res = new Transform3D();

  // formelsammlung sagt cot = 1/tan
  // oder cot = cos(a) / sin(a)
  double alpha = fieldOfView * Math::A_PI * 0.5;
  float f =  1.0 / tan(alpha);
  float nearSubFar = nearClippingPlane - farClippingPlane;

  res->matrix.m00 = f / aspectRatio;
  res->matrix.m10 = 0;
  res->matrix.m20 = 0;
  res->matrix.m30 = 0;

  res->matrix.m01 = 0;
  res->matrix.m11 = f;
  res->matrix.m21 = 0;
  res->matrix.m31 = 0;

  res->matrix.m02 = 0;
  res->matrix.m12 = 0;
  res->matrix.m22 = (farClippingPlane + nearClippingPlane) / nearSubFar;
  res->matrix.m32 = (2 * farClippingPlane * nearClippingPlane) /  nearSubFar;
  
  res->matrix.m03 = 0;
  res->matrix.m13 = 0;
  res->matrix.m23 = -1;
  res->matrix.m33 = 0;

  return(res);
}


void Camera::setSize(int width, int height) {

  aspectRatio = (float)width / (float)height;
}
