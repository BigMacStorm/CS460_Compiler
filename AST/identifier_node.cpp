#include "ast_node.h"
identifier_node::identifier_node(std::string name, SymbolNode* symnode){
  this->id_name = name;
  this->id_symnode = symnode;
}
SymbolNode* identifier_node::getSymNode() const{
  return this->id_symnode;
}
void identifier_node::print(){
  std::cout << this->id_name << std::endl;
}
void identifier_node::generateCode(){
}