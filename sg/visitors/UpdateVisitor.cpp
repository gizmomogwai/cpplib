#include <sg/visitors/UpdateVisitor.h>

#include <sg/nodes/SGObserver.h>
#include <sg/nodes/Group.h>
#include <sg/nodes/Leaf.h>
#include <sg/nodes/Node.h>
#include <sg/nodes/Shape3D.h>
#include <sg/nodes/TGroup.h>
#include <sg/nodes/Root.h>
#include <sg/nodeComponents/app/Appearance.h>
#include <sg/nodeComponents/app/Texture.h>
#include <sg/nodeComponents/app/Material.h>

#include <sg/nodeComponents/geom/Geometry.h>
#include <sg/nodeComponents/geom/IndexedTriangleArray.h>
#include <sg/nodeComponents/geom/TeapotGeometry.h>
#include <sg/nodeComponents/geom/TriangleArray.h>

#include <sg/nodeComponents/geom/IndexedInterleavedTriangleArray.h>

UpdateVisitor::UpdateVisitor() : width(1), height(1) {
}

UpdateVisitor::~UpdateVisitor() {
}

void UpdateVisitor::visit(Root* root) {
  width = root->imageWidth;
  height = root->imageHeight;
  visit((Group*)root);
}

void UpdateVisitor::visit(SGObserver* observer) {
//  bool sceneChanged = observer->scene->hasChangedAndUpdate();
//  bool transformChanged = observer->transform->hasChangedAndUpdate();
//
//  if (transformChanged == true) {
//    observer->calcTransform();
//  }
//
//  Node* scene = observer->scene->get();
//  if (scene != 0) {
//    scene->accept(this);
//    scene->releaseReference();
//  }
  visit((Group*)observer);
  bool transformChanged = observer->transform.hasChangedAndUpdate();
  if (transformChanged == true) {
    observer->calcTransform();
    observer->calculateFrustum(width, height);
  }
}


void UpdateVisitor::visit(SGObject* sgo) {
}

void UpdateVisitor::visit(Node* node) {
//  node->retained->update();
}

void UpdateVisitor::visit(Group* g) {
  visit((Node*)g);

  g->childs->update();
  NodeListIterator* i = g->getChilds();
  while (i->hasNext() == true) {
    Node* child = i->next();
    if (child != 0) {
      child->accept(this);
    }
  }
  delete i;
}

void UpdateVisitor::visit(TGroup* g) {
  visit((Group*)g);
  g->transform.update();
}

void UpdateVisitor::visit(Leaf* leaf) {
  visit((Node*)leaf);
}

void UpdateVisitor::visit(Shape3D* shape3d) {
  // do std. node stuff
  visit((Leaf*)shape3d);

  shape3d->geom.update();

  GeometryListIterator* geoms = shape3d->getGeometries();
  while (geoms->hasNext() == true) {
    geoms->next()->accept(this);
  }
  delete(geoms);

  // and app
  shape3d->app.update();
  Appearance* app = shape3d->app.get();
  if (app != 0) {
    app->accept(this);
    app->releaseReference();
  }
}

void UpdateVisitor::visit(TriangleArray* tArray) {
  if (tArray->coords != 0) {
    tArray->coords->update();
  }

  if (tArray->colors != 0) {
    tArray->colors->update();
  }

  if (tArray->textureCoords != 0) {
    int max = tArray->getMaxMultiTextures();
    for (int i=0; i<max; i++) {
      if (tArray->textureCoords[i] != 0) {
        tArray->textureCoords[i]->update();
      }
    }
  }

  if (tArray->normals != 0) {
    tArray->normals->update();
  }

  if (tArray->stripVertexCounts != 0) {
    tArray->stripVertexCounts->update();
  }
}

void UpdateVisitor::visit(IndexedTriangleArray* itArray) {
  visit((TriangleArray*)itArray);
  if (itArray->indices != 0) {
    itArray->indices->update();
  }
}

void UpdateVisitor::visit(InterleavedTriangleArray* array) {
  array->vertexData.update();
}

void UpdateVisitor::visit(IndexedInterleavedTriangleArray* array) {
  array->indices.update();
  visit((InterleavedTriangleArray*)array);
}

void UpdateVisitor::visit(Appearance* app) {
  app->polygonAttributes->update();

  app->renderingAttributes->update();

  app->material->update();

  Material* material = app->getMaterial();
  if (material != 0) {
    if (material->color != 0) {
      material->color->update();
    }
    material->releaseReference();
  }

  int maxTex = app->getMaxMultiTextures();
  for (int i=0; i<maxTex; i++) {
    // integrate texture-updates
    if (app->textures[i] != 0) {
      app->textures[i]->update();
      Texture* texture = app->textures[i]->get();
      if (texture != 0) {
        texture->accept(this);
        texture->releaseReference();
      }
      if (app->texGens[i] != 0) {
        app->texGens[i]->update();
      }
    }
  }
}

void UpdateVisitor::visit(Texture* texture) {
  texture->image.update();
}
