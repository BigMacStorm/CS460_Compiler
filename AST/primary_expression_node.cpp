#include "ast_node.h"
primary_expression_node::primary_expression_node(identifier_node* identifier){
  init();
  this->mode = 0;
  this->identifier = identifier;
}
primary_expression_node::primary_expression_node(constant_node* constant){
  init();
  this->mode = 1;
  this->constant = constant;
}
primary_expression_node::primary_expression_node(string_node* string){
  init();
  this->mode = 2;
  this->string = string;
}
primary_expression_node::primary_expression_node(expression_node* expr){
  init();
  this->mode = 3;
  this->expr = expr;
}
void primary_expression_node::init(){
  this->identifier = NULL;
  this->constant = NULL;
  this->string = NULL;
  this->expr = NULL;
  int mode = -1;
}
void primary_expression_node::print(){

}
void primary_expression_node::generateCode(){

}