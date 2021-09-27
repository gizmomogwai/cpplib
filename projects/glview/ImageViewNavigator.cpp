#include "ImageViewNavigator.h"

#include "LoadProgress.h"
#include "SGUpdateThread.h"
#include <image/Image.h>
#include <sg/nodes/Node.h>
#include <sg/nodes/Root.h>
#include <sg/nodes/SGObserver.h>
#include <sg/visitors/RenderVisitor.h>
#include <sg/visitors/UpdateVisitor.h>

#include <sgtools/KeyEvent.h>
#include <vecmath/ParallelProjection.h>
#include "Animation.h"

ParallelProjection* getProjection(float factor) {
  auto projection = new ParallelProjection(factor);
  projection->nearClipping = -100;
  projection->farClipping = 100;
  return projection;
}
ImageViewNavigator::ImageViewNavigator(Root* _root,
                                       RenderVisitor* _renderVisitor,
                                       File* _dir,
                                       Animations& _animations)
  :
    observer(0),
    root(_root),
    factor(1),
    renderVisitor(_renderVisitor),
    dir(_dir),
    loadProgress(0),
    animations(_animations) {
  std::cout << "ImageViewNavigator - start" << std::endl;

  observer = new SGObserver();
  observer->setParallel(getProjection(factor));
  //  observer->setCamera(new Camera(75, 1.0, 10, 10000));

  root->addChild(observer);

  loadProgress = new LoadProgress();
  root->addChild(loadProgress);

  files = dir->list();
  std::sort(files->begin(), files->end(),  [](File* f1, File* f2) {
      return f1->toString() < f2->toString();
    });
  std::cout << "Files:\n";
  for (auto file: *files) {
    std::cout << file->toString() << std::endl;
  }
  fileIterator = files->begin();
  auto visitor = UpdateVisitor();
  root->accept(&visitor);

  std::cout << "ImageViewNavigator - exit" << std::endl;
}

ImageViewNavigator::~ImageViewNavigator() {
  std::cout << "~ImageViewNavigator" << std::endl;
  /*
  observer->releaseReference();

  if (dir != 0) {
    delete dir;
    dir = 0;
  }
  if (files != 0) {
    delete files;
    files = 0;
  }
  loadProgress->releaseReference();
  */
}

void ImageViewNavigator::setImage(Image* i) {
  imageWidth = i->getWidth();
  imageHeight = i->getHeight();
  setTranslation(true);
}

void ImageViewNavigator::setTranslation(bool init) {

  if (factor < 0.01f) {
    factor = 0.01f;
  }
  observer->setParallel(getProjection(factor));

  float canvasWidth = renderVisitor->getImageWidth();
  float canvasHeight = renderVisitor->getImageHeight();

  if (init == true) {
    centerImage(imageWidth, imageHeight);
  } else {
    if (imageWidth * factor > canvasWidth) {
      float maxX = (imageWidth * factor - canvasWidth / 2.0f) / factor;
      float minX = canvasWidth / 2.0f / factor;
      if (posX > maxX) {
        posX = maxX;
      } else if (posX < minX) {
        posX = minX;
      }
    } else {
      centerImageX(imageWidth);
    }

    if (imageHeight * factor > canvasHeight) {
      float maxYPos = (imageHeight * factor - canvasHeight / 2.0f) / factor;
      float minYPos = canvasHeight / 2.0f / factor;
      if (posY > maxYPos) {
        posY = maxYPos;
      } else if (posY < minYPos) {
        posY = minYPos;
      }
    } else {
      centerImageY(imageHeight);
    }
  }

  Vector3f translation(posX, posY, 0);
  std::cout << "posX: " << posX << " posY: " << posY << std::endl;
  observer->setTranslation(&translation);
}

void ImageViewNavigator::centerImage(int imageWidth, int imageHeight) {
  centerImageX(imageWidth);
  centerImageY(imageHeight);
}

void ImageViewNavigator::centerImageX(int imageWidth) {
  posX = imageWidth / 2.0f;
}

void ImageViewNavigator::centerImageY(int imageHeight) {
  posY = imageHeight / 2.0f;
}

void ImageViewNavigator::keyPressed(KeyEvent* e) {
  float moveDelta = 1.0f;
  float zoomDelta = 0.01f;
  if (e->shiftPressed() == true) {
    moveDelta *= 5.0f;
    zoomDelta *= 5.0f;
  }
  //      moveDelta /= factor;
  zoomDelta *= factor;

  if (e->keyPressed(KeyEvent::UP)) {
    move(0, moveDelta);
  } else if (e->keyPressed(KeyEvent::DOWN)) {
    move(0, -moveDelta);
  } else if (e->keyPressed(KeyEvent::LEFT)) {
    move(-moveDelta, 0);
  } else if (e->keyPressed(KeyEvent::RIGHT)) {
    move(moveDelta, 0);
  } else if (e->keyPressed('+')) {
    setFactor(factor + zoomDelta);
  } else if (e->keyPressed('-')) {
    setFactor(factor - zoomDelta);
  } else if (e->keyPressed(KeyEvent::PAGE_DOWN)) {
    nextImage();
  } else if (e->keyPressed(KeyEvent::PAGE_UP)) {
    prevImage();
  } else if (e->keyPressed('1')) {
    setFactor(0.06125f);
  } else if (e->keyPressed('2')) {
    setFactor(0.125f);
  } else if (e->keyPressed('3')) {
    setFactor(0.25f);
  } else if (e->keyPressed('4')) {
    setFactor(0.5f);
  } else if (e->keyPressed('5')) {
    setFactor(1.0f);
  } else if (e->keyPressed('6')) {
    setFactor(2.0f);
  } else if (e->keyPressed('7')) {
    setFactor(4.0f);
  } else if (e->keyPressed('8')) {
    setFactor(8.0f);
  } else if (e->keyPressed('9')) {
    setFactor(16.0f);
  }
}

void ImageViewNavigator::setFactor(float newFactor) {
  factor = newFactor;
  setTranslation();
}

void ImageViewNavigator::move(float dx, float dy) {
  posX += dx;
  posY += dy;
  setTranslation();
}

void ImageViewNavigator::showImage(File* f) {
  informSelectionListener(f);
  SGUpdateThread* updater =
    new SGUpdateThread(root, observer, f, this, loadProgress, animations);
  updater->start();
}


void ImageViewNavigator::informSelectionListener(File* newSelection) {
  ListIterator<SelectionListener*> i = ListIterator<SelectionListener*>(&fSelectionListeners);
  while (i.hasNext()) {
    SelectionListener* listener = i.next();
    std::cout << "informing listener " << listener << std::endl;
    listener->selectionChanged(newSelection);
  }
}

void ImageViewNavigator::reload() {
  std::cout << "reloading" << std::endl;
  showImage(*fileIterator);
}

void ImageViewNavigator::nextImage() {
  bool finished = false;
  while (finished == false) {
    fileIterator++;
    if (fileIterator == files->end()) {
      fileIterator = files->begin();
    }
    if ((*fileIterator)->isDirectory() == false) {
      showImage(*fileIterator);
      finished = true;
    }
  }
}

void ImageViewNavigator::prevImage() {

  bool finished = false;
  while (finished == false) {
    if (fileIterator == files->begin()) {
      fileIterator = files->end();
    }
    fileIterator--;
    if ((*fileIterator)->isDirectory() == false) {
      showImage(*fileIterator);
      finished = true;
    }
  }
}
