#include "ast_node.h"

enum_specifier_node::enum_specifier_node(){
}

enum_specifier_node::enum_specifier_node(identifier_node* id, enumerator_list_node* enm){
    this->enumList = enm;
    this->id = id;
}

void enum_specifier_node::print(){
  visualizer.addNode(this->id, "{}");
  visualizer.addEdge(this->pid, this->id);
  
  if(this->enumList!=NULL){
    this->enumList->setPID(this->id);
    this->enumList->print();
  }
}

void enum_specifier_node::generateCode(){

}
