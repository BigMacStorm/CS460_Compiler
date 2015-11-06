#include "ast_node.h"
declarator_node::declarator_node(pointer_node* pointer, direct_declarator_node* directDecl): ast_node(){
  this->pointer = pointer;
  this->directDecl = directDecl;

}
declarator_node::~declarator_node(){
  if(this->pointer!=NULL){
    delete this->pointer;
  }
  if(this->directDecl!=NULL){
    delete this->directDecl;
  }
}
void declarator_node::print(){
  visualizer.debug("declarator");
  if(this->pointer != NULL){
    visualizer.addNode(this->id,"pointer");
    visualizer.addEdge(this->pid,this->id);
    this->pointer->setPID(this->id);
    this->pointer->print();
    this->directDecl->setPID(this->id);
    this->directDecl->print();
  }
  else if(this->directDecl!=NULL){
    this->directDecl->setPID(this->pid);
    this->directDecl->print();
  }
}
Spec* declarator_node::getSpec(){
  if(this->directDecl!=NULL){
    return this->directDecl->getSpec();
  }
  return NULL;
}
void declarator_node::generateCode(){
}