#include "ast_node.h"
expression_node::expression_node(){
}
expression_node::expression_node(assignment_expression_node* child){
  this->children.push_back(child);
}
void expression_node::addAssignmentExpr(assignment_expression_node* child){
  this->children.push_back(child);
}
std::vector<assignment_expression_node*> expression_node::getChildren() const{
  return this->children;
}
void expression_node::print(){
  for(int child = 0; child < this->children.size(); child++){
    this->children[child]->print();
  }
}
void expression_node::generateCode(){
}