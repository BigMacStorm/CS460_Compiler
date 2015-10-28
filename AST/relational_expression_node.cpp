#include "ast_node.h"
  relational_expression_node::relational_expression_node(shift_expression_node* shiftExpr){
    init();
    this->shiftExpr = shiftExpr;
  }
  relational_expression_node::relational_expression_node(relational_expression_node* relExpr, OpType::Unary op, shift_expression_node* shiftExpr){
    init();
    this->relExpr = relExpr;
    this->op = op;
    this->shiftExpr = shiftExpr;
  }
  void relational_expression_node::init(){
    this->shiftExpr = NULL;
    this->relExpr = NULL;
    this->op = OpType::NONE;
    this->mode = -1;
  }
  void relational_expression_node::print(){

  }
  void relational_expression_node::generateCode(){

  }