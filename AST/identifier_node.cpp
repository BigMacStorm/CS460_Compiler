#include "ast_node.h"
identifier_node::identifier_node(std::string name, SymbolNode* symnode): ast_node(){
  this->id_name = name;
  this->id_symnode = symnode;
}
SymbolNode* identifier_node::getSymNode() const{
  return this->id_symnode;
}
void identifier_node::print(){
  visualizer.addNode(this->id,this->id_name);
  visualizer.addEdge(this->pid,this->id);
}
void identifier_node::generateCode(){
}