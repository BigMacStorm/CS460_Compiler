#include "ast_node.h"
equality_expression_node::equality_expression_node(relational_expression_node* relExpr){
  init();
  this->relExpr = relExpr;
  this->mode = 0;
}
equality_expression_node::equality_expression_node(equality_expression_node* equalExpr, OpType::Type op, relational_expression_node* relExpr){
  init();
  this->equalExpr = equalExpr;
  this->op = op;
  this->relExpr = relExpr;
  this->mode = 1;
}
void equality_expression_node::init(){
  equalExpr = NULL;
  relExpr = NULL;
  op = OpType::NONE;
  mode = -1;
}
void equality_expression_node::print(){

}
void equality_expression_node::generateCode(){

}