#include "ast_node.h"
multiplicative_expression_node::multiplicative_expression_node(
  cast_expression_node* castExpr): ast_node(){
  init();
  this->castExpr = castExpr;
  this->mode = 0;
}
multiplicative_expression_node::multiplicative_expression_node(
  multiplicative_expression_node* multiExpr, OpType::Type op,
  cast_expression_node* castExpr): ast_node(){
  init();
  this->multiExpr = multiExpr;
  this->op = op;
  this->castExpr = castExpr;
  this->mode = 1;
}
void multiplicative_expression_node::init(){
  this->multiExpr = NULL;
  this->op = OpType::NONE;
  this->castExpr = NULL;
  this->mode = -1;
}
void multiplicative_expression_node::print(){
  switch(this->mode){
    case 0:
      if(this->castExpr!=NULL){
        this->castExpr->setPID(this->pid);
        this->castExpr->print();
      }
    break;
    case 1:
      if(this->op == OpType::ASTERISK){
        visualizer.addNode(this->id,"*");
      }else if(this->op == OpType::DIV){
        visualizer.addNode(this->id,"/");
      }else{
        visualizer.addNode(this->id,"%%");
      }
      visualizer.addEdge(this->pid,this->id);

      if(this->multiExpr!=NULL){
        this->multiExpr->setPID(this->id);
        this->multiExpr->print();
      }
      if(this->castExpr!=NULL){
        this->castExpr->setPID(this->id);
        this->castExpr->print();
      }
    break;
    default:
      std::cout << "ERROR: unknown multiplicative expression type" << std::endl;
    break;
  }
}
void multiplicative_expression_node::generateCode(){

}
