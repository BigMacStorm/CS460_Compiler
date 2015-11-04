#include "ast_node.h"
exclusive_or_expression_node::exclusive_or_expression_node(and_expression_node* andExpr): ast_node(){
  init();
  this->andExpr = andExpr;
  this->mode = 0;
}
exclusive_or_expression_node::exclusive_or_expression_node(
  exclusive_or_expression_node* exorExpr, OpType::Type op,
  and_expression_node* andExpr): ast_node(){
  init();
  this->andExpr = andExpr;
  this->op = op;
  this->exorExpr = exorExpr;
  this->mode = 1;
}
void exclusive_or_expression_node::init(){
  andExpr = NULL;
  exorExpr = NULL;
  op = OpType::NONE;
  mode = -1;
}
void exclusive_or_expression_node::print(){
  switch(this->mode){
    case 0:
      if(this->andExpr!=NULL){
        this->andExpr->setPID(this->pid);
        this->andExpr->print();
      }
    break;
    case 1:
      visualizer.addNode(this->id,"^");
      visualizer.addEdge(this->pid,this->id);

      if(this->exorExpr!=NULL){
        this->exorExpr->setPID(this->id);
        this->exorExpr->print();
      }
      if(this->andExpr!=NULL){
        this->andExpr->setPID(this->id);
        this->andExpr->print();
      }
    break;
    default:
      error("ERROR: unknown exclusive or expression type whiel print");
    break;
  }
}
Spec* exclusive_or_expression_node::getSpec(){
// fow now
  switch(this->mode){
    case 0:
      return this->andExpr->getSpec();
    case 1:
      return this->exorExpr->getSpec();
  }
  return NULL;
}
void exclusive_or_expression_node::generateCode(){

}