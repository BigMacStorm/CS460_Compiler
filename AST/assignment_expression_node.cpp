#include "ast_node.h"
assignment_expression_node::assignment_expression_node(
  conditional_expression_node* cond_expr): ast_node(){
  init();
  this->cond_expr = cond_expr;
  this->mode = 0;
}
assignment_expression_node::assignment_expression_node(
  unary_expression_node* unary_expr, assignment_operator_node* assign_op,
  assignment_expression_node* assign_expr): ast_node(){
  init();
  this->unary_expr = unary_expr;
  this->assign_op = assign_op;
  this->assign_expr = assign_expr;
  this->mode = 1;
}
void assignment_expression_node::init(){
  this->cond_expr = NULL;
  this->unary_expr = NULL;
  this->assign_op = NULL;
  this->assign_expr = NULL;
  this->mode = -1;
}
void assignment_expression_node::print(){
  switch(this->mode){
    case 0:
      if(this->cond_expr!=NULL){
        this->cond_expr->setPID(this->pid);
        this->cond_expr->print();
      }
    break;
    case 1:
      if(this->assign_op!=NULL){
        this->assign_op->setPID(this->pid);
        this->assign_op->print();
      }
      if(this->unary_expr!=NULL){
        this->unary_expr->setPID(this->assign_op->getID());
        this->unary_expr->print();
      }
      if(this->assign_expr!=NULL){
        this->assign_expr->setPID(this->assign_op->getID());
        this->assign_expr->print();
      }
    break;
    default:
      std::cout << "ERROR: unknown assignment expression type" << std::endl;
    break;
  }
}
void assignment_expression_node::generateCode(){

}