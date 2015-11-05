#include "ast_node.h"
compound_statement_node::compound_statement_node(
  declaration_list_node* declList, statement_list_node* stateList): ast_node(){
  init();
  this->declList = declList;
  this->stateList = stateList;
}
void compound_statement_node::init(){
  this->declList = NULL;
  this->stateList = NULL;
}
void compound_statement_node::print(){
  visualizer.debug("compound_statement");
  visualizer.addNode(this->id, "{}");
  visualizer.addEdge(this->pid, this->id);
  if(this->declList!=NULL){
    this->declList->setPID(this->id);
    this->declList->print();
  }
  if(this->stateList!=NULL){
    this->stateList->setPID(this->id);
    this->stateList->print();
  }
}
void compound_statement_node::generateCode(){
}