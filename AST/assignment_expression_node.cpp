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
      error("[A] ERROR: unknown assignment expression type while print");
    break;
  }
}
Spec* assignment_expression_node::getSpec(){
SpecName::BaseType left = SpecName::NoType;
SpecName::BaseType right = SpecName::NoType;
Spec *leftSpec, *rightSpec;

// fow now
  switch(this->mode){
    case 0:
      return this->cond_expr->getSpec();

    case 1:
      if(this->unary_expr!=NULL && this->assign_expr != NULL){
        leftSpec = this->unary_expr->getSpec();
        rightSpec = this->assign_expr->getSpec();

        if(leftSpec!= NULL && rightSpec!= NULL){
          left = leftSpec->getBaseType();
          right = rightSpec->getBaseType();

          // std::cout << left << " " << right << std::endl;

          // check if assignable
          if(leftSpec->isValue()){
            error("[A] ERROR: expression is not assignable");
          }

          // type matched
          if(left == right){
            return leftSpec;
          }
          // implicit conversions
          else if(left == SpecName::Float && right == SpecName::Int){ // int to float
            warning("[A] WARNING: implicit conversion from 'int' to 'float'");
            return new TypeBasic(SpecName::Float);
          }
          else if(left == SpecName::Int && right == SpecName::Float){ // float to int
            warning("[A] WARNING: implicit conversion from 'float' to 'int'");
            return new TypeBasic(SpecName::Int);
          }
        }
      }
    } // end switch
  return NULL;
}
void assignment_expression_node::generateCode(){

}