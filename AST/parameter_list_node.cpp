#include "ast_node.h"
parameter_list_node::parameter_list_node(): ast_node(){
}
parameter_list_node::parameter_list_node(parameter_declaration_node* child): ast_node(){
  this->children.push_back(child);
}
void parameter_list_node::addParamDecl(parameter_declaration_node* child){
  this->children.push_back(child);
}
std::vector<parameter_declaration_node*> parameter_list_node::getChildren() const{
  return this->children;
}
void parameter_list_node::print(){
  visualizer.addNode(this->id,"parameter_list");
  visualizer.addEdge(this->pid,this->id);
  for(int child = 0; child < this->children.size(); child++){
    if(this->children[child]!=NULL){
      this->children[child]->setPID(this->id);
      this->children[child]->print();
    }
  }
}
void parameter_list_node::generateCode(){
}