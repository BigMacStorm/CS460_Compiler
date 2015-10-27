#include "ast_node.h"
string_node::string_node(){};
string_node::string_node(std::string string_literal){
  this->string_literal = string_literal;
}
std::string string_node::getStringLiteral(){
  return string_literal;
}
void string_node::setStringLiteral(std::string string_literal){
  this->string_literal = string_literal;
}
void string_node::print(){
  std::cout << this->string_literal;
}
void string_node::generateCode(){

}