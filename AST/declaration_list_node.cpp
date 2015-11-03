#include "ast_node.h"
declaration_list_node::declaration_list_node(){

}
declaration_list_node::declaration_list_node(declaration_node* child){
  this->children.push_back(child);
}
void declaration_list_node::addDecl(declaration_node* child){
  this->children.push_back(child);
}
std::vector<declaration_node*> declaration_list_node::getChildren() const{
  return this->children;
}
void declaration_list_node::print(){
  visualizer.addNode(this->id,"declaration_list");
  visualizer.addEdge(this->pid,this->id);
  for(int child = 0; child < this->children.size(); child++){
    if(this->children[child]!=NULL){
      this->children[child]->setPID(this->id);
      this->children[child]->print();
    }
  }
}
void declaration_list_node::generateCode(){

}