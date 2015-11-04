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
  Spec* cast_expression_node::getSpec(){
    if(this->unaryExpr!=NULL){
      return this->unaryExpr->getSpec();
    }
    return NULL;
  }
  void cast_expression_node::generateCode(){

  }