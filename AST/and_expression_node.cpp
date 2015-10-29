#include "ast_node.h"
and_expression_node::and_expression_node(equality_expression_node* equalExpr){
  init();
  this->equalExpr = equalExpr;
  this->mode = 0;
}
and_expression_node::and_expression_node(and_expression_node* andExpr, OpType::Type op, equality_expression_node* equalExpr){
  init();
  this->andExpr = andExpr;
  this->op = op;
  this->equalExpr = equalExpr;
  this->mode = 1;
}
void and_expression_node::init(){
  andExpr = NULL;
  equalExpr = NULL;
  op = OpType::NONE;
  mode = -1;
}
void and_expression_node::print(){

}
void and_expression_node::generateCode(){

}