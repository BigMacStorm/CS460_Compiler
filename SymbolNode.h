#ifndef __SYMBOL_NODE__H__
#define __SYMBOL_NODE__H__
#include "Spec.h"
class SymbolNode{
public:
  SymbolNode();
  SymbolNode(std::string, Spec* specifier, int = -1, bool = false);

  // setter
  void setName(std::string);
  //void setSpecName(std::string);
  void setPosition(int);
  void setSpecifier(Spec*);
  void setInitialized(bool initialized);
  void setDefined(bool defined);

  // getters
  std::string getName() const;
  std::string getSpecName() const;
  Spec* getSpecifier() const;
  int getPos() const;
  bool isInitialized() const;
  bool isDefined() const;

private:
  std::string name;
  //std::string specname;
  Spec* specifier;
  int pos;

  bool initialized;
  bool defined;
};
#endif