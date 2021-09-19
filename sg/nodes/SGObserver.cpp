#include <sg/nodes/SGObserver.h>

#include <util/ReleaseRefCountedObject.h>


SGObserver::SGObserver() : frustum(new Frustum()) {
  result = new RCTransform3D();

  RCTransform3D* t3d = new RCTransform3D();
  transform.set(t3d);
  transform.update();
  t3d->releaseReference();

  calcTransform();
}


SGObserver::~SGObserver() {
  delete(frustum);
  result->releaseReference();
}


Frustum* SGObserver::getFrustum() {

  return(frustum);
}


void SGObserver::setTranslation(Vector3f* v) {
  RCTransform3D* ori = transform.getNew();
  if (ori == 0) {
    ori = transform.get();
  }

  ReleaseRefCountedObject<RCTransform3D> clean1(ori);

  RCTransform3D* t3d = new RCTransform3D();
  ReleaseRefCountedObject<RCTransform3D> clean2(t3d);

  if (ori != 0) {
    t3d->set(ori);
  }

  t3d->matrix.m30 = v->dx;
  t3d->matrix.m31 = v->dy;
  t3d->matrix.m32 = v->dz;
  setTransform(t3d);
}


Vector3f* SGObserver::getTranslation() {
  Vector3f* res = 0;

  RCTransform3D* t3d = transform.get();
  if (t3d != 0) {
    res = new Vector3f(t3d->matrix.m30, t3d->matrix.m31, t3d->matrix.m32);
    t3d->releaseReference();
  }
  return(res);
}


void SGObserver::calcTransform() {
  if (result != 0) {
    result->releaseReference();
    result = 0;
  }

  RCTransform3D* t3d = transform.get();
  Transform3D* help = t3d->invertAffine();
  result = new RCTransform3D(help);
  t3d->releaseReference();
  delete(help);
}


void SGObserver::setTransform(RCTransform3D* t3d) {
  transform.set(t3d);
}


RCTransform3D* SGObserver::getCameraTransform() {
  result->addReference();
  return(result);
}


void SGObserver::calculateFrustum(int width, int height) {

  Transform3D* p = 0;
  if (camera != 0) {

    camera->setSize(width, height);
    p = camera->getProjection();

  } else if (parallel != 0) {

//    parallel->setSize(width, height);
    p = parallel->getProjection();
  }

  if (p != 0) {
    RCTransform3D* t3d = getCameraTransform();
    if (t3d != 0) {
      frustum->create(p, t3d);
      t3d->releaseReference();
    }
    //std::cout << p->toString() << std::endl;
    delete(p);
  }
}
