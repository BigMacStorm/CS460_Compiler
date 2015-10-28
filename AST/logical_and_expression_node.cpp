#include "ast_node.h"
logical_and_expression_node::logical_and_expression_node(inclusive_or_expression_node* iorExpr){
  init();
  this->iorExpr = iorExpr;
  this->mode = 0;
}
logical_and_expression_node::logical_and_expression_node(logical_and_expression_node* logAndExpr, OpType::Type op, inclusive_or_expression_node* iorExpr){
  init();
  this->logAndExpr = logAndExpr;
  this->op = op;
  this->iorExpr = iorExpr;
  this->mode = 1;
}
void logical_and_expression_node::init(){
  logAndExpr = NULL;
  iorExpr = NULL;
  op = OpType::NONE;
  mode = -1;
}
void logical_and_expression_node::print(){

}
void logical_and_expression_node::generateCode(){

}