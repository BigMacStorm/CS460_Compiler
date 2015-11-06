#include "ast_node.h"
expression_statement_node::expression_statement_node(): ast_node(){
  init();
}
expression_statement_node::expression_statement_node(expression_node* expr): ast_node(){
  init();
  this->expr = expr;
}
expression_statement_node::~expression_statement_node(){
  if(this->expr!=NULL){
    delete this->expr;
  }
}
void expression_statement_node::init(){
  this->expr = NULL;
}
void expression_statement_node::print(){
  visualizer.debug("expression_statement");
  if(this->expr != NULL){
    this->expr->setPID(this->pid);
    this->expr->print();
  }
}
void expression_statement_node::generateCode(){
}