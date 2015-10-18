#ifndef __SYMBOL_NODE__H__
#define __SYMBOL_NODE__H__
#include "Spec.h"
class SymbolNode{
public:
  SymbolNode();
  SymbolNode(std::string, std::string, int = -1);
  void setName(std::string);
  void setSpec(std::string);
  void setPosition(int);
  std::string getName() const;
  std::string getSpec() const;
  int getPos() const;

private:
  std::string name;
  std::string specname;
  int pos;
};
#endif