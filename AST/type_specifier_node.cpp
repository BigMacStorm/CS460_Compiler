#include "ast_node.h"
type_specifier_node::type_specifier_node(): ast_node(){
}
type_specifier_node::type_specifier_node(TypeSpecifier::Type type): ast_node(){
  this->type = type;
}
void type_specifier_node::print(){
  std::string type;
  switch(this->type){
    case TypeSpecifier::VOID:
      type = "void";
    break;
    case TypeSpecifier::CHAR:
      type = "char";
    break;
    case TypeSpecifier::SHORT:
      type = "short";
    break;
<<<<<<< HEAD
=======
    case TypeSpecifier::LONG:
      type = "long";
    break;
>>>>>>> symbol
    case TypeSpecifier::INT:
      type = "int";
    break;
    case TypeSpecifier::FLOAT:
      type = "float";
    break;
    case TypeSpecifier::DOUBLE:
      type = "double";
    break;
    case TypeSpecifier::SIGNED:
      type = "signed";
    break;
    case TypeSpecifier::UNSIGNED:
      type = "unsigned";
    break;
    case TypeSpecifier::TYPEDEF_NAME:
      type = "type_name";
    break;
  }
  visualizer.addNode(this->id,type);
  visualizer.addEdge(this->pid,this->id);
}
void type_specifier_node::generateCode(){
}