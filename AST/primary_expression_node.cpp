#include "ast_node.h"
primary_expression_node::primary_expression_node(identifier_node* identifier): ast_node(){
  init();
  this->mode = 0;
  this->identifier = identifier;
}
primary_expression_node::primary_expression_node(constant_node* constant): ast_node(){
  init();
  this->mode = 1;
  this->constant = constant;
}
primary_expression_node::primary_expression_node(string_node* string): ast_node(){
  init();
  this->mode = 2;
  this->string = string;
}
primary_expression_node::primary_expression_node(expression_node* expr): ast_node(){
  init();
  this->mode = 3;
  this->expr = expr;
}
void primary_expression_node::init(){
  this->identifier = NULL;
  this->constant = NULL;
  this->string = NULL;
  this->expr = NULL;
  this->mode = -1;
}
void primary_expression_node::print(){
  switch(this->mode){
    case 0:
      if(this->identifier != NULL){
        this->identifier->setPID(this->pid);
        this->identifier->print();
      }
    break;
    case 1:
      if(this->constant != NULL){
        this->constant->setPID(this->pid);
        this->constant->print();
      }
    break;
    case 2:
      if(this->string != NULL){
        this->string->setPID(this->pid);
        this->string->print();
      }
    break;
    case 3:
      if(this->expr != NULL){
        this->expr->setPID(this->pid);
        this->expr->print();
      }
    break;
    default:
      std::cout << "ERROR: unknown primary expression type";
    break;
  }
}
void primary_expression_node::generateCode(){

}