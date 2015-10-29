#include "ast_node.h"
logical_or_expression_node::logical_or_expression_node(logical_and_expression_node* logAndExpr){
  init();
  this->logAndExpr = logAndExpr;
  this->mode = 0;
}
logical_or_expression_node::logical_or_expression_node(logical_or_expression_node* logOrExpr, OpType::Type op, logical_and_expression_node* logAndExpr){
  init();
  this->logOrExpr = logOrExpr;
  this->op = op;
  this->logAndExpr = logAndExpr;
  this->mode = 1;
}
void logical_or_expression_node::init(){
  logOrExpr = NULL;
  logAndExpr = NULL;
  op = OpType::NONE;
  mode = -1;
}
void logical_or_expression_node::print(){

}
void logical_or_expression_node::generateCode(){

}