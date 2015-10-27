#include "ast_node.h"
argument_expression_list_node::argument_expression_list_node(){
}
argument_expression_list_node::argument_expression_list_node(assignment_expression_node* child){
  this->children.push_back(child);
}
void argument_expression_list_node::addAssignmentExpr(assignment_expression_node* child){
  this->children.push_back(child);
}
std::vector<assignment_expression_node*> argument_expression_list_node::getChildren() const{
  return this->children;
}
void argument_expression_list_node::print(){
  for(int child = 0; child < this->children.size(); child++){
    this->children[child]->print();
  }
}
void argument_expression_list_node::generateCode(){
}