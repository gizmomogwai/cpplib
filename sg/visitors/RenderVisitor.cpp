#include <sg/visitors/RenderVisitor.h>

#include <sg/nodes/ImplicitSGNode.h>

void RenderVisitor::visit(ImplicitSGNode* node) {
  node->paint(this);
}