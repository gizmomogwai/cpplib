#include <sg/visitors/OGLRenderVisitor.h>
#include <sg/nodes/SGObserver.h>

#include <lang/CleanUpObject.h>
#include <iostream>
#include <sstream>
#include <util/Iterator.h>
#include <assert.h>
#include <lang/Exception.h>

#include <sg/visitors/WGLFontManager.h>
#include <sg/visitors/GLUTFontManager.h>
#include <sg/nodeComponents/Light.h>
#include <image/PixelFormat.h>
#include <sg/data/VertexData.h>
#include <sg/nodeComponents/geom/IndexedInterleavedTriangleArray.h>

#include <sg/nodeComponents/app/PolygonAttributes.h>
#include <sg/nodeComponents/app/Material.h>
#include <sg/nodeComponents/app/Texture.h>
#include <sg/nodeComponents/app/SGImage.h>
#include <sg/nodeComponents/app/RenderingAttributes.h>

#include <sg/visitors/OglTools.h>


#ifdef LINUX
  #ifndef OSX
    #include <GL/glx.h>
  #endif
#endif

OGLRenderVisitor::OGLRenderVisitor(OGLFontManager* _fontManager)
  : fontManager(_fontManager) {
  /*
  std::cout << "OGLVendor:   " << glGetString(GL_VENDOR) << std::endl;
  std::cout << "OGLRenderer: " << glGetString(GL_RENDERER) << std::endl;
  std::cout << "OGLVersion:  " << glGetString(GL_VERSION) << std::endl;
  std::cout << "OGLExt:      " << glGetString(GL_EXTENSIONS) << std::endl;
  */

//  fFence = gluCheckExtension ("GL_APPLE_fence", strExt);

}

OGLRenderVisitor::~OGLRenderVisitor() {
  if (fontManager != nullptr) {
    delete(fontManager);
    fontManager = 0;
  }
}

void OGLRenderVisitor::visit(Root* root) {
  glClearColor(0, 0, 0, 1);
  assert(OglTools::checkOglState(__FILE__, __LINE__));

  glColor3f(1, 1, 1);
  assert(OglTools::checkOglState(__FILE__, __LINE__));

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  assert(OglTools::checkOglState(__FILE__, __LINE__));

  glFrontFace(GL_CCW);
  assert(OglTools::checkOglState(__FILE__, __LINE__));

  glCullFace(GL_BACK);
  assert(OglTools::checkOglState(__FILE__, __LINE__));

  glEnable(GL_CULL_FACE);
  // glDisable(GL_CULL_FACE);
  assert(OglTools::checkOglState(__FILE__, __LINE__));

  glDisable(GL_DITHER);
  assert(OglTools::checkOglState(__FILE__, __LINE__));

  glDisable(GL_DEPTH_TEST);
  assert(OglTools::checkOglState(__FILE__, __LINE__));

  //  glDepthFunc(GL_LESS);
  //assert(OglTools::checkOglState(__FILE__, __LINE__));

  glDisable(GL_LIGHTING);
  assert(OglTools::checkOglState(__FILE__, __LINE__));

  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
  assert(OglTools::checkOglState(__FILE__, __LINE__));

  tManager.deleteUnusedTextures();

  imageWidth = root->imageWidth;
  imageHeight = root->imageHeight;

  NodeListIterator* i = root->getChilds();
  CleanUpObject<NodeListIterator> cleaner(i);
  while (i->hasNext() == true) {
    glMatrixMode(GL_MODELVIEW);
    assert(OglTools::checkOglState(__FILE__, __LINE__));

    glLoadIdentity();
    assert(OglTools::checkOglState(__FILE__, __LINE__));

    Node* child = i->next();
    child->accept(this);
  }

}

void OGLRenderVisitor::visit(SGObserver* observer) {
  createBillboards(observer);

  glMatrixMode(GL_MODELVIEW);
  assert(OglTools::checkOglState(__FILE__, __LINE__));

  glLoadIdentity();
  assert(OglTools::checkOglState(__FILE__, __LINE__));

  RCTransform3D* cameraTransform = observer->getCameraTransform();
  if (cameraTransform != nullptr) {
    glMultMatrixf((GLfloat*)cameraTransform->m);
    assert(OglTools::checkOglState(__FILE__, __LINE__));
    cameraTransform->releaseReference();
  }

  visit((ProjectionGroup*)observer);

  glMatrixMode(GL_MODELVIEW);
  assert(OglTools::checkOglState(__FILE__, __LINE__));

  glLoadIdentity();
  assert(OglTools::checkOglState(__FILE__, __LINE__));
}


void OGLRenderVisitor::visit(ProjectionGroup* pGroup) {

  glMatrixMode(GL_PROJECTION);
  assert(OglTools::checkOglState(__FILE__, __LINE__));

  glLoadIdentity();
  assert(OglTools::checkOglState(__FILE__, __LINE__));

  if (pGroup->camera != nullptr) {
    float imageRatio = 1;
    if (imageHeight != 0) {
      imageRatio = (float)imageWidth / (float)imageHeight;
    }

    Camera* c = pGroup->camera;

//    c->aspectRatio = imageRatio;
    Transform3D* t3d = c->getProjection();
    CleanUpObject<Transform3D> cleaner(t3d);

    glMultMatrixf((GLfloat*)t3d->m);
    assert(OglTools::checkOglState(__FILE__, __LINE__));

    // OGLRenderVisitor::printMatrices();
  } else if (pGroup->parallel != nullptr) {

    float f = pGroup->parallel->factor;
    float halfWidth = imageWidth / 2.0f / f;
    float halfHeight = imageHeight / 2.0f / f;
    glOrtho(-halfWidth, halfWidth, -halfHeight, halfHeight, pGroup->parallel->nearClipping, pGroup->parallel->farClipping);
    assert(OglTools::checkOglState(__FILE__, __LINE__));

  } else {
    throw Exception("weder camera noch parallel angegeben", __FILE__, __LINE__);
  }

  glMatrixMode(GL_MODELVIEW);
  assert(OglTools::checkOglState(__FILE__, __LINE__));

  visit((Group*)pGroup);
}


void OGLRenderVisitor::createBillboards(SGObserver* observer) {
  RCTransform3D* help = observer->getTransform();
  RCTransform3D* cameraT = observer->getCameraTransform();
  observerTransformation.set(cameraT);
  cameraT->releaseReference();

  yAxisBillboard.setID();

  Vector3f x;
  Vector3f y(0, 1, 0);
  Vector3f z(help->matrix.m20, help->matrix.m21, help->matrix.m22);

  x.cross(&y, &z);
  x.normalize();

  z.cross(&x, &y);
  z.normalize();

  yAxisBillboard.matrix.m00 = x.dx;
  yAxisBillboard.matrix.m01 = x.dy;
  yAxisBillboard.matrix.m02 = x.dz;

  yAxisBillboard.matrix.m10 = y.dx;
  yAxisBillboard.matrix.m11 = y.dy;
  yAxisBillboard.matrix.m12 = y.dz;

  yAxisBillboard.matrix.m20 = z.dx;
  yAxisBillboard.matrix.m21 = z.dy;
  yAxisBillboard.matrix.m22 = z.dz;

  // no translation
  yAxisBillboard.matrix.m30 = 0.0f;
  yAxisBillboard.matrix.m31 = 0.0f;
  yAxisBillboard.matrix.m32 = 0.0f;

  help->releaseReference();

//  std::cout << "yaxis bei berechnung: " << yAxisBillboard.toString() << std::endl;
}

void OGLRenderVisitor::visit(SGObject* sgo) {
}

void OGLRenderVisitor::visit(Node* node) {
}

void OGLRenderVisitor::visit(Group* group) {
  NodeListIterator* i = group->getChilds();
  CleanUpObject<NodeListIterator> iteratorCleaner(i);
  while (i->hasNext() == true) {
    Node* child = i->next();
    child->accept(this);
  }
}

void OGLRenderVisitor::visit(SwitchGroup* group) {
  int idx = group->getSwitchedIndex();
  if (idx >= group->getChildCount()) {
    throw Exception("OGLRenderVisitor::visit(SwitchGroup*) so ja wohl nicht", __FILE__, __LINE__);
  }

  CleanUpObject<NodeListIterator> childs(group->getChilds());
  Node* child = childs->next();
  for (int i=0; i<idx; i++) {
    child = childs->next();
  }

  if (child == 0) {
    throw Exception("OGLRenderVisitor::visit(SwitchGroup*) child should not be 0", __FILE__, __LINE__);
  }
  child->accept(this);
}

void OGLRenderVisitor::printMatrices() {

  Transform3D t3d;
  GLint matrixMode;
  glGetIntegerv(GL_MATRIX_MODE, &matrixMode);

  glGetFloatv(GL_MODELVIEW_MATRIX, t3d.m);
  std::cout << "modelview: " << t3d.toString() << std::endl;

  glGetFloatv(GL_PROJECTION_MATRIX, t3d.m);
  std::cout << "projection: " << t3d.toString() << std::endl;

  glMatrixMode(matrixMode);
}

void OGLRenderVisitor::checkMatrices() {

  Transform3D t3d;
  GLint matrixMode;
  glGetIntegerv(GL_MATRIX_MODE, &matrixMode);

  glGetFloatv(GL_MODELVIEW_MATRIX, t3d.m);
  if (t3d.matrix.m00 > 100) {
    std::cout << "ohje" << std::endl;
  }
//  std::cout << "modelview: " << t3d.toString() << std::endl;

  glGetFloatv(GL_PROJECTION_MATRIX, t3d.m);
//  std::cout << "projection: " << t3d.toString() << std::endl;

  glMatrixMode(matrixMode);
}



void OGLRenderVisitor::visit(TGroup* tg) {
  glPushMatrix();
  assert(OglTools::checkOglState(__FILE__, __LINE__));

  RCTransform3D* t3d = tg->getTransform();
  if (t3d != nullptr) {
    glMultMatrixf((GLfloat*)t3d->m);
    assert(OglTools::checkOglState(__FILE__, __LINE__));

//    checkMatrices();

    t3d->releaseReference();
  }

  NodeListIterator* i = tg->getChilds();
  CleanUpObject<NodeListIterator> iteratorCleaner(i);
  while (i->hasNext()) {
    i->next()->accept(this);
  }

  glPopMatrix();
  assert(OglTools::checkOglState(__FILE__, __LINE__));
}

void OGLRenderVisitor::visit(FogGroup* fg) {

  glPushAttrib(GL_ALL_ATTRIB_BITS);
  assert(OglTools::checkOglState(__FILE__, __LINE__));

  FogAttributes* fAtts = fg->fog;
  glEnable(GL_FOG);
  assert(OglTools::checkOglState(__FILE__, __LINE__));
  glFogi(GL_FOG_MODE, GL_LINEAR);
  assert(OglTools::checkOglState(__FILE__, __LINE__));
  glHint(GL_FOG_HINT, GL_NICEST);
  assert(OglTools::checkOglState(__FILE__, __LINE__));

  GLfloat fogColor[4] = {fAtts->r, fAtts->g, fAtts->b, 1.0f};
  glFogfv(GL_FOG_COLOR, fogColor);
  assert(OglTools::checkOglState(__FILE__, __LINE__));

  glFogf(GL_FOG_START, fAtts->start);
  assert(OglTools::checkOglState(__FILE__, __LINE__));
  glFogf(GL_FOG_END, fAtts->end);
  assert(OglTools::checkOglState(__FILE__, __LINE__));

  visit((Group*)fg);

  glPopAttrib();
  assert(OglTools::checkOglState(__FILE__, __LINE__));
}


void OGLRenderVisitor::visit(LightGroup* lGroup) {
  Light* l = lGroup->light;

  glEnable(GL_LIGHTING);
  assert(OglTools::checkOglState(__FILE__, __LINE__));

  Color3f* aC = l->ambientColor;
  GLfloat ambient[] = {aC->rgb[0], aC->rgb[1], aC->rgb[2], 1.0f};

  Color3f* dC = l->diffuseColor;
  GLfloat diffuse[] = {dC->rgb[0], dC->rgb[1], dC->rgb[2], 1.0f};

  Color3f* sC = l->specularColor;
  GLfloat specular[] = {sC->rgb[0], sC->rgb[1], sC->rgb[2], 1.0f};

  Point4f* dP = &(l->homogenPosition);
  GLfloat homogen[] = {dP->x, dP->y, dP->z, dP->w};

  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
  assert(OglTools::checkOglState(__FILE__, __LINE__));

  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
  assert(OglTools::checkOglState(__FILE__, __LINE__));

  glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
  assert(OglTools::checkOglState(__FILE__, __LINE__));

  glLightfv(GL_LIGHT0, GL_POSITION, homogen);
  assert(OglTools::checkOglState(__FILE__, __LINE__));

  glEnable(GL_LIGHT0);
  assert(OglTools::checkOglState(__FILE__, __LINE__));

  visit((Group*)lGroup);

  glDisable(GL_LIGHT0);
  assert(OglTools::checkOglState(__FILE__, __LINE__));

  glDisable(GL_LIGHTING);
  assert(OglTools::checkOglState(__FILE__, __LINE__));
}


void OGLRenderVisitor::bringUpTexture(Texture* texture,
                                      TexGen* texGen) {

  glEnable(GL_TEXTURE_2D);
  assert(OglTools::checkOglState(__FILE__, __LINE__));

  tManager.activate(texture);

  if (texGen != nullptr) {
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    assert(OglTools::checkOglState(__FILE__, __LINE__));

    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    assert(OglTools::checkOglState(__FILE__, __LINE__));

    glTexGenfv(GL_S, GL_OBJECT_PLANE, texGen->s);
    assert(OglTools::checkOglState(__FILE__, __LINE__));

    glTexGenfv(GL_T, GL_OBJECT_PLANE, texGen->t);
    assert(OglTools::checkOglState(__FILE__, __LINE__));

    glEnable(GL_TEXTURE_GEN_S);
    assert(OglTools::checkOglState(__FILE__, __LINE__));

    glEnable(GL_TEXTURE_GEN_T);
    assert(OglTools::checkOglState(__FILE__, __LINE__));

    texGen->releaseReference();
  }

  GLint wrap = (texture->wrapS == true) ? GL_REPEAT : GL_CLAMP;
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
  assert(OglTools::checkOglState(__FILE__, __LINE__));

  wrap = (texture->wrapT == true) ? GL_REPEAT : GL_CLAMP;
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
  assert(OglTools::checkOglState(__FILE__, __LINE__));

  SGImage* image = texture->getImage();
  if (image != nullptr) {
    if (image->getFormat()->bitPerPixel == 32) {
      glEnable(GL_ALPHA_TEST);
      glAlphaFunc(GL_GREATER, 0.2f);
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
      glColor4f(1, 1, 1, 1);
    } else if (image->getFormat()->bitPerPixel == 24) {
      glDisable(GL_ALPHA_TEST);
      glDisable(GL_BLEND);
    }
    image->releaseReference();
  }

  texture->releaseReference();
}


void OGLRenderVisitor::startApp(Appearance* app) {
//glPushAttrib(GL_FOG_BIT | GL_DEPTH_BUFFER_BIT); // GL_ALL_ATTRIB_BITS
  glPushAttrib(GL_ALL_ATTRIB_BITS);
  assert(OglTools::checkOglState(__FILE__, __LINE__));

  PolygonAttributes* pAtts = app->getPolygonAttributes();
  if (pAtts != nullptr) {
    if (pAtts->polyMode == PolygonAttributes::POLYGON_FILL) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    } else if (pAtts->polyMode == PolygonAttributes::POLYGON_LINE) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else if (pAtts->polyMode == PolygonAttributes::POLYGON_POINT) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    }
    pAtts->releaseReference();
  }
  assert(OglTools::checkOglState(__FILE__, __LINE__));

  Material* material = app->getMaterial();
  if (material != nullptr) {

    if (material->lighted == true) {
      glEnable(GL_LIGHTING);
    } else {
      glDisable(GL_LIGHTING);
    }
    assert(OglTools::checkOglState(__FILE__, __LINE__));

    RCColor3f* color = material->getColor();
    if (color != nullptr) {
      glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
      glEnable(GL_COLOR_MATERIAL);
      glColor3fv(color->rgb);
      color->releaseReference();
    }

    material->releaseReference();
  } else {
    glDisable(GL_LIGHTING);
    assert(OglTools::checkOglState(__FILE__, __LINE__));
  }

  RenderingAttributes* rAtts = app->getRenderingAttributes();
  if (rAtts != nullptr) {
    // depth test
    if (rAtts->zBufferRead == true) {
      glEnable(GL_DEPTH_TEST);
      assert(OglTools::checkOglState(__FILE__, __LINE__));

      glDepthFunc(GL_LESS);
      assert(OglTools::checkOglState(__FILE__, __LINE__));
    } else {

      glDisable(GL_DEPTH_TEST);
      assert(OglTools::checkOglState(__FILE__, __LINE__));
    }
    assert(OglTools::checkOglState(__FILE__, __LINE__));

    // zbuffer write
    if (rAtts->zBufferWrite == true) {
      glDepthMask(GL_TRUE);
    } else {
      glDepthMask(GL_FALSE);
    }
    assert(OglTools::checkOglState(__FILE__, __LINE__));

    rAtts->releaseReference();
  }
  assert(OglTools::checkOglState(__FILE__, __LINE__));

  int maxMultis = app->getMaxMultiTextures();
  if (maxMultis == 1) {
    // single texturing
    Texture* texture = app->getTexture(0);
    if (texture != nullptr) {
      bringUpTexture(texture, app->getTexGen(0));
    }
  } else {
    // multitexturing
    for (int i=0; i<maxMultis; i++) {
      Texture* texture = app->getTexture(i);
      if (texture != nullptr) {
        glActiveTextureARB(GL_TEXTURE0_ARB + i);
        assert(OglTools::checkOglState(__FILE__, __LINE__));

        bringUpTexture(texture, app->getTexGen(i));
      }
    }
  }
}

void OGLRenderVisitor::cleanUpTexture(Texture* texture, TexGen* texGen) {
  glDisable(GL_TEXTURE_2D);
  assert(OglTools::checkOglState(__FILE__, __LINE__));

  if (texGen != nullptr) {
    glDisable(GL_TEXTURE_GEN_S);
    assert(OglTools::checkOglState(__FILE__, __LINE__));

    glDisable(GL_TEXTURE_GEN_T);
    assert(OglTools::checkOglState(__FILE__, __LINE__));

    texGen->releaseReference();
  }
  texture->releaseReference();

}

void OGLRenderVisitor::endApp(Appearance* app) {

  int maxMultis = app->getMaxMultiTextures();
  if (maxMultis == 1) {
    // single texturing
    Texture* texture = app->getTexture(0);
    if (texture != nullptr) {
      cleanUpTexture(texture, app->getTexGen(0));
    }
  } else {
    // multitexturing
    for (int i=0; i<maxMultis; i++) {
      Texture* texture = app->getTexture(i);
      if (texture != nullptr) {
        glActiveTextureARB(GL_TEXTURE0_ARB + i);
        assert(OglTools::checkOglState(__FILE__, __LINE__));

        cleanUpTexture(texture, app->getTexGen(i));
      }
    }
  }

  glPopAttrib();
  assert(OglTools::checkOglState(__FILE__, __LINE__));
}


void OGLRenderVisitor::visit(Shape3D* shape3d) {
  Appearance* a = shape3d->app.get();
  if (a != nullptr) {
    startApp(a);
  }

  GeometryListIterator* g = shape3d->getGeometries();
  CleanUpObject<GeometryListIterator> cleaner(g);
  if (g != nullptr) {
    while (g->hasNext() == true) {
      g->next()->accept(this);
    }
  }

  if (a != nullptr) {
    endApp(a);
    a->releaseReference();
  }

}


void OGLRenderVisitor::visit(OrientedShape3D* oShape3d) {
  glPushMatrix();
  assert(OglTools::checkOglState(__FILE__, __LINE__));

//  Transform3D current2;
//  glGetFloatv(GL_MODELVIEW_MATRIX, current2.m);
//  assert(OglTools::checkOglState(__FILE__, __LINE__));
//
//  std::cout << "vorher: " << current2.toString() << std::endl;
//  std::cout << "yaxisbillboard: " << yAxisBillboard.toString() << std::endl;

  glMultMatrixf((GLfloat*)yAxisBillboard.m);
  assert(OglTools::checkOglState(__FILE__, __LINE__));

  visit((Shape3D*)oShape3d);

  glPopMatrix();
  assert(OglTools::checkOglState(__FILE__, __LINE__));

//  glPushMatrix();
//  assert(OglTools::checkOglState(__FILE__, __LINE__));
//
//  Transform3D current;
//  glGetFloatv(GL_MODELVIEW_MATRIX, current.m);
//  assert(OglTools::checkOglState(__FILE__, __LINE__));
//  std::cout << "falsch: " << current.toString() << std::endl;
//
//  Transform3D cameraRotation;
//  cameraRotation.setRotation(&observerTransformation);
//
//  Transform3D billboardRotation;
//  billboardRotation.setRotation(&yAxisBillboard);
//
//  std::cout << "billboard: " << billboardRotation.toString() << std::endl;
//  std::cout << "camera: " << cameraRotation.toString() << std::endl;
//  Transform3D result;
//  result.mul(&cameraRotation, &billboardRotation);
//
//  current.setRotation(&result);
//  std::cout << "falsch: " << current.toString() << std::endl;
//
//  glLoadMatrixf((GLfloat*)current.m);
//
//  assert(OglTools::checkOglState(__FILE__, __LINE__));
//
//  visit((Shape3D*)oShape3d);
//
//  glPopMatrix();
//  assert(OglTools::checkOglState(__FILE__, __LINE__));
}


void OGLRenderVisitor::visit(Leaf* shape3d) {
}

void OGLRenderVisitor::visit(Geometry* geom) {
}

void OGLRenderVisitor::visit(TeapotGeometry* geom) {
  //glutWireSphere(50, 10, 10);
  //glutWireTeapot(50);
  assert(OglTools::checkOglState(__FILE__, __LINE__));
  //glutSolidTorus(1, 3.2, 10, 10);
}

void OGLRenderVisitor::visit(Text3D* text3d) {
  if (fontManager != nullptr) {
    fontManager->render(text3d);
  }
}

void OGLRenderVisitor::activateTexCoordPointer(Array2f* tCoords) {

  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  assert(OglTools::checkOglState(__FILE__, __LINE__));

  glTexCoordPointer(2, GL_FLOAT, 0, tCoords->get(0));
  assert(OglTools::checkOglState(__FILE__, __LINE__));

  tCoords->releaseReference();
}

void OGLRenderVisitor::bringUpTCoords(TriangleArray* tArray) {
  if (tArray->textureCoords != nullptr) {
    int max = tArray->getMaxMultiTextures();
    if (max == 1) {
      if (tArray->textureCoords[0] != nullptr) {
        Array2f* tCoords = tArray->textureCoords[0]->get();
        if (tCoords != nullptr) {
          activateTexCoordPointer(tCoords);
        }
      }
    } else {
      for (int i=0; i<max; i++) {
        if (tArray->textureCoords[i] != nullptr) {
          Array2f* tCoords = tArray->textureCoords[i]->get();
          if (tCoords != nullptr) {
            glClientActiveTextureARB(GL_TEXTURE0_ARB + i);
            assert(OglTools::checkOglState(__FILE__, __LINE__));

            activateTexCoordPointer(tCoords);
          }
        }
      }
    }
  }
}


void OGLRenderVisitor::deactivateTexCoordPointer(Array2f* tCoords) {

  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  assert(OglTools::checkOglState(__FILE__, __LINE__));

  tCoords->releaseReference();
}

void OGLRenderVisitor::cleanUpTCoords(TriangleArray* tArray) {
  if (tArray->textureCoords != nullptr) {
    int max = tArray->getMaxMultiTextures();
    if (max == 1) {
      if (tArray->textureCoords[0] != nullptr) {
        if (tArray->textureCoords[0] != nullptr) {
          Array2f* tCoords = tArray->textureCoords[0]->get();
          if (tCoords != nullptr) {
            deactivateTexCoordPointer(tCoords);
          }
        }
      }
    } else {
      for (int i=0; i<max; i++) {
        if (tArray->textureCoords[i] != nullptr) {
          Array2f* tCoords = tArray->textureCoords[i]->get();
          if (tCoords != nullptr) {
            glClientActiveTextureARB(GL_TEXTURE0_ARB + i);
            assert(OglTools::checkOglState(__FILE__, __LINE__));

            deactivateTexCoordPointer(tCoords);
          }
        }
      }
    }

  }
}


void OGLRenderVisitor::visit(IndexedTriangleArray* itArray) {
  if (itArray->coords == 0) {
    std::cout <<"OGLRenderVisitor::visit(IndexedTriangleArray*) "
      << "- einige punkte sollten schon vorhanden sein" << std::endl;
  } else {
    Array3f* coords = itArray->coords->get();
    Array3f* colors = 0;
    Array3f* normals = 0;
    Array1i* indices = 0;

    if (coords != nullptr) {
      if (itArray->colors != nullptr) {
        colors = itArray->colors->get();
      }
      if (itArray->normals != nullptr) {
        normals = itArray->normals->get();
      }
      if (itArray->indices != nullptr) {
        indices = itArray->indices->get();
      }

      glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);
      assert(OglTools::checkOglState(__FILE__, __LINE__));

      glEnableClientState(GL_VERTEX_ARRAY);
      assert(OglTools::checkOglState(__FILE__, __LINE__));

      glVertexPointer(3, GL_FLOAT, 0, coords->get(0));
      assert(OglTools::checkOglState(__FILE__, __LINE__));

      if (colors != nullptr) {
        glEnableClientState(GL_COLOR_ARRAY);
        assert(OglTools::checkOglState(__FILE__, __LINE__));

        glColorPointer(3, GL_FLOAT, 0, colors->get(0));
        assert(OglTools::checkOglState(__FILE__, __LINE__));

      }

      bringUpTCoords(itArray);

      if (normals != nullptr) {
        glEnableClientState(GL_NORMAL_ARRAY);
        assert(OglTools::checkOglState(__FILE__, __LINE__));

        glNormalPointer(GL_FLOAT, 0, normals->get(0));
        assert(OglTools::checkOglState(__FILE__, __LINE__));
      }

      GLenum help = type2Enum(itArray->type);

      glDrawElements(help, indices->getSize(), GL_UNSIGNED_INT, indices->get(0));
      assert(OglTools::checkOglState(__FILE__, __LINE__));

      glPopClientAttrib();
      assert(OglTools::checkOglState(__FILE__, __LINE__));

      if (colors != nullptr) {
        colors->releaseReference();
      }
      if (normals != nullptr) {
        normals->releaseReference();
      }
      cleanUpTCoords(itArray);
      if (indices != nullptr) {
        indices->releaseReference();
      }
    }
    if (coords != nullptr) {
      coords->releaseReference();
    }
  }
} // visit indexedtrianglearray

GLenum OGLRenderVisitor::type2Enum(TriangleArrayType type) {

  if (type == TRIS) {
    return GL_TRIANGLES;
  } else if (type == FAN) {
    return GL_TRIANGLE_FAN;
  } else if (type == STRIP) {
    return GL_TRIANGLE_STRIP;
  } else {
    throw Exception("OGLRenderVisitor::type2Enum - type not supported", __FILE__, __LINE__);
  }

}

void OGLRenderVisitor::visit(TriangleArray* tArray) {
  if (tArray->coords == 0) {
    std::cout << "RenderVisitor::visit(TriangleFan*) - einiges punkte sollte ein fan mindestens haben" << std::endl;
  } else {
    Array3f* coords = tArray->coords->get();
    Array3f* colors = 0;
    Array3f* normals = 0;
    if (tArray->colors != nullptr) {
      colors = tArray->colors->get();
    }
    if (tArray->normals != nullptr) {
      normals = tArray->normals->get();
    }

    if (coords != nullptr) {
      glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);
      assert(OglTools::checkOglState(__FILE__, __LINE__));

      glEnableClientState(GL_VERTEX_ARRAY);
      assert(OglTools::checkOglState(__FILE__, __LINE__));

      glVertexPointer(3, GL_FLOAT, 0, coords->get(0));
      assert(OglTools::checkOglState(__FILE__, __LINE__));

      if (colors != nullptr) {
        glEnableClientState(GL_COLOR_ARRAY);
        assert(OglTools::checkOglState(__FILE__, __LINE__));

        glColorPointer(3, GL_FLOAT, 0, colors->get(0));
        assert(OglTools::checkOglState(__FILE__, __LINE__));
      }

      bringUpTCoords(tArray);

      if (normals != nullptr) {
        glEnableClientState(GL_NORMAL_ARRAY);
        assert(OglTools::checkOglState(__FILE__, __LINE__));

        glNormalPointer(GL_FLOAT, 0, normals->get(0));
        assert(OglTools::checkOglState(__FILE__, __LINE__));
      }

      GLenum help = type2Enum(tArray->type);
      if (tArray->stripVertexCounts == 0) {

        glDrawArrays(help, 0, coords->getSize());
        assert(OglTools::checkOglState(__FILE__, __LINE__));

      } else {
        Array1i* stripVertexCounts = tArray->stripVertexCounts->get();
        if (stripVertexCounts != nullptr) {
          int startIdx = 0;
          for (int count = 0; count < stripVertexCounts->getSize(); count++) {
            int length = *(stripVertexCounts->get(count));

            glDrawArrays(help, startIdx, length);
            assert(OglTools::checkOglState(__FILE__, __LINE__));

            startIdx += length;
          }

          stripVertexCounts->releaseReference();
        }
      }

      glPopClientAttrib();
      assert(OglTools::checkOglState(__FILE__, __LINE__));
    }
    if (coords != nullptr) {
      coords->releaseReference();
    }
    if (colors != nullptr) {
      colors->releaseReference();
    }
    if (normals != nullptr) {
      normals->releaseReference();
    }
    cleanUpTCoords(tArray);
  }

} // visittrianglearray


void OGLRenderVisitor::visit(InterleavedTriangleArray* array) {
  VertexData* data = array->vertexData.get();
  if (data != nullptr) {
    glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);
    assert(OglTools::checkOglState(__FILE__, __LINE__));

    glEnableClientState(GL_VERTEX_ARRAY);
    assert(OglTools::checkOglState(__FILE__, __LINE__));

    int stride = data->getTupelSize() * 4;
    glVertexPointer(3, GL_FLOAT, stride, data->getCoord(0));
    assert(OglTools::checkOglState(__FILE__, __LINE__));

    if (data->containsNormalData() == true) {
      glEnableClientState(GL_NORMAL_ARRAY);
      assert(OglTools::checkOglState(__FILE__, __LINE__));

      glNormalPointer(GL_FLOAT, stride, data->getNormal(0));
      assert(OglTools::checkOglState(__FILE__, __LINE__));
    }

    if (data->containsTexCoordData() == true) {
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      assert(OglTools::checkOglState(__FILE__, __LINE__));

      glTexCoordPointer(2, GL_FLOAT, stride, data->getTexCoord(0));
      assert(OglTools::checkOglState(__FILE__, __LINE__));
    }

    GLenum help = type2Enum(array->type);

    glDrawArrays(help, 0, data->getSize());
    assert(OglTools::checkOglState(__FILE__, __LINE__));

    data->releaseReference();

    glPopClientAttrib();
    assert(OglTools::checkOglState(__FILE__, __LINE__));
  }
}

void OGLRenderVisitor::visit(IndexedInterleavedTriangleArray* array) {
  VertexData* data = array->vertexData.get();
  if (data != nullptr) {
    glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);
    assert(OglTools::checkOglState(__FILE__, __LINE__));

    glEnableClientState(GL_VERTEX_ARRAY);
    assert(OglTools::checkOglState(__FILE__, __LINE__));

    int stride = data->getTupelSize() * 4;
    glVertexPointer(3, GL_FLOAT, stride, data->getCoord(0));
    assert(OglTools::checkOglState(__FILE__, __LINE__));

    if (data->containsNormalData() == true) {
      glEnableClientState(GL_NORMAL_ARRAY);
      assert(OglTools::checkOglState(__FILE__, __LINE__));

      glNormalPointer(GL_FLOAT, stride, data->getNormal(0));
      assert(OglTools::checkOglState(__FILE__, __LINE__));
    }

    if (data->containsTexCoordData() == true) {
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      assert(OglTools::checkOglState(__FILE__, __LINE__));

      glTexCoordPointer(2, GL_FLOAT, stride, data->getTexCoord(0));
      assert(OglTools::checkOglState(__FILE__, __LINE__));
    }

    GLenum help = type2Enum(array->type);
    Array1i* indices = array->indices.get();
    if (indices != nullptr) {
      glDrawElements(help, indices->getSize(), GL_UNSIGNED_INT, indices->get(0));
      assert(OglTools::checkOglState(__FILE__, __LINE__));
      indices->releaseReference();
    }

    data->releaseReference();

    glPopClientAttrib();
    assert(OglTools::checkOglState(__FILE__, __LINE__));
  }
}

void OGLRenderVisitor::visit(Appearance* app) {
}

void OGLRenderVisitor::visit(Texture* texture) {
}
