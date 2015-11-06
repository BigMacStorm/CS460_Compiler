#include "ast_node.h"
declaration_specifiers_node::declaration_specifiers_node(storage_class_specifier_node* storage,
                           declaration_specifiers_node* declSpec): ast_node(){
  init();
  this->storage = storage;
  this->declSpec = declSpec;
}
declaration_specifiers_node::declaration_specifiers_node(type_specifier_node* typeSpec,
                            declaration_specifiers_node* declSpec): ast_node(){
  init();
  this->typeSpec = typeSpec;
  this->declSpec = declSpec;
}
declaration_specifiers_node::declaration_specifiers_node(type_qualifier_node* qualifier,
                            declaration_specifiers_node* declSpec): ast_node(){
  init();
  this->qualifier = qualifier;
  this->declSpec = declSpec;
}
declaration_specifiers_node::~declaration_specifiers_node(){
  if(this->storage!=NULL){
    delete this->storage;
  }
  if(this->typeSpec!=NULL){
    delete this->typeSpec;
  }
  if(this->qualifier!=NULL){
    delete this->qualifier;
  }
  if(this->declSpec!=NULL){
    delete this->declSpec;
  }
}
void declaration_specifiers_node::init(){
  this->storage = NULL;
  this->typeSpec = NULL;
  this->qualifier = NULL;
  this->declSpec = NULL;
}
void declaration_specifiers_node::print(){
  visualizer.debug("declaration_specifiers");
  //visualizer.addNode(this->id, "declaration_specifiers");
  //visualizer.addEdge(this->pid, this->id);
  if(this->storage != NULL){
    this->storage->setPID(this->pid);
    this->storage->print();
  }
  else if(this->typeSpec != NULL){
    this->typeSpec->setPID(this->pid);
    this->typeSpec->print();
  }
  else if(this->qualifier != NULL){
    this->qualifier->setPID(this->pid);
    this->qualifier->print();
  }
  if(this->declSpec != NULL){
    this->declSpec->setPID(this->pid);
    this->declSpec->print();
  }
}
void declaration_specifiers_node::generateCode(){

}