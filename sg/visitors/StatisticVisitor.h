#ifndef _StatisticVisitor_h_
#define _StatisticVisitor_h_

#include <iostream>

#include <sg/visitors/Visitor.h>

#include <sg/visitors/StatisticInfo.h>

/** Visitor, der statistische Informationen ueber den
 * Szenegraphen ausgibt.
 *
 * <p>
 * Curriculum Vitae:
 * <ul>
 *   <li> 2001-03-17, cK, Created.
 * </ul>
 *
 * @version $Revision: 1.1.1.1 $, $Date: 2001/04/27 14:10:36 $
 *
 * @author cK, $Author: koestlin $
 */
class StatisticVisitor : public Visitor {

 public:
    /** Virtueller Deconstructor. */
    virtual ~StatisticVisitor() {
    }

    virtual void visit(Root* root) {
      info.clear();
      Visitor::visit(root);
      std::cout << info.toString() << std::endl;
    }

    virtual void visit(SGObserver* observer) {
      Visitor::visit(observer);
    }
    
    virtual void visit(SGObject* sgo) {}
  
    virtual void visit(Node* node) {}

    virtual void visit(Group* g) {
      info.update(g);      
      Visitor::visit(g);
    }

    virtual void visit(TGroup* tg) {
      info.update(tg);
      Visitor::visit(tg);
    }

    virtual void visit(FogGroup* g) {
      info.update(g);
      Visitor::visit(g);
    }

    virtual void visit(LightGroup* lg) {
      info.update(lg);
      Visitor::visit(lg);
    }

    virtual void visit(ProjectionGroup* g) {
      info.update(g);
      visit((Group*)g);
    }

    virtual void visit(Leaf* l) {}

    virtual void visit(Shape3D* s3d) {
      info.update(s3d);
      Visitor::visit(s3d);
    }

		virtual void visit(OrientedShape3D* os3d) {
      info.update(os3d);
      Visitor::visit(os3d);
		}

    virtual void visit(Geometry* geometry) {}

    virtual void visit(TeapotGeometry* teapot) {
      info.update(teapot);
    }

    virtual void visit(TriangleArray* tArray) {
      info.update(tArray);
    }

    virtual void visit(IndexedTriangleArray* itArray) {
      info.update(itArray);
    }

    virtual void visit(Text3D* text3d) {
      info.update(text3d);
    }

    virtual void visit(Appearance* app) {
      info.update(app);
    }

    virtual void visit(Texture* texture) {
    }

    virtual void visit(Behavior* b) {
      info.update(b);
    }

    std::string toString() {
      return("StatisticVisitor");
    }

  private:
    /** Statische infos. */
    StatisticInfo info;

};

#endif // _StatisticVisitor_h_
