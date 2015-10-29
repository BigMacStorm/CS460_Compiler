#include "ast_node.h"
constant_expression_node::constant_expression_node(conditional_expression_node* condExpr){
  init();
  this->condExpr = condExpr;
}
void constant_expression_node::init(){
  this->condExpr = NULL;
}
void constant_expression_node::print(){

}
void constant_expression_node::generateCode(){

}