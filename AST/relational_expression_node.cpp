#include "ast_node.h"
relational_expression_node::relational_expression_node(shift_expression_node* shiftExpr): ast_node(){
  init();
  this->shiftExpr = shiftExpr;
  this->mode = 0;
}
relational_expression_node::relational_expression_node(
  relational_expression_node* relExpr, OpType::Type op,
  shift_expression_node* shiftExpr): ast_node(){
  init();
  this->relExpr = relExpr;
  this->op = op;
  this->shiftExpr = shiftExpr;
  this->mode = 1;
}
void relational_expression_node::init(){
  this->shiftExpr = NULL;
  this->relExpr = NULL;
  this->op = OpType::NONE;
  this->mode = -1;
}
void relational_expression_node::print(){
  visualizer.debug("relational_expression");
  switch(this->mode){
    case 0:
      if(this->shiftExpr!=NULL){
        this->shiftExpr->setPID(this->pid);
        this->shiftExpr->print();
      }
    break;
    case 1:
      if(this->op == OpType::L){
        visualizer.addNode(this->id,"<");
      }else if(this->op == OpType::G){
        visualizer.addNode(this->id,">");
      }else if(this->op == OpType::LE){
        visualizer.addNode(this->id,"<=");
      }else if(this->op == OpType::GE){
        visualizer.addNode(this->id,">=");
      }
      visualizer.addEdge(this->pid,this->id);

      if(this->relExpr!=NULL){
        this->relExpr->setPID(this->id);
        this->relExpr->print();
      }
      if(this->shiftExpr!=NULL){
        this->shiftExpr->setPID(this->id);
        this->shiftExpr->print();
      }
    break;
    default:
      std::cout << "ERROR: unknown relational expression type" << std::endl;
    break;
  }
}
Spec* relational_expression_node::getSpec(){
// fow now
  switch(this->mode){
    case 0:
      return this->shiftExpr->getSpec();
    case 1:
      return this->relExpr->getSpec();
  }
  return NULL;
}
void relational_expression_node::generateCode(){

}
