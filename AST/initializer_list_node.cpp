#include "ast_node.h"
initializer_list_node::initializer_list_node(): ast_node(){
}
initializer_list_node::initializer_list_node(initializer_node* child): ast_node(){
  this->children.push_back(child);
}
void initializer_list_node::addInit(initializer_node* child){
  this->children.push_back(child);
}
std::vector<initializer_node*> initializer_list_node::getChildren() const{
  return this->children;
}
void initializer_list_node::print(){
  visualizer.debug("initializer_list");
  visualizer.addNode(this->id,"initializer_list");
  visualizer.addEdge(this->pid,this->id);
  for(int child = 0; child < this->children.size(); child++){
    if(this->children[child]!=NULL){
      this->children[child]->setPID(this->id);
      this->children[child]->print();
    }
  }
}
/*
std::vector<Spec*> initializer_list_node::getSpecs(){
  std::vector<Spec*> specs;
  for(int child = 0; child < this->children.size(); child++){
    if(this->children[child]!=NULL){
      specs[child] = this->children[child]->getSpec(); // assume 1D
    }
  }
  return specs;
}
*/
void initializer_list_node::generateCode(){
}