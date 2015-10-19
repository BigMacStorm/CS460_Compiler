#ifndef __SYMBOL_NODE__H__
#define __SYMBOL_NODE__H__
#include "Spec.h"
class SymbolNode{
public:
  SymbolNode();
  SymbolNode(std::string, Spec* = NULL, int = -1);
  void setName(std::string);
  void setSpec(Spec*);
  void setPosition(int);
  std::string getName() const;
  Spec* getSpec() const;
  int getPos() const;

private:
  std::string name;
  Spec* spec;
  int pos;
};
#endif