#include "ast_node.h"
/*
assignment_expression_node::assignment_expression_node(conditional_expression_node* cond_expr){
  init();
  this->isConditionalExpr = true;
  this->cond_expr = cond_expr;
  this->mode = 0;
}
*/
assignment_expression_node::assignment_expression_node(unary_expression_node* unary_expr,
  assignment_operator_node* assign_op, assignment_expression_node* assign_expr){
  init();
  this->isConditionalExpr = false;
  this->unary_expr = unary_expr;
  this->assign_op = assign_op;
  this->assign_expr = assign_expr;
  this->mode = 1;
}
void assignment_expression_node::init(){
  this->isConditionalExpr = false;
  this->cond_expr = NULL;
  this->unary_expr = NULL;
  this->assign_op = NULL;
  this->assign_expr = NULL;
  this->mode = -1;
}
void assignment_expression_node::print(){
  if(!this->isConditionalExpr){
    if(this->unary_expr != NULL){
      this->unary_expr->print();
      std::cout<< " ";
    }
    if(this->unary_expr != NULL){
      this->assign_op->print();
      std::cout<< " ";
    }
    if(this->unary_expr != NULL){
      this->assign_expr->print();
      std::cout<< " ";
    }
  }
}
void assignment_expression_node::generateCode(){

}