#include "ast_node.h"
init_declarator_node::init_declarator_node(declarator_node* declarator,
                                           initializer_node* initializer):
                                           ast_node(){
  this->declarator = declarator;
  this->initializer = initializer;
}
void init_declarator_node::print(){
  if(this->initializer != NULL){
    this->equal_id = ast_node::getUID();
    visualizer.addNode(this->equal_id,"=");
    visualizer.addEdge(this->pid, this->equal_id);
    if(this->declarator!= NULL){
      this->declarator->setPID(this->equal_id);
      this->declarator->print();
    }
    if(this->initializer!= NULL){
      this->initializer->setPID(this->equal_id);
      this->initializer->print();
    }
  }
  else{
    if(this->declarator!= NULL){
      this->declarator->setPID(this->pid);
      this->declarator->print();
    }
  }
}
void init_declarator_node::generateCode(){

}