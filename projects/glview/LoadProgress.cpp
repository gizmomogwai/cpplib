#include "LoadProgress.h"

#include <sg/nodes/TGroup.h>
#include <sg/nodes/Shape3D.h>

#include <vecmath/Camera.h>
#include <vecmath/Vector3f.h>

#include <sg/nodeComponents/app/RenderingAttributes.h>
#include <sg/nodeComponents/app/Appearance.h>
#include <sg/nodeComponents/app/PolygonAttributes.h>

#include <sgtools/nodeComponents/geom/CubeGeometry.h>

LoadProgress::LoadProgress() {
  setCamera(new Camera(22, 1, 1, 10000));
  Vector3f translation(0, 0, 10);
  setTranslation(&translation);

  TGroup* tG = new TGroup();

  Geometry* geom = new CubeGeometry(1, 0);
  Appearance* app = new Appearance(0);
  PolygonAttributes* pAtts =
    new PolygonAttributes(PolygonAttributes::POLYGON_LINE);
  app->setPolygonAttributes(pAtts);
  pAtts->releaseReference();

  RenderingAttributes* rAtts =
    new RenderingAttributes(false, false);
  app->setRenderingAttributes(rAtts);
  rAtts->releaseReference();

  Shape3D* shape = new Shape3D(geom, app);
  geom->releaseReference();
  app->releaseReference();
  tG->addChild(shape);
  shape->releaseReference();

  rot = new RotationBehavior(tG);
  tG->addChild(rot);

  addChild(tG);
  tG->releaseReference();
}
