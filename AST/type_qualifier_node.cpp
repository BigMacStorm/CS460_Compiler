#include "ast_node.h"
type_qualifier_node::type_qualifier_node(): ast_node(){
}
type_qualifier_node::type_qualifier_node(SpecName::Qualifier qual): ast_node(){
  this->qual = qual;
}
void type_qualifier_node::print(){
  Spec spec;
  spec.setQualifier(this->qual);
  visualizer.addNode(this->id,spec.getTypeQualifierStr());
  visualizer.addEdge(this->pid,this->id);
}
void type_qualifier_node::generateCode(){
}