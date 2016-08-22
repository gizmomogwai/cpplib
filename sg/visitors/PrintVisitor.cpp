#include <sg/visitors/PrintVisitor.h>
#include <iostream>
#include <sstream>
#include <sg/nodeComponents/app/Appearance.h>

#include <sg/nodes/Group.h>
#include <sg/nodes/Leaf.h>
#include <sg/nodes/Node.h>
#include <sg/nodes/Shape3D.h>
#include <sg/nodes/TGroup.h>
#include <sg/nodeComponents/app/SGImage.h>
#include <sg/nodeComponents/app/Texture.h>
#include <sg/nodeComponents/geom/TriangleArray.h>
#include <sg/nodes/SGObserver.h>

PrintVisitor::PrintVisitor() {
}

PrintVisitor::~PrintVisitor() {
  
//  std::cout << "PrintVisitor::~PrintVisitor" << std::endl;
}

void PrintVisitor::visit(SGObserver* observer) {

//  std::cout << "Visiting SGObserver" << std::endl;
  visit((Group*)observer);
//  Node* node = observer->getScene();
//  if (node != 0) {
//    node->accept(this);
//    node->releaseReference();
//  }
}


void PrintVisitor::visit(Node* node) {

  std::cout << prefix.substr(0, prefix.size()) << " +-" 
    << node->toString() << std::endl;
//  std::cout << prefix.substr(0, prefix.size()-1) << "+-" 
//    << node->toString() << std::endl;

}

void PrintVisitor::visit(Group* group) {
  visit((Node*)group);
  
  std::string oldPrefix = prefix;
  std::ostringstream help;
  if (group->getChildCount() > 1) {
    help << prefix << " |" << std::ends;
  } else {
    help << prefix << "  " << std::ends;
  }
  
  prefix = std::string(help.str());

  if (group->getChildCount() < 10) {
    NodeListIterator* i = group->getChilds();
    while (i->hasNext() == true) {
      Node* child = i->next();
      child->accept(this);
    }
    delete(i);
  }

  prefix = oldPrefix;

}

void PrintVisitor::visit(TGroup* g) {
  visit((Group*)g);
}

void PrintVisitor::visit(Leaf* l) {
  visit((Node*)l);
}

void PrintVisitor::visit(Shape3D* shape) {
  std::cout << prefix.substr(0, prefix.size()) << " +-" 
    << shape->toString() << " (" << shape->getGeometryCount() << ") " << std::endl;

  std::string oldPrefix = prefix;
  
  prefix += "  ";
  Visitor::visit(shape);
  prefix = oldPrefix;
}

void PrintVisitor::visit(Appearance* app) {
  std::cout << prefix << " +-" << app->toString() << std::endl;
/*
  Texture* texture = app->getTexture(0);
  if (texture != 0) {
    texture->accept(this);
    texture->releaseReference();
  }
  */
}

void PrintVisitor::visit(Geometry* geom) {
  std::cout << prefix << " +-" << geom->toString() << std::endl;
}

void PrintVisitor::visit(Texture* texture) {

  SGImage* sgImage = texture->getImage();
  std::cout << "PrintVisitor::visit(Texture*)" << std::endl;

  if (sgImage != 0) {

//    int width = sgImage->getImage()->getWidth();
//    int height = sgImage->getImage()->getHeight();
    std::cout << prefix << "Texture: ("
      << sgImage->getImage()->getWidth() << " x "
      << sgImage->getImage()->getHeight() << ")" << std::endl;
      
    sgImage->releaseReference();
  } else {
    std::cout << "image == 0" << std::endl;
  }

}

void PrintVisitor::visit(Behavior* b) {
  std::cout << prefix << " +-Behavior" << std::endl;
}
