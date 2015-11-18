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
specifier_qualifier_list_node::~specifier_qualifier_list_node(){
  if(this->spec!=NULL){
    delete this->spec;
  }
  if(this->sqlist!=NULL){
    delete this->sqlist;
  }
  if(this->qual!=NULL){
    delete this->qual;
  }
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
std::string specifier_qualifier_list_node::generateCode(){
<<<<<<< HEAD
  std::string ret;
=======
>>>>>>> be7319b8b25d0e06628e992a04129cf8143d6907
  if(this->spec!=NULL){
    this->spec->generateCode();
  }
  if(this->qual!=NULL){
    this->qual->generateCode();
  }
  if(this->sqlist!=NULL){
    this->sqlist->generateCode();
  }
<<<<<<< HEAD
  return ret;
}
=======
  return "";
}
>>>>>>> be7319b8b25d0e06628e992a04129cf8143d6907
