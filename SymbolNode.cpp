#include "SymbolNode.h"
SymbolNode::SymbolNode(){};
SymbolNode::SymbolNode(std::string name, std::string specname, int pos){
  this->name = name;
  this->specname = specname;
  this->pos = pos;
}
void SymbolNode::setName(std::string name){
  this->name = name;
}
void SymbolNode::setSpec(std::string specname){
  this->specname = specname;
}
void SymbolNode::setPosition(int pos){
  this->pos = pos;
}
std::string SymbolNode::getName() const{
  return this->name;
}
std::string SymbolNode::getSpec() const{
  return this->specname;
}
int SymbolNode::getPos() const{
  return this->pos;
}