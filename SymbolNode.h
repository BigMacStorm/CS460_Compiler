#ifndef __SYMBOL_NODE__H__
#define __SYMBOL_NODE__H__
#include "Spec.h"
class SymbolNode{
public:
  SymbolNode();
  SymbolNode(std::string, std::string, int = -1);

  // setters
  void setName(std::string);
  void setSpecName(std::string);
  void setPosition(int);
  void setSpecifier(Spec*);

  // getters
  std::string getName() const;
  std::string getSpecName() const;
  Spec* getSpecifier() const;
  int getPos() const;

private:
  std::string name;
  std::string specname;
  Spec* specifier;
  int pos;
};
#endif