#include "SymbolNode.h"
SymbolNode::SymbolNode(): initialized(false), defined(false){};
SymbolNode::SymbolNode(std::string name, Spec* specifier, int pos, bool defined){
  this->name = name;
  this->specifier = specifier;
  this->pos = pos;
  this->defined = defined;
}
void SymbolNode::setName(std::string name){
  this->name = name;
}
void SymbolNode::setPosition(int pos){
  this->pos = pos;
}
void SymbolNode::setInitialized(bool initialized){
  this->initialized = initialized;
}
void SymbolNode::setDefined(bool defined){
  this->defined = defined;
}
// getters ------------------------------
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
bool SymbolNode::isInitialized() const{
  return this->initialized;
}
bool SymbolNode::isDefined() const{
  return this->defined;
}