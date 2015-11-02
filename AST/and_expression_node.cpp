#include "ast_node.h"
and_expression_node::and_expression_node(
  equality_expression_node* equalExpr): ast_node(){
  init();
  this->equalExpr = equalExpr;
  this->mode = 0;
}
and_expression_node::and_expression_node(and_expression_node* andExpr,
  OpType::Type op, equality_expression_node* equalExpr): ast_node(){
  init();
  this->andExpr = andExpr;
  this->op = op;
  this->equalExpr = equalExpr;
  this->mode = 1;
}
void and_expression_node::init(){
  andExpr = NULL;
  equalExpr = NULL;
  op = OpType::NONE;
  mode = -1;
}
void and_expression_node::print(){
  switch(this->mode){
    case 0:
      if(this->equalExpr!=NULL){
        this->equalExpr->setPID(this->pid);
        this->equalExpr->print();
      }
    break;
    case 1:
      visualizer.addNode(this->id,"&");
      visualizer.addEdge(this->pid,this->id);

      if(this->andExpr!=NULL){
        this->andExpr->setPID(this->id);
        this->andExpr->print();
      }
      if(this->equalExpr!=NULL){
        this->equalExpr->setPID(this->id);
        this->equalExpr->print();
      }
    break;
    default:
      std::cout << "ERROR: unknown and expression type" << std::endl;
    break;
  }
}
void and_expression_node::generateCode(){

}