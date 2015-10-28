#include "ast_node.h"
additive_expression_node::additive_expression_node(multiplicative_expression_node* multiExpr){
  init();
  this->multiExpr = multiExpr;
  this->mode = 0;
}
additive_expression_node::additive_expression_node(additive_expression_node* addExpr, UnaryOpType::Type op, multiplicative_expression_node* multiExpr){
  init();
  this->addExpr = addExpr;
  this->op = op;
  this->multiExpr = multiExpr;
  this->mode = 1;
}
void additive_expression_node::init(){
  this->addExpr = NULL;
  this->multiExpr = NULL;
  this->op = UnaryOpType::NONE;
  this->mode = -1;
}
void additive_expression_node::print(){

}
void additive_expression_node::generateCode(){

}