#include <vecmath/Transform3D.h>
#include <math.h>
#include <sstream>
#include <lang/Exception.h>


Transform3D::Transform3D() {
  setID();
}


Transform3D::Transform3D(Transform3D* t3d) {
  set(t3d);
}


Transform3D::~Transform3D() {
}


void Transform3D::set(Transform3D* t3d) {
  (void)memcpy(m, t3d->m, 64);
}


void Transform3D::rotX(double rad) {
  float s = (float)sin(rad);
  float c = (float)cos(rad);

  indices.idx0 = 1;
  indices.idx4 = 0;
  indices.idx8 = 0;
  indices.idx1 = 0;
  indices.idx2 = 0;

  indices.idx5 = c;
  indices.idx6 = -s;
  indices.idx9 = s;
  indices.idx10 = c;
}


void Transform3D::rotY(double rad) {
  float s = (float)sin(rad);
  float c = (float)cos(rad);

  indices.idx5 = 1;
  indices.idx4 = 0;
  indices.idx6 = 0;
  indices.idx1 = 0;
  indices.idx9 = 0;

  indices.idx0 = c;
  indices.idx2 = -s;
  indices.idx8 = s;
  indices.idx10 = c;
}


void Transform3D::rotZ(double rad) {
  float s = (float)sin(rad);
  float c = (float)cos(rad);

  indices.idx10 = 1;
  indices.idx8 = 0;
  indices.idx9 = 0;
  indices.idx2 = 0;
  indices.idx6 = 0;

  indices.idx0 = c;
  indices.idx1 = -s;
  indices.idx4 = s;
  indices.idx5 = c;
}


void Transform3D::setEulerXYZ(Vector3f* v) {
  float a = (float)(cos(v->dx));
  float b = (float)(sin(v->dx));
  float c = (float)(cos(v->dy));
  float d = (float)(sin(v->dy));
  float e = (float)(cos(v->dz));
  float f = (float)(sin(v->dz));

  float ad = a * d;
  float bd = b * d;

  matrix.m00 = c * e;
  matrix.m10 = -c * f;
  matrix.m20 = -d;

  matrix.m01 = -bd * e + a * f;
  matrix.m11 = bd * f + a * e;
  matrix.m21 = -b * c;

  matrix.m02 = ad * e + b * f;
  matrix.m12 = -ad * f + b * e;
  matrix.m22 = a * c;

}


Vector3f* Transform3D::getEuler() {
  Vector3f* res = new Vector3f();

  float angleX = 0;
  float angleY = 0;
  float angleZ = 0;
  angleY = (float)(-asin(indices.idx8));
  float c = cos(angleY);


  if (fabs(c) > 0.005) {
    float x = indices.idx10 / c;
    float y = -indices.idx9 / c;

    angleX = atan2(y, x);

    x = indices.idx0 / c;
    y = -indices.idx4 / c;

    angleZ = atan2(y, x);


  } else {
    angleX = 0;
    float x = indices.idx5;
    float y = indices.idx1;
    angleZ = atan2(y, x);
  }

  angleX = clamp(angleX);
  angleY = clamp(angleY);
  angleZ = clamp(angleZ);

  res->dx = angleX;
  res->dy = angleY;
  res->dz = angleZ;

  return(res);
}


float Transform3D::clamp(float v) {
  /*
  const float PI = (const float)3.1415926535;
  
    while (v < 0) {
    v += 2*PI;
    }
    while (v > 2*PI) {
    v -= 2*PI;
    }
  */
  return v;
}


void Transform3D::setRotation(Transform3D* t3d) {
    matrix.m00 = t3d->matrix.m00;
    if (matrix.m00 > 100) {
      std::cout << "ohje1" << std::endl;
    }
    matrix.m01 = t3d->matrix.m01;
    matrix.m02 = t3d->matrix.m02;

    matrix.m10 = t3d->matrix.m10;
    matrix.m11 = t3d->matrix.m11;
    matrix.m12 = t3d->matrix.m12;

    matrix.m20 = t3d->matrix.m20;
    matrix.m21 = t3d->matrix.m21;
    matrix.m22 = t3d->matrix.m22;
}


void Transform3D::setTranslation(Vector3f* v) {

    matrix.m30 = v->dx;
    matrix.m31 = v->dy;
    matrix.m32 = v->dz;
}


void Transform3D::getTranslation(Vector3f* v) {

  v->dx = matrix.m30;
  v->dy = matrix.m31;
  v->dz = matrix.m32;
}


void Transform3D::lookAt(Vector3f* eye, Vector3f* at, Vector3f* up) {

  Vector3f zAxis;
  zAxis.sub(at, eye);
  zAxis.normalize();

  Vector3f yAxis;

  Vector3f xAxis;

  xAxis.cross(&zAxis, up);
  xAxis.normalize();

  yAxis.cross(&xAxis, &zAxis);
  yAxis.normalize();
  yAxis.scale(-1);

  setID();

  matrix.m00 = xAxis.dx;
  if (matrix.m00 > 100) {
    std::cout << "ohje1" << std::endl;
  }

  matrix.m01 = xAxis.dy;
  matrix.m02 = xAxis.dz;
  matrix.m10 = yAxis.dx;
  matrix.m11 = yAxis.dy;
  matrix.m12 = yAxis.dz;
  matrix.m20 = zAxis.dx;
  matrix.m21 = zAxis.dy;
  matrix.m22 = zAxis.dz;

  matrix.m30 = -eye->dx * m[ 0] - eye->dy * m[ 4] - eye->dz * m[ 8];
  matrix.m31 = -eye->dx * m[ 1] - eye->dy * m[ 5] - eye->dz * m[ 9];
  matrix.m32 = -eye->dx * m[ 2] - eye->dy * m[ 6] - eye->dz * m[10];
}


void Transform3D::lookAt(Vector3f* x, Vector3f* y, Vector3f* z, Vector3f* t) {
  setID();

  matrix.m00 = x->dx;
  matrix.m01 = x->dy;
  matrix.m02 = x->dz;
  if (matrix.m00 > 100) {
    std::cout << "ohje1" << std::endl;
  }

  matrix.m10 = y->dx;
  matrix.m11 = y->dy;
  matrix.m12 = y->dz;

  matrix.m20 = z->dx;
  matrix.m21 = z->dy;
  matrix.m22 = z->dz;

  matrix.m30 = t->dx * x->dx + t->dy * x->dy + t->dz * x->dz;
  matrix.m31 = t->dx * y->dx + t->dy * y->dy + t->dz * y->dz;
  matrix.m32 = t->dx * z->dx + t->dy * z->dy + t->dz * z->dz;
}


void Transform3D::lookAt(Transform3D* t) {
  set(t);
  float* h = t->m;
  matrix.m30 = h[12] * h[ 0] + h[13] * h[ 1] + h[14] * h[ 2];
  matrix.m31 = h[12] * h[ 4] + h[13] * h[ 5] + h[14] * h[ 6];
  matrix.m32 = h[12] * h[ 8] + h[13] * h[ 9] + h[14] * h[10];
}


Transform3D* Transform3D::invertAffine() {
  Transform3D help;
  help.set(this);
  help.lookAt(this);
  Transform3D* res = help.fake();
  return(res);
}


Transform3D* Transform3D::fake() {
  Transform3D* res = new Transform3D();

  res->m[ 0] = m[ 0];
  res->m[ 5] = m[ 5];
  res->m[10] = m[10];
  res->m[15] = m[15];

  res->m[ 1] = m[ 4];
  res->m[ 4] = m[ 1];

  res->m[ 2] = m[ 8];
  res->m[ 8] = m[ 2];

  res->m[ 6] = m[ 9];
  res->m[ 9] = m[ 6];

  res->m[12] = -m[12];
  res->m[13] = -m[13];
  res->m[14] = -m[14];

  res->m[ 3] = 0;
  res->m[ 7] = 0;
  res->m[11] = 0;

  return(res);
}

void Transform3D::setScale(Vector3f* scale) {
    matrix.m00 *= scale->dx;
    matrix.m11 *= scale->dy;
    matrix.m22 *= scale->dz;
}


void Transform3D::set(float scale, Vector3f* translation) {
  setID();
  indices.idx0 = scale;
  indices.idx5 = scale;
  indices.idx10 = scale;
  indices.idx12 = translation->dx;
  indices.idx13 = translation->dy;
  indices.idx14 = translation->dz;
}


void Transform3D::setData(int col, int row, float v) {
  m[col*4 + row] = v;
}


float Transform3D::getData(int col, int row) {
  return(m[col*4+row]);
}


std::string Transform3D::toString() {
  std::ostringstream help;
  help << "Transform3D\n";
  for (int i=0; i<4; i++) {
    help << m[i+0] << ", \t" << m[i+4] << ", \t"
         << m[i+8] << ", \t" << m[i+12] << std::endl;
  }
  help << std::ends;

  std::string res = std::string(help.str());

  return(res);
}


void Transform3D::transformInplace(Point4f* p) {

  float h0;
  float h1;
  float h2;
  float h3;
  h0 = p->x;
  h1 = p->y;
  h2 = p->z;
  h3 = p->w;

  p->x = indices.idx0 * h0 + indices.idx4 * h1 + indices.idx8  * h2 + indices.idx12 * h3;
  p->y = indices.idx1 * h0 + indices.idx5 * h1 + indices.idx9  * h2 + indices.idx13 * h3;
  p->z = indices.idx2 * h0 + indices.idx6 * h1 + indices.idx10 * h2 + indices.idx14 * h3;
  p->w = indices.idx3 * h0 + indices.idx7 * h1 + indices.idx11 * h2 + indices.idx15 * h3;
}

void Transform3D::transformInplace(Point3f* p) {

  float h0;
  float h1;
  float h2;
  float h3;
  h0 = p->x;
  h1 = p->y;
  h2 = p->z;
  h3 = 1;

  p->x = indices.idx0 * h0 + indices.idx4 * h1 + indices.idx8  * h2 + indices.idx12 * h3;
  p->y = indices.idx1 * h0 + indices.idx5 * h1 + indices.idx9  * h2 + indices.idx13 * h3;
  p->z = indices.idx2 * h0 + indices.idx6 * h1 + indices.idx10 * h2 + indices.idx14 * h3;
}


//void Transform3D::mul(Transform3D* t1, Transform3D* t2) {
//  /*
//  // 3301, 3306, 3355, 3312
//  float* m1 = t1->m;
//  float* m2 = t2->m;
//
//  m00 = m1[ 0] * m2[ 0] + m1[ 4] * m2[ 1] + m1[ 8] * m2[ 2] + m1[12] * m2[ 3];
//  m10 = m1[ 0] * m2[ 4] + m1[ 4] * m2[ 5] + m1[ 8] * m2[ 6] + m1[12] * m2[ 7];
//  m20 = m1[ 0] * m2[ 8] + m1[ 4] * m2[ 9] + m1[ 8] * m2[10] + m1[12] * m2[11];
//  m30 = m1[ 0] * m2[12] + m1[ 4] * m2[13] + m1[ 8] * m2[14] + m1[12] * m2[15];
//
//  m01 = m1[ 1] * m2[ 0] + m1[ 5] * m2[ 1] + m1[ 9] * m2[ 2] + m1[13] * m2[ 3];
//  m11 = m1[ 1] * m2[ 4] + m1[ 5] * m2[ 5] + m1[ 9] * m2[ 6] + m1[13] * m2[ 7];
//  m21 = m1[ 1] * m2[ 8] + m1[ 5] * m2[ 9] + m1[ 9] * m2[10] + m1[13] * m2[11];
//  m31 = m1[ 1] * m2[12] + m1[ 5] * m2[13] + m1[ 9] * m2[14] + m1[13] * m2[15];
//
//  m02 = m1[ 2] * m2[ 0] + m1[ 6] * m2[ 1] + m1[10] * m2[ 2] + m1[14] * m2[ 3];
//  m12 = m1[ 2] * m2[ 4] + m1[ 6] * m2[ 5] + m1[10] * m2[ 6] + m1[14] * m2[ 7];
//  m22 = m1[ 2] * m2[ 8] + m1[ 6] * m2[ 9] + m1[10] * m2[10] + m1[14] * m2[11];
//  m32 = m1[ 2] * m2[12] + m1[ 6] * m2[13] + m1[10] * m2[14] + m1[14] * m2[15];
//
//  m03 = m1[ 3] * m2[ 0] + m1[ 7] * m2[ 1] + m1[11] * m2[ 2] + m1[15] * m2[ 3];
//  m13 = m1[ 3] * m2[ 4] + m1[ 7] * m2[ 5] + m1[11] * m2[ 6] + m1[15] * m2[ 7];
//  m23 = m1[ 3] * m2[ 8] + m1[ 7] * m2[ 9] + m1[11] * m2[10] + m1[15] * m2[11];
//  m33 = m1[ 3] * m2[12] + m1[ 7] * m2[13] + m1[11] * m2[14] + m1[15] * m2[15];
//  */
//
///*
//  // 3308, 3319, 3390
//  m00 = t1->idx0 * t2->idx0 + t1->idx4 * t2->idx1 + t1->idx8 * t2->idx2 + t1->idx12 * t2->idx3;
//  m10 = t1->idx0 * t2->idx4 + t1->idx4 * t2->idx5 + t1->idx8 * t2->idx6 + t1->idx12 * t2->idx7;
//  m20 = t1->idx0 * t2->idx8 + t1->idx4 * t2->idx9 + t1->idx8 * t2->idx10 + t1->idx12 * t2->idx11;
//  m30 = t1->idx0 * t2->idx12 + t1->idx4 * t2->idx13 + t1->idx8 * t2->idx14 + t1->idx12 * t2->idx15;
//
//  m01 = t1->idx1 * t2->idx0 + t1->idx5 * t2->idx1 + t1->idx9 * t2->idx2 + t1->idx13 * t2->idx3;
//  m11 = t1->idx1 * t2->idx4 + t1->idx5 * t2->idx5 + t1->idx9 * t2->idx6 + t1->idx13 * t2->idx7;
//  m21 = t1->idx1 * t2->idx8 + t1->idx5 * t2->idx9 + t1->idx9 * t2->idx10 + t1->idx13 * t2->idx11;
//  m31 = t1->idx1 * t2->idx12 + t1->idx5 * t2->idx13 + t1->idx9 * t2->idx14 + t1->idx13 * t2->idx15;
//
//  m02 = t1->idx2 * t2->idx0 + t1->idx6 * t2->idx1 + t1->idx10 * t2->idx2 + t1->idx14 * t2->idx3;
//  m12 = t1->idx2 * t2->idx4 + t1->idx6 * t2->idx5 + t1->idx10 * t2->idx6 + t1->idx14 * t2->idx7;
//  m22 = t1->idx2 * t2->idx8 + t1->idx6 * t2->idx9 + t1->idx10 * t2->idx10 + t1->idx14 * t2->idx11;
//  m32 = t1->idx2 * t2->idx12 + t1->idx6 * t2->idx13 + t1->idx10 * t2->idx14 + t1->idx14 * t2->idx15;
//
//  m03 = t1->idx3 * t2->idx0 + t1->idx7 * t2->idx1 + t1->idx11 * t2->idx2 + t1->idx15 * t2->idx3;
//  m13 = t1->idx3 * t2->idx4 + t1->idx7 * t2->idx5 + t1->idx11 * t2->idx6 + t1->idx15 * t2->idx7;
//  m23 = t1->idx3 * t2->idx8 + t1->idx7 * t2->idx9 + t1->idx11 * t2->idx10 + t1->idx15 * t2->idx11;
//  m33 = t1->idx3 * t2->idx12 + t1->idx7 * t2->idx13 + t1->idx11 * t2->idx14 + t1->idx15 * t2->idx15;
//*/
//
//  /*
//  // 7500
//  Transform3D h1 = *t1;
//  Transform3D h2 = *t2;
//  m00 = h1.idx0 * h2.idx0 + h1.idx4 * h2.idx1 + h1.idx8 * h2.idx2 + h1.idx12 * h2.idx3;
//  m10 = h1.idx0 * h2.idx4 + h1.idx4 * h2.idx5 + h1.idx8 * h2.idx6 + h1.idx12 * h2.idx7;
//  m20 = h1.idx0 * h2.idx8 + h1.idx4 * h2.idx9 + h1.idx8 * h2.idx10 + h1.idx12 * h2.idx11;
//  m30 = h1.idx0 * h2.idx12 + h1.idx4 * h2.idx13 + h1.idx8 * h2.idx14 + h1.idx12 * h2.idx15;
//
//  m01 = h1.idx1 * h2.idx0 + h1.idx5 * h2.idx1 + h1.idx9 * h2.idx2 + h1.idx13 * h2.idx3;
//  m11 = h1.idx1 * h2.idx4 + h1.idx5 * h2.idx5 + h1.idx9 * h2.idx6 + h1.idx13 * h2.idx7;
//  m21 = h1.idx1 * h2.idx8 + h1.idx5 * h2.idx9 + h1.idx9 * h2.idx10 + h1.idx13 * h2.idx11;
//  m31 = h1.idx1 * h2.idx12 + h1.idx5 * h2.idx13 + h1.idx9 * h2.idx14 + h1.idx13 * h2.idx15;
//
//  m02 = h1.idx2 * h2.idx0 + h1.idx6 * h2.idx1 + h1.idx10 * h2.idx2 + h1.idx14 * h2.idx3;
//  m12 = h1.idx2 * h2.idx4 + h1.idx6 * h2.idx5 + h1.idx10 * h2.idx6 + h1.idx14 * h2.idx7;
//  m22 = h1.idx2 * h2.idx8 + h1.idx6 * h2.idx9 + h1.idx10 * h2.idx10 + h1.idx14 * h2.idx11;
//  m32 = h1.idx2 * h2.idx12 + h1.idx6 * h2.idx13 + h1.idx10 * h2.idx14 + h1.idx14 * h2.idx15;
//
//  m03 = h1.idx3 * h2.idx0 + h1.idx7 * h2.idx1 + h1.idx11 * h2.idx2 + h1.idx15 * h2.idx3;
//  m13 = h1.idx3 * h2.idx4 + h1.idx7 * h2.idx5 + h1.idx11 * h2.idx6 + h1.idx15 * h2.idx7;
//  m23 = h1.idx3 * h2.idx8 + h1.idx7 * h2.idx9 + h1.idx11 * h2.idx10 + h1.idx15 * h2.idx11;
//  m33 = h1.idx3 * h2.idx12 + h1.idx7 * h2.idx13 + h1.idx11 * h2.idx14 + h1.idx15 * h2.idx15;
//*/
//
///*
//  // 3622, 3588
//  float* h = m;
//  *h++ = t1->idx0 * t2->idx0 + t1->idx4 * t2->idx1 + t1->idx8 * t2->idx2 + t1->idx12 * t2->idx3;
//  *h++ = t1->idx1 * t2->idx0 + t1->idx5 * t2->idx1 + t1->idx9 * t2->idx2 + t1->idx13 * t2->idx3;
//  *h++ = t1->idx2 * t2->idx0 + t1->idx6 * t2->idx1 + t1->idx10 * t2->idx2 + t1->idx14 * t2->idx3;
//  *h++ = t1->idx3 * t2->idx0 + t1->idx7 * t2->idx1 + t1->idx11 * t2->idx2 + t1->idx15 * t2->idx3;
//
//  *h++ = t1->idx0 * t2->idx4 + t1->idx4 * t2->idx5 + t1->idx8 * t2->idx6 + t1->idx12 * t2->idx7;
//  *h++ = t1->idx1 * t2->idx4 + t1->idx5 * t2->idx5 + t1->idx9 * t2->idx6 + t1->idx13 * t2->idx7;
//  *h++ = t1->idx2 * t2->idx4 + t1->idx6 * t2->idx5 + t1->idx10 * t2->idx6 + t1->idx14 * t2->idx7;
//  *h++ = t1->idx3 * t2->idx4 + t1->idx7 * t2->idx5 + t1->idx11 * t2->idx6 + t1->idx15 * t2->idx7;
//
//  *h++ = t1->idx0 * t2->idx8 + t1->idx4 * t2->idx9 + t1->idx8 * t2->idx10 + t1->idx12 * t2->idx11;
//  *h++ = t1->idx1 * t2->idx8 + t1->idx5 * t2->idx9 + t1->idx9 * t2->idx10 + t1->idx13 * t2->idx11;
//  *h++ = t1->idx2 * t2->idx8 + t1->idx6 * t2->idx9 + t1->idx10 * t2->idx10 + t1->idx14 * t2->idx11;
//  *h++ = t1->idx3 * t2->idx8 + t1->idx7 * t2->idx9 + t1->idx11 * t2->idx10 + t1->idx15 * t2->idx11;
//
//  *h++ = t1->idx0 * t2->idx12 + t1->idx4 * t2->idx13 + t1->idx8 * t2->idx14 + t1->idx12 * t2->idx15;
//  *h++ = t1->idx1 * t2->idx12 + t1->idx5 * t2->idx13 + t1->idx9 * t2->idx14 + t1->idx13 * t2->idx15;
//  *h++ = t1->idx2 * t2->idx12 + t1->idx6 * t2->idx13 + t1->idx10 * t2->idx14 + t1->idx14 * t2->idx15;
//  *h++ = t1->idx3 * t2->idx12 + t1->idx7 * t2->idx13 + t1->idx11 * t2->idx14 + t1->idx15 * t2->idx15;
//*/
//
//  // 3223
//  float* m1 = t1->m;
//  float* m2 = t2->m;
//
//  float f1 = m1[0];
//  float f2 = m1[4];
//  float f3 = m1[8];
//  float f4 = m1[12];
//  m00 = f1 * m2[ 0] + f2 * m2[ 1] + f3 * m2[ 2] + f4 * m2[ 3];
//  m10 = f1 * m2[ 4] + f2 * m2[ 5] + f3 * m2[ 6] + f4 * m2[ 7];
//  m20 = f1 * m2[ 8] + f2 * m2[ 9] + f3 * m2[10] + f4 * m2[11];
//  m30 = f1 * m2[12] + f2 * m2[13] + f3 * m2[14] + f4 * m2[15];
//
//  f1 = m1[1];
//  f2 = m1[5];
//  f3 = m1[9];
//  f4 = m1[13];
//  m01 = f1 * m2[ 0] + f2 * m2[ 1] + f3 * m2[ 2] + f4 * m2[ 3];
//  m11 = f1 * m2[ 4] + f2 * m2[ 5] + f3 * m2[ 6] + f4 * m2[ 7];
//  m21 = f1 * m2[ 8] + f2 * m2[ 9] + f3 * m2[10] + f4 * m2[11];
//  m31 = f1 * m2[12] + f2 * m2[13] + f3 * m2[14] + f4 * m2[15];
//
//
//  f1 = m1[2];
//  f2 = m1[6];
//  f3 = m1[10];
//  f4 = m1[14];
//  m02 = f1 * m2[ 0] + f2 * m2[ 1] + f3 * m2[ 2] + f4 * m2[ 3];
//  m12 = f1 * m2[ 4] + f2 * m2[ 5] + f3 * m2[ 6] + f4 * m2[ 7];
//  m22 = f1 * m2[ 8] + f2 * m2[ 9] + f3 * m2[10] + f4 * m2[11];
//  m32 = f1 * m2[12] + f2 * m2[13] + f3 * m2[14] + f4 * m2[15];
//
//  f1 = m1[3];
//  f2 = m1[7];
//  f3 = m1[11];
//  f4 = m1[15];
//  m03 = f1 * m2[ 0] + f2 * m2[ 1] + f3 * m2[ 2] + f4 * m2[ 3];
//  m13 = f1 * m2[ 4] + f2 * m2[ 5] + f3 * m2[ 6] + f4 * m2[ 7];
//  m23 = f1 * m2[ 8] + f2 * m2[ 9] + f3 * m2[10] + f4 * m2[11];
//  m33 = f1 * m2[12] + f2 * m2[13] + f3 * m2[14] + f4 * m2[15];
//
//
///*
//  // 5800
//  float* m1 = t1->m;
//  float* m2 = t2->m;
//
//  float f1 = m1[0];
//  float f2 = m1[4];
//  float f3 = m1[8];
//  float f4 = m1[12];
//  m00  = f1 * *m2++;
//  m00 += f2 * *m2++;
//  m00 += f3 * *m2++;
//  m00 += f4 * *m2++;
//  m10  = f1 * *m2++;
//  m10 += f2 * *m2++;
//  m10 += f3 * *m2++;
//  m10 += f4 * *m2++;
//  m20  = f1 * *m2++;
//  m20 += f2 * *m2++;
//  m20 += f3 * *m2++;
//  m20 += f4 * *m2++;
//  m30  = f1 * *m2++;
//  m30 += f2 * *m2++;
//  m30 += f3 * *m2++;
//  m30 += f4 * *m2++;
//
//  m2 = t2->m;
//  f1 = m1[1];
//  f2 = m1[5];
//  f3 = m1[9];
//  f4 = m1[13];
//  m01  = f1 * *m2++;
//  m01 += f2 * *m2++;
//  m01 += f3 * *m2++;
//  m01 += f4 * *m2++;
//  m11  = f1 * *m2++;
//  m11 += f2 * *m2++;
//  m11 += f3 * *m2++;
//  m11 += f4 * *m2++;
//  m21  = f1 * *m2++;
//  m21 += f2 * *m2++;
//  m21 += f3 * *m2++;
//  m21 += f4 * *m2++;
//  m31  = f1 * *m2++;
//  m31 += f2 * *m2++;
//  m31 += f3 * *m2++;
//  m31 += f4 * *m2++;
//
//
//  m2 = t2->m;
//  f1 = m1[2];
//  f2 = m1[6];
//  f3 = m1[10];
//  f4 = m1[14];
//  m02  = f1 * *m2++;
//  m02 += f2 * *m2++;
//  m02 += f3 * *m2++;
//  m02 += f4 * *m2++;
//  m12  = f1 * *m2++;
//  m12 += f2 * *m2++;
//  m12 += f3 * *m2++;
//  m12 += f4 * *m2++;
//  m22  = f1 * *m2++;
//  m22 += f2 * *m2++;
//  m22 += f3 * *m2++;
//  m22 += f4 * *m2++;
//  m32  = f1 * *m2++;
//  m32 += f2 * *m2++;
//  m32 += f3 * *m2++;
//  m32 += f4 * *m2++;
//
//  m2 = t2->m;
//  f1 = m1[3];
//  f2 = m1[7];
//  f3 = m1[11];
//  f4 = m1[15];
//  m03  = f1 * *m2++;
//  m03 += f2 * *m2++;
//  m03 += f3 * *m2++;
//  m03 += f4 * *m2++;
//  m13  = f1 * *m2++;
//  m13 += f2 * *m2++;
//  m13 += f3 * *m2++;
//  m13 += f4 * *m2++;
//  m23  = f1 * *m2++;
//  m23 += f2 * *m2++;
//  m23 += f3 * *m2++;
//  m23 += f4 * *m2++;
//  m33  = f1 * *m2++;
//  m33 += f2 * *m2++;
//  m33 += f3 * *m2++;
//  m33 += f4 * *m2++;
//*/
//}


void Transform3D::setTranslation(Transform3D* t) {

  float* h = t->m;
  indices.idx12 = h[12];
  indices.idx13 = h[13];
  indices.idx14 = h[14];
}


bool Transform3D::equals(Transform3D* t3d) {
  float* self = m;
  float* other = t3d->m;

  for (int i=0; i<16; i++) {
    if (*other++ != *self++) return(false);
  }
  return(true);
}

void Transform3D::mul(Vector3f* v, Vector3f* target) {
  target->dx = indices.idx0 * v->dx + indices.idx4 * v->dy + indices.idx8  * v->dz;
  target->dy = indices.idx1 * v->dx + indices.idx5 * v->dy + indices.idx9  * v->dz;
  target->dz = indices.idx2 * v->dx + indices.idx6 * v->dy + indices.idx10 * v->dz;
}

void Transform3D::mul(Point4f* v, Point4f* target) {
  target->x = indices.idx0 * v->x + indices.idx4 * v->y + indices.idx8  * v->z + indices.idx12 * v->w;
  target->y = indices.idx1 * v->x + indices.idx5 * v->y + indices.idx9  * v->z + indices.idx13 * v->w;
  target->z = indices.idx2 * v->x + indices.idx6 * v->y + indices.idx10 * v->z + indices.idx14 * v->w;
  target->w = indices.idx3 * v->x + indices.idx7 * v->y + indices.idx11 * v->z + indices.idx15 * v->w;
}

void Transform3D::transpose() {
  Transform3D clone(this);

  for (int i=0; i<4; i++) {
    for (int j=0; j<4; j++) {
      setData(i, j, clone.getData(j, i));
    }
  }
}
