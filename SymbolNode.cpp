#include "SymbolNode.h"
SymbolNode::SymbolNode(){};
SymbolNode::SymbolNode(std::string name, Spec* spec, int pos){
  this->name = name;
  this->spec = spec;
  this->pos = pos;
}
void SymbolNode::setName(std::string name){
  this->name = name;
}
void SymbolNode::setSpec(Spec* spec){
  this->spec = spec;
}
void SymbolNode::setPosition(int pos){
  this->pos = pos;
}
std::string SymbolNode::getName() const{
  return this->name;
}
Spec* SymbolNode::getSpec() const{
  return this->spec;
}
int SymbolNode::getPos() const{
  return this->pos;
}