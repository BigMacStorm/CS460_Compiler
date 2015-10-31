#include "ast_node.h"
additive_expression_node::additive_expression_node(multiplicative_expression_node* multiExpr): ast_node(){
  init();
  this->multiExpr = multiExpr;
  this->mode = 0;
}
additive_expression_node::additive_expression_node(additive_expression_node* addExpr, OpType::Type op, multiplicative_expression_node* multiExpr): ast_node(){
  init();
  this->addExpr = addExpr;
  this->op = op;
  this->multiExpr = multiExpr;
  this->mode = 1;
}
void additive_expression_node::init(){
  this->addExpr = NULL;
  this->multiExpr = NULL;
  this->op = OpType::NONE;
  this->mode = -1;
}
void additive_expression_node::print(){
    switch(this->mode){
      case 0:
        if(this->multiExpr!=NULL){
          this->multiExpr->setPID(this->pid);
          this->multiExpr->print();
        }
      break;
      case 1:
        if(this->op == OpType::PLUS){
          visualizer.addNode(this->id,"+");
        }else{
          visualizer.addNode(this->id,"-");
        }
        visualizer.addEdge(this->pid,this->id);

        if(this->addExpr!=NULL){
          this->addExpr->setPID(this->id);
          this->addExpr->print();
        }
        if(this->multiExpr!=NULL){
          this->multiExpr->setPID(this->id);
          this->multiExpr->print();
        }
      break;
      default:
        std::cout << "ERROR: unknown additive expression type" << std::endl;
      break;
    }
  }
void additive_expression_node::generateCode(){

}
