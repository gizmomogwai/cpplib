#include <lang/HPStopWatch.h>

#include <sgtools/GLUTEngine.h>
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
#include <projects/glview/RotationBehavior.h>

File* getDir(File* dirOrFile) {
  if (dirOrFile->isDirectory() == true) {
    return new File(dirOrFile);
  } else {
    return dirOrFile->getParent();
  }
}



/** Imageviewer mainprogramm.
 *
 * Usage: glview fileName
 *
 * @param argc Anzahl commandozeilenargumente.
 * @param args Commandozeilenargumente.
 */
/*
int main(int argc, char** args) {
  try {
    if (argc != 2) {
      throw(Exception("Usage: glview fileName"));
    }
    Engine* engine = new GLUTEngine(argc, args, 512, 512, "glView");
    engine->addVisitor(new UpdateVisitor());
    engine->addVisitor(new BehaviorVisitor());
    OGLRenderVisitor* renderer = new OGLRenderVisitor(new GLUTFontManager());
    engine->addVisitor(renderer);

    Root* root = new Root();

    File arg(args[1]);
    File* dir = getDir(&arg);

    ImageViewNavigator* navigator =
      new ImageViewNavigator(root, renderer, dir);
    engine->setRoot(root);

    SGObserver* iotdObserver = new SGObserver();

    InfoNode* infoNode = new InfoNode();

    SwitchableWatermark* iotd = new SwitchableWatermark(ImageReader::readImage(std::string("iotd.enabled.png")), 0, 50);
    SwitchableWatermark* async = new SwitchableWatermark(ImageReader::readImage(std::string("async.png")), 0, 0);
    SwitchableWatermark* thumb = new SwitchableWatermark(0, -1, -1);
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
*/
