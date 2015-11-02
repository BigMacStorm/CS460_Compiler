#include "ast_node.h"

enumerator_list_node::enumerator_list_node(): ast_node(){
}

enumerator_list_node::enumerator_list_node(enum_specifier_node* child): ast_node(){
  this->children.push_back(child);
}

void enumerator_list_node::addAssignmentExpr(enum_specifier_node* child){
  this->children.push_back(child);
}

std::vector<enum_specifier_node*> enumerator_list_node::getChildren() const{
  return this->children;
}

void enumerator_list_node::print(){
  visualizer.addNode(this->id,"enumerator_list");
  visualizer.addEdge(this->pid,this->id);
  for(int child = 0; child < this->children.size(); child++){
    if(this->children[child]!=NULL){
      this->children[child]->setPID(this->id);
      this->children[child]->print();
    }
  }
}

void enumerator_list_node::generateCode(){
}