#include "ast_node.h"
unary_expression_node::unary_expression_node(postfix_expression_node* postExpr): ast_node(){
  init();
  this->postExpr = postExpr;
  this->mode = 0;
}
unary_expression_node::unary_expression_node(OpType::Type op, unary_expression_node* unaryExpr): ast_node(){
  init();
  this->op = op;
  this->unaryExpr = unaryExpr;
  this->mode = 1;
}
unary_expression_node::unary_expression_node(unary_operator_node* unaryOp, cast_expression_node* castExpr): ast_node(){
  init();
  this->unaryOp = unaryOp;
  this->castExpr = castExpr;
  this->mode = 2;
}
unary_expression_node::~unary_expression_node(){
  if(this->postExpr!=NULL){
    delete this->postExpr;
  }
  if(this->unaryExpr!=NULL){
    delete this->unaryExpr;
  }
  if(this->castExpr!=NULL){
    delete this->castExpr;
  }
}
void unary_expression_node::init(){
  this->postExpr = NULL;
  this->unaryOp = NULL;
  this->unaryExpr = NULL;
  this->castExpr = NULL;
  this->mode = -1;
}
std::string unary_expression_node::getOpStr() const{
  if(this->op == OpType::INC){
    return "++";
  }
  else if(this->op == OpType::DEC){
    return "--";
  }
  else if(this->op == OpType::SIZEOF){
    return "sizeof";
  }
  return "";
}
void unary_expression_node::print(){
  visualizer.debug("unary_expression");
  switch(this->mode){
    case 0:
      if(this->postExpr != NULL){
        this->postExpr->setPID(this->pid);
        this->postExpr->print();
      }
    break;
    case 1:
     visualizer.addNode(this->id,getOpStr());
     visualizer.addEdge(this->pid,this->id);
     if(this->unaryExpr != NULL){
       this->unaryExpr->setPID(this->id);
       this->unaryExpr->print();
     }
    break;
    case 2:
     if(this->unaryOp != NULL){
       this->unaryOp->setPID(this->pid);
       this->unaryOp->print();
     }
     if(this->castExpr != NULL){
       this->castExpr->setPID(this->unaryOp->getID());
       this->castExpr->print();
     }
    break;
    default:
      std::cout << "ERROR: unknown unary expression type" << std::endl;
    break;
  }
}
Spec* unary_expression_node::getSpec(){
  switch(this->mode){
    case 0:
      if(this->postExpr != NULL){
        return this->postExpr->getSpec();
      }
      return NULL;
    case 1:
     if(this->unaryExpr != NULL){
       return this->unaryExpr->getSpec();
     }
     return NULL;
    case 2:
     if(this->castExpr != NULL){
       return this->castExpr->getSpec();
     }
     return NULL;
    default:
      return NULL;
  }
}

void unary_expression_node::generateCode(){

}
