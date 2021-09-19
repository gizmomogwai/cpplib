#pragma once

#include <assert.h>
#include <sg/math/RCTransform3D.h>

#include <sg/visitors/OGLRenderVisitor.h>

#include <iostream>

#include <vecmath/bounds/BoundVisitor.h>
#include <vecmath/bounds/EmptyBound.h>
#include <vecmath/bounds/InfiniteBound.h>
#include <vecmath/bounds/AabbBound.h>

#include <io/file/FileInputStream.h>
#include <io/DataInputStream.h>
#include <string>
#include <lang/Integer.h>

class OGLBoundRenderer : public BoundVisitor {

  private:
    float hue;
    TGroup* tg;

  public:
    OGLBoundRenderer() : tg(0) {
      reset();
    }

    void reset() {
      hue = 0.0f;
    }

    void visit(EmptyBound* b) {
    }

    void visit(InfiniteBound* b) {
    }

    void visit(AabbBound* b) {

      hue += 10.0f;
      if (hue >= 360) hue = 0;

//        std::cout << "OGLBoundRenderer: " << b->toString() << std::endl;
//      std::cout << std::hex << b << std::endl;
      Point3f* minP = b->getMin();
      Point3f* maxP = b->getMax();

      glDisable(GL_TEXTURE_2D);
      assert(glGetError() == GL_NO_ERROR);

      glDisable(GL_LIGHTING);
      assert(glGetError() == GL_NO_ERROR);

      Color3f* color = Color3f::createFromHSB(hue, 1, 0.5f);
      glColor3fv(color->rgb);
      delete(color);

      assert(glGetError() == GL_NO_ERROR);
      glBegin(GL_LINE_STRIP);
        // viereck unten
        glVertex3f(minP->x, minP->y, minP->z);
        glVertex3f(maxP->x, minP->y, minP->z);

        glVertex3f(maxP->x, minP->y, maxP->z);
        glVertex3f(minP->x, minP->y, maxP->z);
        glVertex3f(minP->x, minP->y, minP->z);
      glEnd();
      assert(glGetError() == GL_NO_ERROR);

      glBegin(GL_LINE_STRIP);
        // viereck oben
        glVertex3f(minP->x, maxP->y, minP->z);
        glVertex3f(maxP->x, maxP->y, minP->z);

        glVertex3f(maxP->x, maxP->y, maxP->z);
        glVertex3f(minP->x, maxP->y, maxP->z);
        glVertex3f(minP->x, maxP->y, minP->z);
      glEnd();
      assert(glGetError() == GL_NO_ERROR);

      glBegin(GL_LINES);
        // unten nach oben
        glVertex3f(minP->x, minP->y, minP->z);
        glVertex3f(minP->x, maxP->y, minP->z);

        glVertex3f(maxP->x, minP->y, minP->z);
        glVertex3f(maxP->x, maxP->y, minP->z);

        glVertex3f(maxP->x, minP->y, maxP->z);
        glVertex3f(maxP->x, maxP->y, maxP->z);

        glVertex3f(minP->x, minP->y, maxP->z);
        glVertex3f(minP->x, maxP->y, maxP->z);
      glEnd();
      assert(glGetError() == GL_NO_ERROR);
    }
};

class DebugOGLRenderVisitor : public OGLRenderVisitor {

  public:

    std::string toString() {
      return "DebugOGLRenderVisitor";
    }

    DebugOGLRenderVisitor() : OGLRenderVisitor(0) {
    }

    void visit(Root* root) {
//      std::cout << " +++ Root started" << std::endl;
      boundRenderer.reset();
      OGLRenderVisitor::visit(root);
//      std::cout << " +++ Root finished" << std::endl;
    }

    void visit(Node* node) {
      Bound* b = node->getBound();
      if (b != 0) {
        b->accept(&boundRenderer);
      }
    }

    void visit(Shape3D* shape) {

//      printMatrices();
//      RCTransform3D* local2World = shape->getLocal2World();
//      std::cout << "local2World" << local2World->toString() << std::endl;
//      local2World->releaseReference();

      OGLRenderVisitor::visit(shape);

      visit((Node*)shape);
    }

    void visit(TGroup* tg) {
      OGLRenderVisitor::visit(tg);

      visit((Node*)tg);
    }

    void visit(Group* group) {
      OGLRenderVisitor::visit(group);

      visit((Node*)group);
    }

  private:
    OGLBoundRenderer boundRenderer;

};
