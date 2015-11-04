#include "ast_node.h"
logical_or_expression_node::logical_or_expression_node(
  logical_and_expression_node* logAndExpr): ast_node(){
  init();
  this->logAndExpr = logAndExpr;
  this->mode = 0;
}
logical_or_expression_node::logical_or_expression_node(
  logical_or_expression_node* logOrExpr, OpType::Type op,
  logical_and_expression_node* logAndExpr): ast_node(){
  init();
  this->logOrExpr = logOrExpr;
  this->op = op;
  this->logAndExpr = logAndExpr;
  this->mode = 1;
}
void logical_or_expression_node::init(){
  logOrExpr = NULL;
  logAndExpr = NULL;
  op = OpType::NONE;
  mode = -1;
}
void logical_or_expression_node::print(){
  switch(this->mode){
    case 0:
      if(this->logAndExpr!=NULL){
        this->logAndExpr->setPID(this->pid);
        this->logAndExpr->print();
      }
    break;
    case 1:
      visualizer.addNode(this->id,"||");
      visualizer.addEdge(this->pid,this->id);

      if(this->logOrExpr!=NULL){
        this->logOrExpr->setPID(this->id);
        this->logOrExpr->print();
      }
      if(this->logAndExpr!=NULL){
        this->logAndExpr->setPID(this->id);
        this->logAndExpr->print();
      }
    break;
    default:
      std::cout << "ERROR: unknown logical or expression type" << std::endl;
    break;
  }
}
Spec* logical_or_expression_node::getSpec(){
// fow now
  switch(this->mode){
    case 0:
      return this->logAndExpr->getSpec();
    break;
    case 1:
      return this->logOrExpr->getSpec();
    break;
  }
  return NULL;
}
void logical_or_expression_node::generateCode(){

}