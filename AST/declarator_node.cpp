#include "ast_node.h"
declarator_node::declarator_node(pointer_node* pointer, direct_declarator_node* directDecl): ast_node(){
  this->pointer = pointer;
  this->directDecl = directDecl;

}
void declarator_node::print(){
  if(this->pointer != NULL){
    this->pointer->setPID(this->pid);
    this->pointer->print();
  }
  if(this->directDecl!=NULL){
    this->directDecl->setPID(this->pid);
    this->directDecl->print();
  }
}
void declarator_node::generateCode(){
}