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
    observer(new SGObserver()),
    root(_root),
    factor(1),
    renderVisitor(_renderVisitor),
    dir(_dir),
    loadProgress(0),
    animations(_animations),
    autoFactor(true) {
  observer->setParallel(getProjection(factor));

  root->addChild(observer);

  //  loadProgress = new LoadProgress();
  // root->addChild(loadProgress);

  files = dir->list();
  std::sort(files->begin(), files->end(), [](File* f1, File* f2) {
      return f1->toString() < f2->toString();
    });
  fileIterator = files->begin();
  auto visitor = UpdateVisitor();
  root->accept(&visitor);
}

ImageViewNavigator::~ImageViewNavigator() {
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
  std::cout << __FILE__ << ":" << __LINE__ << std::endl;
  imageWidth = i->getWidth();
  imageHeight = i->getHeight();
  setTranslation(true);
}

void ImageViewNavigator::setTranslation(bool init) {
  float canvasWidth = renderVisitor->getImageWidth();
  float canvasHeight = renderVisitor->getImageHeight();

  if (autoFactor) {
    factor = min(
                   canvasWidth / imageWidth,
                   canvasHeight / imageHeight
                 );
  }

  if (factor < 0.01f) {
    std::cout << "FALLING back to 0.01\n";
    factor = 0.01f;
  }
  observer->setParallel(getProjection(factor));

  if (init == true) {
    centerImage(imageWidth, imageHeight);
  } else {
    if (imageWidth * factor > canvasWidth) {
      float maxX = (imageWidth * factor - canvasWidth / 2.0f) / factor;
      float minX = canvasWidth / 2.0f / factor;
      posX = max(min(posX, maxX), minX);
    } else {
      centerImageX(imageWidth);
    }

    if (imageHeight * factor > canvasHeight) {
      float maxY = (imageHeight * factor - canvasHeight / 2.0f) / factor;
      float minY = canvasHeight / 2.0f / factor;
      posY = max(min(posY, maxY), minY);
    } else {
      centerImageY(imageHeight);
    }
  }

  Vector3f translation(posX, posY, 0);
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
    setFactor(1.0f/16);
  } else if (e->keyPressed('2')) {
    setFactor(1.0f/8);
  } else if (e->keyPressed('3')) {
    setFactor(1.0f/4);
  } else if (e->keyPressed('4')) {
    setFactor(1.0f/2);
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
  } else if (e->keyPressed('a')) {
    toggleAutoFactor();
    setTranslation();
  }
}

void ImageViewNavigator::setFactor(float newFactor) {
  autoFactor = false;
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
