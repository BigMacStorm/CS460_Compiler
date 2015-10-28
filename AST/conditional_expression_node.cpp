#include "ast_node.h"
conditional_expression_node::conditional_expression_node(logical_or_expression_node* logOrExpr){
  init();
  this->logOrExpr = logOrExpr;
  this->mode = 0;
}
conditional_expression_node::conditional_expression_node(logical_or_expression_node* logOrExpr, expression_node* expr, conditional_expression_node* condExpr){
  init();
  this->condExpr = condExpr;
  this->expr = expr;
  this->logOrExpr = logOrExpr;
  this->mode = 1;
}
void conditional_expression_node::init(){
  this->condExpr = NULL;
  this->logOrExpr = NULL;
  this->expr = NULL;
  this->mode = -1;
}
void conditional_expression_node::print(){

}
void conditional_expression_node::generateCode(){

}