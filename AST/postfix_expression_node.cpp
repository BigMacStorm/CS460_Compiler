#include "ast_node.h"
postfix_expression_node::postfix_expression_node(primary_expression_node* primayExpr){
  init();
  this->primayExpr = primayExpr;
  this->mode = 0;
}
postfix_expression_node::postfix_expression_node(postfix_expression_node* postExpr, expression_node* expr){
  init();
  this->postExpr = postExpr;
  this->expr = expr;
  this->mode = 1;
}
postfix_expression_node::postfix_expression_node(postfix_expression_node* postExpr){
  init();
  this->postExpr = postExpr;
  this->mode = 2;
}
postfix_expression_node::postfix_expression_node(postfix_expression_node* postExpr, argument_expression_list_node* argExpr){
  init();
  this->postExpr = postExpr;
  this->argExpr = argExpr;
  this->mode = 3;
}
postfix_expression_node::postfix_expression_node(postfix_expression_node* postExpr, PostOpType::Type op, std::string identifier){
  init();
  this->postExpr = postExpr;
  this->op = op;
  this->identifier = identifier;
  this->mode = 4;
}
postfix_expression_node::postfix_expression_node(postfix_expression_node* postExpr, PostOpType::Type op){
  init();
  this->postExpr = postExpr;
  this->op = op;
  this->mode = 5;
}
void postfix_expression_node::init(){
  this->primayExpr = NULL;
  this->postExpr = NULL;
  this->expr = NULL;
  this->argExpr = NULL;
  this->op = PostOpType::NONE;
  this->identifier ="";
}
void postfix_expression_node::print(){

}
void postfix_expression_node::generateCode(){

}