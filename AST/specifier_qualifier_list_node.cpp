#include "ast_node.h"
specifier_qualifier_list_node::specifier_qualifier_list_node(type_specifier_node* spec,
  specifier_qualifier_list_node* sqlist): ast_node(){
  init();
  this->spec = spec;
  this->sqlist = sqlist;
}
specifier_qualifier_list_node::specifier_qualifier_list_node(type_qualifier_node* qual,
  specifier_qualifier_list_node* sqlist): ast_node(){
  init();
  this->qual = qual;
  this->sqlist = sqlist;
}
void specifier_qualifier_list_node::init(){
  this->spec = NULL;
  this->qual = NULL;
  this->sqlist = NULL;
}
Spec* specifier_qualifier_list_node::getSpec(){
 // not yet
 return NULL;
}
void specifier_qualifier_list_node::print(){
  visualizer.debug("specifier_qualifier_list");
  if(this->spec!=NULL){
    this->spec->setPID(this->pid);
    this->spec->print();
  }
  if(this->qual!=NULL){
    this->qual->setPID(this->pid);
    this->qual->print();
  }
  if(this->sqlist!=NULL){
    this->sqlist->setPID(this->pid);
    this->sqlist->print();
  }
}
void specifier_qualifier_list_node::generateCode(){
}