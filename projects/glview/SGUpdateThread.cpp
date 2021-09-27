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
#include "LoadProgress.h"

#include <util/profile/ProfileObject.h>
#include <util/profile/Profiler.h>
#include <util/profile/PrintProfileVisitor.h>

#include <sgtools/nodeComponents/behavior/RotationBehavior.h>
#include <lang/Math.h>

#include <sg/nodeComponents/geom/TeapotGeometry.h>
#include <sg/visitors/UpdateVisitor.h>

const int SGUpdateThread::textureSize = 128;

SGUpdateThread::SGUpdateThread(Root* _root,
                               SGObserver* _observer,
                               File* _file,
                               ImageViewNavigator* _navigator,
                               LoadProgress* _loadProgress)
  : Thread(),
    observer(_observer),
    root(_root),
    file(new File(_file)),
    loadProgress(_loadProgress),
    navigator(_navigator) {

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

void SGUpdateThread::createShape(Image* image,
                                 int xPos, int yPos,
                                 int xCount, int yCount,
                                 Group* res, bool clipped) {
  //ProfileObject profiler("zerstueckeln");

  Image* part;
  if (clipped == false) {
    part = image->getRect(xPos, yPos, textureSize, textureSize);
  } else {
    part = image->getClippedRect(xPos, yPos, textureSize, textureSize);
  }

  auto shape = shapeForImage(image->getHeight(),
                             xCount, yCount, part);

  auto translationTransformation = new TGroup();
  auto rotationTransformation = new TGroup();
  auto rotation = (new RotationBehavior(rotationTransformation))->setDelta(Math::toRadians(1));
  rotationTransformation->addChild(rotation);

  auto transform = new Transform3D();
  transform->setTranslation(new Vector3f(0.5+xCount*(textureSize-1), image->getHeight() - (0.5+yCount*(textureSize-1)), 0));
  translationTransformation->setTransform(transform);

  translationTransformation->addChild(rotationTransformation);
  rotationTransformation->releaseReference();

  rotationTransformation->addChild(shape);
  shape->releaseReference();

  res->addChild(translationTransformation);
  translationTransformation->releaseReference();
}

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
 */
void SGUpdateThread::buildViewGraph(File* file) {

  //ProfileObject profiler("buildViewGraph");

  std::cout << "Working on: " << file->toString() << std::endl;

  setDummy(observer, 0);

  loadProgress->load();
  root->setChild(loadProgress, 1);

  cutTime = 0.0f;

  Image* image = ImageReader::readImage(file);

  //ProfileObject* profiler2 = new ProfileObject("cutImage");

  Group* res = new Group();

  int yPos = 0;
  int yCount = 0;
  int xPos = 0;
  int xCount = 0;
  while (yPos + textureSize < image->getHeight()) {
    xPos = 0;
    xCount = 0;
    while (xPos + textureSize < image->getWidth()) {

      createShape(image, xPos, yPos, xCount, yCount, res, false);
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
    createShape(image, xPos, yPos, xCount, yCount, res, true);
    yPos += textureSize - 1;
    yCount++;
  }

  // letzte zeile
  xPos = 0;
  xCount = 0;
  yPos = lastYPos;
  yCount = lastYCount;
  while (xPos + textureSize < image->getWidth()) {
    createShape(image, xPos, yPos, xCount, yCount, res, true);
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
  createShape(image, xPos, yPos, xCount, yCount, res, true);

  // delete(profiler2);

  navigator->setImage(image);
  delete image;

  observer->setChild(res, 0);
  auto visitor = UpdateVisitor();
  res->accept(&visitor);
  std::cout << "Childs: " << res->getChildCount() << std::endl;

  res->releaseReference();

  setDummy(root, 1);
}

void SGUpdateThread::setDummy(Group* g, int idx) {
  std::cout << "SGUpdateThread.setDummy - start" << std::endl;
  Node* dummy = new Node();
  g->setChild(dummy, idx);
  dummy->releaseReference();
  std::cout << "SGUpdateThread.setDummy - finished" << std::endl;
}
