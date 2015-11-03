#include "ast_node.h"
expression_statement_node::expression_statement_node(): ast_node(){
  init();
}
expression_statement_node::expression_statement_node(expression_node* expr): ast_node(){
  init();
  this->expr = expr;
}
void expression_statement_node::init(){
  this->expr = NULL;
}
void expression_statement_node::print(){
  if(this->expr != NULL){
    this->expr->setPID(this->pid);
    this->expr->print();
  }
}
void expression_statement_node::generateCode(){
}