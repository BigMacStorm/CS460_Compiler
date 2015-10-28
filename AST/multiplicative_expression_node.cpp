#include "ast_node.h"
multiplicative_expression_node::multiplicative_expression_node(cast_expression_node* castExpr){
  init();
  this->castExpr = castExpr;
  this->mode = 0;
}
multiplicative_expression_node::multiplicative_expression_node(multiplicative_expression_node* multiExpr, OpType::Type op, cast_expression_node* castExpr){
  init();
  this->multiExpr = multiExpr;
  this->op = op;
  this->castExpr = castExpr;
  this->mode = 1;
}
void multiplicative_expression_node::init(){
  this->multiExpr = NULL;
  this->op = OpType::NONE;
  this->castExpr = NULL;
  this->mode = -1;
}
void multiplicative_expression_node::print(){

}
void multiplicative_expression_node::generateCode(){

}
