#ifndef __SYMBOL_NODE__H__
#define __SYMBOL_NODE__H__
#include "Type.h"
class SymbolNode{
public:
  SymbolNode(std::string, Type*, int);
  std::string name;
  Type* type;
  int pos;
};
#endif