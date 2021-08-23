#include "InfoNode.h"

#include <sg/nodes/SGObserver.h>
#include <sg/nodes/Leaf.h>

#include <sg/nodeComponents/app/Appearance.h>
#include <sg/nodeComponents/geom/Text3D.h>
#include <sg/nodeComponents/geom/TriangleArray.h>
#include <sg/nodeComponents/geom/TriangleArrayType.h>

#include <sg/visitors/UpdateVisitor.h>

#include <util/ReleaseRefCountedObject.h>

#include <sg/data/Array2f.h>


#include <assert.h>

void InfoNodeHelper::setPoints(Array3f* points, 
                               int imageWidth, int imageHeight, 
                               int fromLeft, int fromTop,
                               int canvasWidth, int canvasHeight, 
									       			 int realWidth, int realHeight) {
  int border = 1;
  int left = -canvasWidth/2 + border + fromLeft;
	if (fromLeft < 0) {
		left = canvasWidth/2 - border - realWidth + fromLeft;
	}
  int bottom = canvasHeight/2 - border - imageHeight - fromTop;
	if (fromTop < 0) {
		bottom = -canvasHeight/2 + border - fromTop - (imageHeight - realHeight);
	}
		
  points->set(0, left,            bottom,             0);
  points->set(1, left+imageWidth, bottom,             0);
  points->set(2, left+imageWidth, bottom+imageHeight, 0);
  points->set(3, left,            bottom+imageHeight, 0);
}


void InfoNodeHelper::addDummyNodeTo(SwitchGroup* sg) {
	ReleaseRefCountedObject<Leaf> emptyNode(new Leaf());
	sg->addChild(*emptyNode);
}

void InfoNodeHelper::setFillAndZBuffer(Appearance* app) {
  ReleaseRefCountedObject<PolygonAttributes> pAtts(new PolygonAttributes(PolygonAttributes::POLYGON_FILL));
  app->setPolygonAttributes(*pAtts);

  ReleaseRefCountedObject<RenderingAttributes> rAtts(new RenderingAttributes(false, false));
  app->setRenderingAttributes(*rAtts);
}

void InfoNodeHelper::setRectTexCoords(TriangleArray* triangles) {
	ReleaseRefCountedObject<Array2f> texCoords(new Array2f(4));
	texCoords->set(0, 0, 1);
	texCoords->set(1, 1, 1);
  texCoords->set(2, 1, 0);
	texCoords->set(3, 0, 0);
	triangles->setTextureCoordinates(*texCoords, 0);
}

SwitchableWatermark::SwitchableWatermark(Image* image, int left, int top) : fLeft(left), fTop(top) {
	InfoNodeHelper::addDummyNodeTo(this);

	fWatermarkApp = new Appearance(1);
	if (image != 0) {
		ReleaseRefCountedObject<SGImage> sgImage(new SGImage(image));
		fImageWidth = sgImage->getWidth();
		fImageHeight = sgImage->getHeight();
		ReleaseRefCountedObject<Texture> enabledImage(new Texture(*sgImage));
		enabledImage->setTextureWrap(false, false);
	  fWatermarkApp->setTexture(*enabledImage, 0);
	} else {
		fImageWidth = 0;
		fImageHeight = 0;
		fRealImageWidth = 0;
		fRealImageHeight = 0;
	  fWatermarkApp->setTexture(0, 0);
	}
	
	ReleaseRefCountedObject<TriangleArray> triangles(new TriangleArray(FAN, 1));
	fPoints = new Array3f(4);
	triangles->setCoordinates(fPoints);

	InfoNodeHelper::setRectTexCoords(*triangles);
	
  ReleaseRefCountedObject<PolygonAttributes> pAtts(new PolygonAttributes(PolygonAttributes::POLYGON_FILL));
  fWatermarkApp->setPolygonAttributes(*pAtts);

  ReleaseRefCountedObject<RenderingAttributes> rAtts(new RenderingAttributes(false, false));
  fWatermarkApp->setRenderingAttributes(*rAtts);

  ReleaseRefCountedObject<Shape3D> iotdShape(new Shape3D(*triangles, fWatermarkApp));  
	
	addChild(*iotdShape);
}


void SwitchableWatermark::setImage(Image* image, int realWidth, int realHeight) {
	assert(image != 0);
	
	fImageWidth = image->getWidth();
	fImageHeight = image->getHeight();
	if (realWidth == 0) {
		fRealImageWidth = fImageWidth;
	} else {
		fRealImageWidth = realWidth;
	}
	if (realHeight == 0) {
		fRealImageHeight = fImageHeight;
	} else {
		fRealImageHeight = realHeight;
	}
  
	ReleaseRefCountedObject<SGImage> sgImage(new SGImage(image));
	ReleaseRefCountedObject<Texture> tex(new Texture(*sgImage));
	fWatermarkApp->setTexture(*tex, 0);
	
  auto updater = UpdateVisitor();
	fWatermarkApp->accept(&updater);
}

void SwitchableWatermark::update(int canvasWidth, int canvasHeight) {
	InfoNodeHelper::setPoints(fPoints, 
	                          fImageWidth, fImageHeight, 
	                          fLeft, fTop, 
														canvasWidth, canvasHeight,
	                          fRealImageWidth, fRealImageHeight);
}

void SwitchableWatermark::setVisible(bool flag) {
	int idx = flag ? 1 : 0;
  setSwitchedIndex(idx);
}

void InfoNode::addChild(SwitchableWatermark* newChild) {
  fInfoNodes->addChild(newChild);
  auto updater = UpdateVisitor();
	fInfoNodes->accept(&updater);
}

InfoNode::InfoNode() {
	fInfoNodes = new Group();	
}

void InfoNode::paint(RenderVisitor* renderVisitor) {
  int w = renderVisitor->getImageWidth();
  int h = renderVisitor->getImageHeight();
  
  CleanUpObject<NodeListIterator> childs(fInfoNodes->getChilds());
  while (childs->hasNext()) {
    Node* child = childs->next();
    SwitchableWatermark* watermark = dynamic_cast<SwitchableWatermark*>(child);
    watermark->update(w, h);
  }
  
 /* 
	fIotdSwitch->update(renderVisitor->getImageWidth(), renderVisitor->getImageHeight());
	fSyncSwitch->update(renderVisitor->getImageWidth(), renderVisitor->getImageHeight());
	fThumbSwitch->update(renderVisitor->getImageWidth(), renderVisitor->getImageHeight());
*/
	fInfoNodes->accept(renderVisitor);
}

void InfoNode::setIotd(bool value) {
	int idx = value ? 1 : 0;
  fIotdSwitch->setSwitchedIndex(idx);
}

void InfoNode::setSync(bool value) {
	int idx = value ? 0 : 1;
  fSyncSwitch->setSwitchedIndex(idx);
}

void InfoNode::setThumbnail(Image* image, int realWidth, int realHeight) {
	if (image == 0) {
		fThumbSwitch->setSwitchedIndex(0);
	} else {
		fThumbSwitch->setImage(image, realWidth, realHeight);
		fThumbSwitch->setSwitchedIndex(1);
	}
}
