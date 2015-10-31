#include "ast_node.h"

unary_expression_node::unary_expression_node(postfix_expression_node* postExpr): ast_node(){
  this->postExpr = postExpr;
  this->mode = 0;
}
unary_expression_node::unary_expression_node(OpType::Type op, unary_expression_node* unaryExpr): ast_node(){
  this->op = op;
  this->unaryExpr = unaryExpr;
  this->mode = 1;
}
std::string unary_expression_node::getOpStr() const{
  if(this->op == OpType::INC){
    return "++";
  }
  else if(this->op == OpType::INC){
    return "--";
  }
  else if(this->op == OpType::INC){
    return "sizeof";
  }
  return "";
}
void unary_expression_node::print(){
  int op_node_id;
  switch(this->mode){
    case 0:
      if(this->postExpr != NULL){
        this->postExpr->setPID(this->pid);
        this->postExpr->print();
      }
    break;
    case 1:
     visualizer.addNode(this->id,"unary_expression");  // for now
     visualizer.addEdge(this->pid,this->id);
     op_node_id = ast_node::getUID();
     visualizer.addNode(op_node_id,getOpStr());
     visualizer.addEdge(this->pid,this->id);

     if(this->unaryExpr != NULL){
       this->unaryExpr->setPID(this->id);
       this->unaryExpr->print();
     }
    break;
    default:
      std::cout << "ERROR: unknown unary expression type" << std::endl;
    break;
  }
}
void unary_expression_node::generateCode(){

}
