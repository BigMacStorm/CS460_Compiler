#include "SymbolNode.h"

SymbolNode::SymbolNode(std::string name, Type* type, int pos){
  this->name = name;
  this->type = type;
  this->pos = pos;
}