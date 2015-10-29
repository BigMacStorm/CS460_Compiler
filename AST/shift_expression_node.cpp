#include "ast_node.h"
shift_expression_node::shift_expression_node(additive_expression_node* addExpr){
  init();
  this->addExpr = addExpr;
  mode = 0;
}
shift_expression_node::shift_expression_node(shift_expression_node* shiftExpr, OpType::Type op, additive_expression_node* addExpr){
  init();
  this->shiftExpr = shiftExpr;
  this->op = op;
  this->addExpr = addExpr;
  mode = 1;
}
void shift_expression_node::init(){
  this->shiftExpr = NULL;
  this->op = OpType::NONE;
  this->addExpr = NULL;
  mode = -1;
}
void shift_expression_node::print(){

}
void shift_expression_node::generateCode(){

}
