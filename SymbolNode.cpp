#include "SymbolNode.h"
SymbolNode::SymbolNode(){};
SymbolNode::SymbolNode(std::string name, Spec* specifier, int pos){
  this->name = name;
  this->specifier = specifier;
  this->pos = pos;
}
void SymbolNode::setName(std::string name){
  this->name = name;
}
void SymbolNode::setPosition(int pos){
  this->pos = pos;
}
std::string SymbolNode::getName() const{
  return this->name;
}
std::string SymbolNode::getSpecName() const{
  return this->specifier->toString();
}
int SymbolNode::getPos() const{
  return this->pos;
}
void SymbolNode::setSpecifier(Spec* specifier){
  this->specifier = specifier;
}
Spec* SymbolNode::getSpecifier() const{
  return this->specifier;
}