#include "ast_node.h"
logical_and_expression_node::logical_and_expression_node(
  inclusive_or_expression_node* iorExpr): ast_node(){
  init();
  this->iorExpr = iorExpr;
  this->mode = 0;
}
logical_and_expression_node::logical_and_expression_node(
  logical_and_expression_node* logAndExpr, OpType::Type op,
  inclusive_or_expression_node* iorExpr): ast_node(){
  init();
  this->logAndExpr = logAndExpr;
  this->op = op;
  this->iorExpr = iorExpr;
  this->mode = 1;
}
void logical_and_expression_node::init(){
  logAndExpr = NULL;
  iorExpr = NULL;
  op = OpType::NONE;
  mode = -1;
}
void logical_and_expression_node::print(){
  switch(this->mode){
    case 0:
      if(this->iorExpr!=NULL){
        this->iorExpr->setPID(this->pid);
        this->iorExpr->print();
      }
    break;
    case 1:
      visualizer.addNode(this->id,"&&");
      visualizer.addEdge(this->pid,this->id);

      if(this->logAndExpr!=NULL){
        this->logAndExpr->setPID(this->id);
        this->logAndExpr->print();
      }
      if(this->iorExpr!=NULL){
        this->iorExpr->setPID(this->id);
        this->iorExpr->print();
      }
    break;
    default:
      std::cout << "ERROR: unknown logical and expression type" << std::endl;
    break;
  }
}
void logical_and_expression_node::generateCode(){

}