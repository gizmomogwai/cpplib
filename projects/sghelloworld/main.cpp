#include <string>

#include <sgtools-glut/GLUTEngine.h>
#include <sg/visitors/OGLRenderVisitor.h>
#include <sg/visitors/UpdateVisitor.h>
#include <sg/visitors/BehaviorVisitor.h>
#include <sg/visitors/PrintVisitor.h>
#include <sg/visitors/GLUTFontManager.h>

#include <sg/nodeComponents/geom/TeapotGeometry.h>
#include <sgtools/nodeComponents/geom/CubeGeometry.h>

#include <sgtools/nodeComponents/behavior/RotationBehavior.h>

int main(int argc, char** args) {
  Engine* engine = new GLUTEngine(argc, args, 512, 512, "glView");
  engine->addVisitor(new UpdateVisitor());
  engine->addVisitor(new BehaviorVisitor());
  engine->addVisitor(new OGLRenderVisitor(new GLUTFontManager()));

  auto root = new Root();
  engine->setRoot(root);
  root->releaseReference();

  auto observer = new SGObserver();
  auto all = new TGroup();


  if (std::string("camera") == args[1]) {
    observer->setCamera(new Camera(75, 1.0, 1, 1000));
    auto transform = Transform3D();
    transform.setTranslation(new Vector3f(0, 0, -150));
    all->setTransform(&transform);
  } else if (std::string("parallel") == args[1]) {
    auto projection = new ParallelProjection();
    projection->left = -100;
    projection->right = 100;
    projection->top = 100;
    projection->bottom = -100;
    projection->nearClipping = -100;
    projection->farClipping = 100;
    observer->setParallel(projection);
    auto transform = Transform3D();
    transform.setTranslation(new Vector3f(-0, -0, -0));
    all->setTransform(&transform);
  } else {
    std::cout << "Usage: " << args[0] << " parallel|camera\n";
    return 1;
  }

  auto rotation = new TGroup();
  all->addChild(new RotationBehavior(rotation, 0.03f));
  all->addChild(rotation);

  //auto geometry = new CubeGeometry(50, 0);
  auto geometry = new TeapotGeometry();
  auto appearance = new Appearance(0);
  auto material = new Material();
  auto red = Color3f(1,0,0);
  material->setColor(&red);
  material->setLighting(false);
  appearance->setMaterial(material);

  auto shape = new Shape3D(geometry, appearance);
  geometry->releaseReference();
  appearance->releaseReference();

  rotation->addChild(shape);
  observer->addChild(all);
  all->releaseReference();

  root->addChild(observer);
  observer->releaseReference();

  engine->run();
  return 0;
}
