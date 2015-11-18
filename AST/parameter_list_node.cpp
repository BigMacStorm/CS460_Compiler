#include "ast_node.h"
parameter_list_node::parameter_list_node(): ast_node(){
}
parameter_list_node::parameter_list_node(parameter_declaration_node* child): ast_node(){
  this->children.push_back(child);
}
parameter_list_node::~parameter_list_node(){
  for(int child = 0; child < this->children.size(); child++){
    if(this->children[child]!=NULL){
      delete this->children[child];
    }
  }
}
void parameter_list_node::addParamDecl(parameter_declaration_node* child){
  this->children.push_back(child);
}
std::vector<parameter_declaration_node*> parameter_list_node::getChildren() const{
  return this->children;
}
void parameter_list_node::print(){
  visualizer.debug("parameter_list");
  visualizer.addNode(this->id,"parameter_list");
  visualizer.addEdge(this->pid,this->id);
  for(int child = 0; child < this->children.size(); child++){
    if(this->children[child]!=NULL){
      this->children[child]->setPID(this->id);
      this->children[child]->print();
    }
  }
}
std::string parameter_list_node::generateCode(){
<<<<<<< HEAD
  std::string ret;
=======
>>>>>>> be7319b8b25d0e06628e992a04129cf8143d6907
  for(int child = 0; child < this->children.size(); child++){
    if(this->children[child]!=NULL){
      this->children[child]->generateCode();
    }
  }
<<<<<<< HEAD
  return ret;
}
=======
  return "";
}
>>>>>>> be7319b8b25d0e06628e992a04129cf8143d6907
