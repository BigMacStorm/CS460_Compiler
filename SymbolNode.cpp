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
void SymbolNode::setSpecName(std::string specname){
  this->specname = specname;
}
void SymbolNode::setPosition(int pos){
  this->pos = pos;
}
std::string SymbolNode::getName() const{
  return this->name;
}
std::string SymbolNode::getSpecName() const{
  return this->specname;
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