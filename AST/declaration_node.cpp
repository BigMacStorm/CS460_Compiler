#include "ast_node.h"
declaration_node::declaration_node(): ast_node(){
}
declaration_node::declaration_node(declaration_specifiers_node* specifier,
  init_declarator_list_node* decList): ast_node(){
    this->specifier = specifier;
    this->decList = decList;
}
declaration_node::~declaration_node(){
  if(this->decList!=NULL){
    delete this->decList;
  }
  if(this->specifier!=NULL){
    delete this->specifier;
  }
}
void declaration_node::print(){
  visualizer.debug("declaration");
  visualizer.addNode(this->id, "declaration");
  visualizer.addEdge(this->pid, this->id);

  if(this->specifier!=NULL){
    this->spec_id = ast_node::getUID();
    visualizer.addNode(this->spec_id, "specifier");
    visualizer.addEdge(this->id, this->spec_id);
    this->specifier->setPID(this->spec_id);
    this->specifier->print();
  }
  if(this->decList!=NULL){
    this->decList->setPID(this->id);
    this->decList->print();
  }
}
void declaration_node::generateCode(){
}