#include "ast_node.h"
declaration_specifiers_node::declaration_specifiers_node(storage_class_specifier_node* storage,
                           declaration_specifiers_node* declSpec): ast_node(){
  this->storage = storage;
  this->declSpec = declSpec;
}
declaration_specifiers_node::declaration_specifiers_node(type_specifier_node* typeSpec,
                            declaration_specifiers_node* declSpec): ast_node(){
  this->typeSpec = typeSpec;
  this->declSpec = declSpec;
}
declaration_specifiers_node::declaration_specifiers_node(type_qualifier_node* qualifier,
                            declaration_specifiers_node* declSpec): ast_node(){
  this->qualifier = qualifier;
  this->declSpec = declSpec;
}
void declaration_specifiers_node::print(){
  if(this->storage != NULL){
    this->storage->setPID(this->pid);
    this->storage->print();
  }
  if(this->typeSpec != NULL){
    this->typeSpec->setPID(this->pid);
    this->typeSpec->print();
  }
  if(this->qualifier != NULL){
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