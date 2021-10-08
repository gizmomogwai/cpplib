#include "SGUpdateThread.h"

#include "ImageReader.h"
#include "ImageViewNavigator.h"
#include <assert.h>
#include <image/Image.h>
#include <io/file/File.h>
#include <lang/Exception.h>
#include <lang/HPStopWatch.h>
#include <sg/data/Array2f.h>
#include <sg/data/Array3f.h>
#include <sg/nodeComponents/app/Appearance.h>
#include <sg/nodeComponents/app/SGImage.h>
#include <sg/nodeComponents/app/Texture.h>
#include <sg/nodeComponents/geom/TriangleArray.h>
#include <sg/nodes/Group.h>
#include <sg/nodes/Node.h>
#include <sg/nodes/TGroup.h>
#include <sg/nodes/Root.h>
#include <sg/nodes/SGObserver.h>
#include <sg/nodes/Shape3D.h>
#include <sg/visitors/Visitors.h>
#include "LoadProgress.h"

#include <util/profile/ProfileObject.h>
#include <util/profile/Profiler.h>
#include <util/profile/PrintProfileVisitor.h>

#include <sgtools/nodeComponents/behavior/RotationBehavior.h>
#include <lang/Math.h>

#include <sg/nodeComponents/geom/TeapotGeometry.h>
#include <sg/visitors/UpdateVisitor.h>
#include <projects/glview/Animation.h>
#include "Animation.h"

const int SGUpdateThread::textureSize = 256;

SGUpdateThread::SGUpdateThread(Root* _root,
                               SGObserver* _observer,
                               File* _file,
                               ImageViewNavigator* _navigator,
                               LoadProgress* _loadProgress,
                               Animations& _animations)
  : Thread(),
    observer(_observer),
    file(new File(_file)),
    loadProgress(_loadProgress),
    navigator(_navigator),
    animations(_animations) {

  Profiler::getInstance()->clear();

  assert(observer != 0);
  assert(file != 0);
  assert(navigator != 0);
  setupTileGeometry();
}

SGUpdateThread::~SGUpdateThread() {
  tileGeometry->releaseReference();
  delete file;
}

void SGUpdateThread::run() {
  try {
    buildViewGraph(file);
    //    std::cout << Profiler::getInstance()->toString();
  } catch (Exception& e) {
    std::cout << "Exception: " << e.getMessage() << std::endl;
    loadProgress->error();
  }
  delete this;
}

void SGUpdateThread::setupTileGeometry() {
  tileGeometry = new TriangleArray(FAN, 1);
  Array3f* coords = new Array3f(4);
  double half = (textureSize - 1)/2.0f;
  coords->set(3,
              -half,
              textureSize-1.0f-half,
              0);
  coords->set(2,
              textureSize - 1.0f-half,
              textureSize - 1.0f-half,
              0);
  coords->set(1,
              textureSize - 1.0f-half,
              -half,
              0);
  coords->set(0,
              -half,
              -half,
              0);
  tileGeometry->setCoordinates(coords);
  coords->releaseReference();

  Array2f* texCoords = new Array2f(4);
  float pixel = 0.5f / textureSize;
  texCoords->set(3, pixel,      pixel);
  texCoords->set(2, 1.0f-pixel, pixel);
  texCoords->set(1, 1.0f-pixel, 1.0f-pixel);
  texCoords->set(0, pixel,      1.0f-pixel);
  tileGeometry->setTextureCoordinates(texCoords, 0);
  texCoords->releaseReference();
}

Shape3D* SGUpdateThread::shapeForImage(int height,
                                       int i, int j,
                                       Image* image) {
  //ProfileObject profiler("shapeImage");

  Appearance* app = new Appearance(1);
  SGImage* sgImage = new SGImage(image);
  Texture* texture = new Texture(sgImage);
  texture->setTextureWrap(false, false);
  sgImage->releaseReference();
  app->setTexture(texture, 0);
  texture->releaseReference();

  auto shape = new Shape3D(tileGeometry, app);
  app->releaseReference();

  return shape;
}

class AnimatedTGroup : public TGroup {
public:
  AnimatedTGroup(Animation* _out) : out(_out) {}
  ~AnimatedTGroup() {
    delete out;
  }
  Animation* out;
};
class RotateAnimation : public Animation {
public:
  RotateAnimation(const std::function<void (void)> _done, TGroup* _rotationGroup, float _start, float _end, int _delay) : Animation(_done), rotationGroup(_rotationGroup), alpha(_start), end(_end), delay(_delay) {
    rotationGroup->addReference();
  }
  ~RotateAnimation() {
    rotationGroup->releaseReference();
  }
  bool step() {
    if (delay > 0) {
      delay--;
      return false;
    }
    auto transform = new Transform3D();
    alpha = min(alpha + Math::toRadians(3), end);
    transform->rotY(alpha);
    rotationGroup->setTransform(transform);
    return alpha == end;
  }
  std::string toString() const {
    return "RotateAnimation";
  }
private:
  TGroup* rotationGroup;
  float alpha;
  float end;
  int delay;
};

void createDebugShape(Image* image, Group* res) {
  float factor = 5;
  Image* i = image->getRect(0, 0, 256, 256);

  Appearance* app = new Appearance(1);
  SGImage* sgImage = new SGImage(i);
  Texture* texture = new Texture(sgImage);
  texture->setTextureWrap(false, false);
  sgImage->releaseReference();
  app->setTexture(texture, 0);
  texture->releaseReference();

  auto tileGeometry = new TriangleArray(FAN, 1);
  Array3f* coords = new Array3f(4);
  coords->set(3,
              0,
              256*factor,
              0);
  coords->set(2,
              256*factor,
              256*factor,
              0);
  coords->set(1,
              256*factor,
              0,
              0);
  coords->set(0,
              0,
              0,
              0);
  tileGeometry->setCoordinates(coords);
  coords->releaseReference();

  Array2f* texCoords = new Array2f(4);
  texCoords->set(3, 0, 0);
  texCoords->set(2, 1, 0);
  texCoords->set(1, 1, 1);
  texCoords->set(0, 0, 1);
  tileGeometry->setTextureCoordinates(texCoords, 0);
  texCoords->releaseReference();

  auto shape = new Shape3D(tileGeometry, app);
  app->releaseReference();
  tileGeometry->releaseReference();
  res->addChild(shape);
  shape->releaseReference();
}
void SGUpdateThread::createShape(Image* image,
                                 int xPos, int yPos,
                                 int xCount, int yCount,
                                 Group* res, bool clipped,
                                 AnimationGroup& animationGroup) {
  //ProfileObject profiler("zerstueckeln");

  Image* part;
  if (clipped == false) {
    part = image->getRect(xPos, yPos, textureSize, textureSize);
  } else {
    part = image->getClippedRect(xPos, yPos, textureSize, textureSize);
  }

  auto shape = shapeForImage(image->getHeight(),
                             xCount, yCount, part);

  auto rotationTransformation = new TGroup();
  rotationTransformation->addChild(shape);
  shape->releaseReference();

  auto outAnimation = new RotateAnimation([]{}, rotationTransformation, Math::toRadians(0), Math::toRadians(90), xCount+yCount);
  // auto outAnimation = new RotateAnimation([]{}, rotationTransformation, Math::toRadians(0), Math::toRadians(90), static_cast<int>(Math::random(50)));
  animationGroup.add(outAnimation);
  auto translationTransformation = new AnimatedTGroup(outAnimation);

  auto transform = new Transform3D();
  transform->setTranslation(new Vector3f((0.5+xCount)*(textureSize-1), image->getHeight() - ((0.5+yCount)*(textureSize-1)), 0));
  translationTransformation->setTransform(transform);

  translationTransformation->addChild(rotationTransformation);
  rotationTransformation->releaseReference();

  res->addChild(translationTransformation);
  translationTransformation->releaseReference();
}

void* ANIM = reinterpret_cast<void*>(1);
/*
  create from an imagefile:
  - each image is split into tiles
  - a tile is textureSize-1 in width and height (because of bilinear filtering the tile needs to go from pixel 0.5 till textureSize - 0.5)
  so the geometry goes from 0.5+n*(textureSize-1) ... 0.5+(n+1)(textureSize-1)
  - the texture of a tile is textureSize in width and height from 0..textureSize-1, textureSize-1..2*(textureSize-1)
  - texturecoordinates are always the same, as the image is cut into pieces ...
  from the middle of the first pixel to the middle of the last pixel
  0.5/textureSize .. 1 - 0.5 / texturesize
  e.g. textureSize 4:
  geometry  0.5,3.5       3.5,6.5   6.5,9.5    9.5,12.5
  texture   0,1,2,3       3,4,5,6   6,7,8,9    9,10,11,12
  1/8...1-1/8


pixel        0          1           2          3          4         5          6
       |-----x-----|----------|----------|-----x-----|----------|--------|-----x-----|
geom        0.5                               3.5                             6.5
  observer->childs[0] ist das neue bild, observer->childs[1] ist das alte bild
*/
void SGUpdateThread::buildViewGraph(File* file) {
  try {
    std::cout << "Working on: " << file->toString() << std::endl;

    //loadProgress->load();
    //root->setChild(loadProgress, 1);

    cutTime = 0.0f;

    auto image = ImageReader::readImage(file);

    auto res = new Group();
    if (observer->getChildCount() == 1) {
      res->setName("newImage");
    } else {
      res->setName("currentImage");
    }
    auto outAnimations = new AnimationGroup([=](){
      auto newImage = findByName(res->parent, "newImage");
      res->parent->removeChild(res);
      if (newImage) {
        newImage->setName("currentImage");
      }
    });
    res->setCustomData(ANIM, outAnimations);

    int yPos = 0;
    int yCount = 0;
    int xPos = 0;
    int xCount = 0;
    while (yPos + textureSize < image->getHeight()) {
      xPos = 0;
      xCount = 0;
      while (xPos + textureSize < image->getWidth()) {
        createShape(image, xPos, yPos, xCount, yCount, res, false, *outAnimations);
        xPos += textureSize -1;
        xCount++;
      }

      yPos += textureSize -1;
      yCount++;
    }

    int lastXCount = xCount;
    int lastYCount = yCount;
    int lastXPos = xPos;
    int lastYPos = yPos;

    // letzte spalte runter
    xPos = lastXPos;
    yPos = 0;
    xCount = lastXCount;
    yCount = 0;
    while (yPos + textureSize < image->getHeight()) {
      createShape(image, xPos, yPos, xCount, yCount, res, true, *outAnimations);
      yPos += textureSize - 1;
      yCount++;
    }

    // letzte zeile
    xPos = 0;
    xCount = 0;
    yPos = lastYPos;
    yCount = lastYCount;
    while (xPos + textureSize < image->getWidth()) {
      createShape(image, xPos, yPos, xCount, yCount, res, true, *outAnimations);
      xPos += textureSize - 1;
      xCount++;
    }

    lastXPos = xPos;
    lastXCount = xCount;

    // ecke
    xPos = lastXPos;
    yPos = lastYPos;
    xCount = lastXCount;
    yCount = lastYCount;
    createShape(image, xPos, yPos, xCount, yCount, res, true, *outAnimations);

    navigator->setImage(image);
    delete image;

    observer->addChildInFront(res);
    res->releaseReference();

    auto visitor = UpdateVisitor();
    observer->accept(&visitor);

    auto childs = observer->getChildsAsList();
    if (childs->size() == 2) {
      auto currentImage = dynamic_cast<Node*>(findByName(observer, "currentImage"));
      if (currentImage) {
        auto anim = reinterpret_cast<Animation*>(currentImage->getCustomData(ANIM));
        if (anim == nullptr) {
          observer->removeChild(currentImage);
        } else {
          animations.run(anim);
        }
      }
    }
    // setDummy(root, 1);
  } catch (...) {
    std::cout << "Problem in sgupdatethread" << std::endl;
  }
}

void SGUpdateThread::setDummy(Group* g, int idx) {
  std::cout << "SGUpdateThread.setDummy - start" << std::endl;
  auto dummy = new Group();
  g->setChild(dummy, idx);
  dummy->releaseReference();
  std::cout << "SGUpdateThread.setDummy - finished" << std::endl;
}
