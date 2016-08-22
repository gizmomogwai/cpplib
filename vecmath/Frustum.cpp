#include <vecmath/Frustum.h>

Frustum::Frustum() {
}


Frustum::~Frustum() {
}

void Frustum::create(Transform3D* projection, Transform3D* modelView) {

  Transform3D tmp;
  
  tmp.mul(projection, modelView);

  float* clip = tmp.m;

  /* Extract the numbers for the RIGHT plane */
  frustumPlanes[0].coefs.a = clip[ 3] - clip[ 0];
  frustumPlanes[0].coefs.b = clip[ 7] - clip[ 4];
  frustumPlanes[0].coefs.c = clip[11] - clip[ 8];
  frustumPlanes[0].coefs.d = clip[15] - clip[12];

  /* Extract the numbers for the LEFT plane */
  frustumPlanes[1].coefs.a = clip[ 3] + clip[ 0];
  frustumPlanes[1].coefs.b = clip[ 7] + clip[ 4];
  frustumPlanes[1].coefs.c = clip[11] + clip[ 8];
  frustumPlanes[1].coefs.d = clip[15] + clip[12];

  /* Extract the BOTTOM plane */
  frustumPlanes[2].coefs.a = clip[ 3] + clip[ 1];
  frustumPlanes[2].coefs.b = clip[ 7] + clip[ 5];
  frustumPlanes[2].coefs.c = clip[11] + clip[ 9];
  frustumPlanes[2].coefs.d = clip[15] + clip[13];

  /* Extract the TOP plane */
  frustumPlanes[3].coefs.a = clip[ 3] - clip[ 1];
  frustumPlanes[3].coefs.b = clip[ 7] - clip[ 5];
  frustumPlanes[3].coefs.c = clip[11] - clip[ 9];
  frustumPlanes[3].coefs.d = clip[15] - clip[13];

  /* Extract the FAR plane */
  frustumPlanes[4].coefs.a = clip[ 3] - clip[ 2];
  frustumPlanes[4].coefs.b = clip[ 7] - clip[ 6];
  frustumPlanes[4].coefs.c = clip[11] - clip[10];
  frustumPlanes[4].coefs.d = clip[15] - clip[14];

  /* Extract the NEAR plane */
  frustumPlanes[5].coefs.a = clip[ 3] + clip[ 2];
  frustumPlanes[5].coefs.b = clip[ 7] + clip[ 6];
  frustumPlanes[5].coefs.c = clip[11] + clip[10];
  frustumPlanes[5].coefs.d = clip[15] + clip[14];

  for (int i=0; i<6; i++) {
    frustumPlanes[i].normalize();
  }
}


double Frustum::sphereInFrustumDistance(float x, float y, float z, float r) {

  double d = 0.0;

  for(int i=0; i<6; i++ ) {

      d = frustumPlanes[i].distance(x, y, z);

      if(d <= -r) {

        return(0.0);
      }
  }

  return d;
}

double Frustum::sphereInFrustumDistance(BoundingSphere* bSphere) {

  double d = 0.0;

  for(int i=0; i<6; i++ ) {

      d = frustumPlanes[i].distance(bSphere->center);  

      if(d <= -bSphere->radius) {

        return(0.0);
      }
  }

  return d;
}


bool Frustum::sphereInFrustum(BoundingSphere* bSphere) {

  Point3f* center = bSphere->center;
  
  return(sphereInFrustum(center->x, center->y, center->z, bSphere->radius));
}

bool Frustum::sphereInFrustum(float x, float y, float z, float radius) {

  double d = sphereInFrustumDistance(x, y, z, radius);

  return(d != 0);
}
