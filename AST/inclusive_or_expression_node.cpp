#include "ast_node.h"
inclusive_or_expression_node::inclusive_or_expression_node(
  exclusive_or_expression_node* exorExpr): ast_node(){
  init();
  this->exorExpr = exorExpr;
  this->mode = 0;
}
inclusive_or_expression_node::inclusive_or_expression_node(
  inclusive_or_expression_node* iorExpr, OpType::Type op,
  exclusive_or_expression_node* exorExpr): ast_node(){
  init();
  this->iorExpr = iorExpr;
  this->op = op;
  this->exorExpr = exorExpr;
  this->mode = 1;
}
void inclusive_or_expression_node::init(){
  iorExpr = NULL;
  exorExpr = NULL;
  op = OpType::NONE;
  mode = -1;
}
void inclusive_or_expression_node::print(){
  switch(this->mode){
    case 0:
      if(this->exorExpr!=NULL){
        this->exorExpr->setPID(this->pid);
        this->exorExpr->print();
      }
    break;
    case 1:
      visualizer.addNode(this->id,"|");
      visualizer.addEdge(this->pid,this->id);

      if(this->iorExpr!=NULL){
        this->iorExpr->setPID(this->id);
        this->iorExpr->print();
      }
      if(this->exorExpr!=NULL){
        this->exorExpr->setPID(this->id);
        this->exorExpr->print();
      }
    break;
    default:
      std::cout << "ERROR: unknown inclusive or expression type" << std::endl;
    break;
  }
}
void inclusive_or_expression_node::generateCode(){

}