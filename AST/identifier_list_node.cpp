#include "ast_node.h"
identifier_list_node::identifier_list_node(){
}
identifier_list_node::identifier_list_node(std::string child){
  this->children.push_back(child);
}
identifier_list_node::~identifier_list_node(){

}
void identifier_list_node::addIdentifier(std::string child){
  this->children.push_back(child);
}
std::vector<std::string> identifier_list_node::getChildren() const{
  return this->children;
}
void identifier_list_node::print(){
  visualizer.debug("identifier_list");
  visualizer.addNode(this->id,"identifier_list");
  visualizer.addEdge(this->pid,this->id);
  for(int child = 0; child < this->children.size(); child++){
    int identifier_id = ast_node::getUID();
    visualizer.addNode(identifier_id,this->children[child]);
    visualizer.addEdge(this->id,identifier_id);
  }
}
std::string identifier_list_node::generateCode(){
<<<<<<< HEAD
  //returns an empty string as nothing should be needed from here
  std::string ret;
  return ret;
}
=======

}
>>>>>>> be7319b8b25d0e06628e992a04129cf8143d6907
