#include "ast_node.h"
type_qualifier_node::type_qualifier_node(): ast_node(){
}
type_qualifier_node::type_qualifier_node(TypeQualifier::Qual qual): ast_node(){
  this->qual = qual;
}
void type_qualifier_node::print(){
  std::string type;
  switch(this->qual){
    case TypeQualifier::CONST:
      type = "const";
    break;
    case TypeQualifier::VOLATILE:
      type = "volatile";
    break;
  }
  visualizer.addNode(this->id,type);
  visualizer.addEdge(this->pid,this->id);
}
void type_qualifier_node::generateCode(){
}