#include "ast_node.h"
  cast_expression_node::cast_expression_node(
    unary_expression_node* unaryExpr): ast_node(){
    this->unaryExpr = unaryExpr;
  }
  void cast_expression_node::print(){
    if(this->unaryExpr!=NULL){
      this->unaryExpr->setPID(this->pid);
      this->unaryExpr->print();
    }
  }
  void cast_expression_node::generateCode(){

  }