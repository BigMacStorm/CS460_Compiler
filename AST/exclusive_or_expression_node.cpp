#include "ast_node.h"
exclusive_or_expression_node::exclusive_or_expression_node(and_expression_node* andExpr){
  init();
  this->andExpr = andExpr;
  this->mode = 0;
}
exclusive_or_expression_node::exclusive_or_expression_node(exclusive_or_expression_node* exorExpr, OpType::Type op, and_expression_node* andExpr){
  init();
  this->andExpr = andExpr;
  this->op = op;
  this->exorExpr = exorExpr;
  this->mode = 1;
}
void exclusive_or_expression_node::init(){
  andExpr = NULL;
  exorExpr = NULL;
  op = OpType::NONE;
  mode = -1;
}
void exclusive_or_expression_node::print(){

}
void exclusive_or_expression_node::generateCode(){

}