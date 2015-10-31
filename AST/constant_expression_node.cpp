#include "ast_node.h"
constant_expression_node::constant_expression_node(conditional_expression_node* condExpr): ast_node(){
  init();
  this->condExpr = condExpr;
}
void constant_expression_node::init(){
  this->condExpr = NULL;
}
void constant_expression_node::print(){
  if(this->condExpr!=NULL){
    this->condExpr->setPID(this->pid);
    this->condExpr->print();
  }
}
void constant_expression_node::generateCode(){

}