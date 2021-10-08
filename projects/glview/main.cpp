#include <lang/HPStopWatch.h>

#include <sgtools/QuitKeyListener.h>

#include <sg/visitors/OGLRenderVisitor.h>
#include <sg/visitors/UpdateVisitor.h>
#include <sg/visitors/BehaviorVisitor.h>
#include <sg/visitors/PrintVisitor.h>
#include <lang/CleanUpObject.h>
#include <util/Properties.h>
#include <io/file/FileInputStream.h>
#include <io/DataInputStream.h>

#include "ImageViewNavigator.h"
#include "SelectionListener.h"
#include "LosslessRotationHandler.h"
#include "InfoNode.h"
#include <sg/visitors/GLUTFontManager.h>
#include "IotdHandler.h"
#include "ImageReader.h"

#include "ExifDateHandler.h"
#include "DeleteFileHandler.h"
#include <sgtools/nodeComponents/geom/CubeGeometry.h>
#include "Animation.h"

extern Engine* setupEngine(int argc, char** args, int width, int height, const char* title, Root* root);

File* getDir(File* dirOrFile) {
  if (dirOrFile->isDirectory() == true) {
    return new File(dirOrFile);
  } else {
    return dirOrFile->getParent();
  }
}

class AnimationVisitor : public Visitor {
public:
  AnimationVisitor(Animations& _animations) : animations(_animations) {}
  ~AnimationVisitor() {}
  void visit(Root* root) {
    animations.animate();
  }
  std::string toString() {
    return "AnimationVisitor";
  }
private:
  Animations& animations;

};
/** Imageviewer mainprogramm.
 *
 * Usage: glview fileName
 *
 * @param argc Anzahl commandozeilenargumente.
 * @param args Commandozeilenargumente.
 */
int main(int argc, char** args) {
  try {
    if (argc != 2) {
      throw(Exception("Usage: glview fileName"));
    }
    auto root = new Root();

    auto engine = setupEngine(argc, args, 512, 512, "glView", root);
    Animations animations;
    engine->addVisitor(new AnimationVisitor(animations));
    engine->addVisitor(new BehaviorVisitor());
    engine->addVisitor(new UpdateVisitor());
    auto renderer = new OGLRenderVisitor(nullptr);
    engine->addVisitor(renderer);


    File arg(args[1]);
    File* dir = getDir(&arg);

    auto navigator = new ImageViewNavigator(root, renderer, dir, animations);
    engine->setRoot(root);

    auto iotdObserver = new SGObserver();

    auto infoNode = new InfoNode();

    auto iotd = new SwitchableWatermark(ImageReader::readImage(std::string("iotd.enabled.png")), 0, 50);
    auto async = new SwitchableWatermark(ImageReader::readImage(std::string("async.png")), 0, 0);
    auto thumb = new SwitchableWatermark(0, -1, -1);
    infoNode->addChild(iotd);
    infoNode->addChild(async);
    infoNode->addChild(thumb);

    iotdObserver->setParallel(new ParallelProjection());
    iotdObserver->addChild(infoNode);

    root->addChild(iotdObserver);
    iotdObserver->releaseReference();

    root->releaseReference();
    IotdHandler handler(engine, navigator, iotd);
    ExifDateHandler exifDateHandler(engine, navigator, thumb, async);

    iotd->releaseReference();
    async->releaseReference();
    thumb->releaseReference();

    infoNode->releaseReference();

    LosslessRotationHandler rotationHandler(engine, navigator);
    //  DeleteFileHandler deleteFileHandler(engine, navigator);

    engine->addKeyListener(navigator);
    engine->addKeyListener(new QuitKeyListener(engine));

    if (arg.isDirectory() == true) {
      navigator->nextImage();
    } else {
      navigator->showImage(&arg);
    }

    std::cout << "main - callin engine run" << std::endl;
    engine->run();
    std::cout << "main - engine run fertig" << std::endl;
  } catch (Exception &e) {
    printf("%s\n", e.getMessage().c_str());
//    MessageBox(NULL, e.getMessage().c_str(), "Problem", 0);
  }
  std::cout << "main-end" << std::endl;

  return 0;
}
