#include "ast_node.h"

unary_expression_node::unary_expression_node(postfix_expression_node* postExpr){
  this->postExpr = postExpr;
  this->mode = 0;
}
unary_expression_node::unary_expression_node(OpType::Type op, unary_expression_node* unaryExpr){
  this->op = op;
  this->unaryExpr = unaryExpr;
  this->mode = 0;
}
void unary_expression_node::print(){

}
void unary_expression_node::generateCode(){

}
