#include "ast_node.h"
inclusive_or_expression_node::inclusive_or_expression_node(exclusive_or_expression_node* exorExpr){
  init();
  this->exorExpr = exorExpr;
  this->mode = 0;
}
inclusive_or_expression_node::inclusive_or_expression_node(inclusive_or_expression_node* iorExpr, OpType::Type op, exclusive_or_expression_node* exorExpr){
  init();
  this->iorExpr = iorExpr;
  this->op = op;
  this->exorExpr = exorExpr;
  this->mode = 1;
}
void inclusive_or_expression_node::init(){
  iorExpr = NULL;
  exorExpr = NULL;
  op = OpType::NONE;
  mode = -1;
}
void inclusive_or_expression_node::print(){

}
void inclusive_or_expression_node::generateCode(){

}