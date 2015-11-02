#include "ast_node.h"

enumerator_node::enumerator_node(){
}

enumerator_node::enumerator_node(identifier_node* id, constant_expression_node, expr){
    this -> id = id;
    this -> constExpr = expr;
}
void enumerator_node::print(){
  visualizer.addNode(this->id, "{}");
  visualizer.addEdge(this->pid, this->id);
  
  if(this->constExpr!=NULL){
    this->constExpr->setPID(this->id);
    this->constExpr->print();
  }

}

void enumerator_node::generateCode(){
}
