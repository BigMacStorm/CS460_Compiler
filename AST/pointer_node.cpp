#include "ast_node.h"
pointer_node::pointer_node(type_qualifier_list_node* typeQualList, pointer_node* pointer): ast_node(){
  this->typeQualList = typeQualList;
  this->pointer = pointer;
}
void pointer_node::print(){
  visualizer.addNode(this->id,"*");
  visualizer.addEdge(this->pid,this->id);
  if(this->typeQualList != NULL){
    this->typeQualList->setPID(this->id);
    this->typeQualList->print();
  }
  if(this->pointer != NULL){
    this->pointer->setPID(this->id);
    this->pointer->print();
  }
}
void pointer_node::generateCode(){
}