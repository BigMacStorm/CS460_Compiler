#ifndef __SYMBOL_TABLE__H__
#define __SYMBOL_TABLE__H__
#include <stack>
#include <map>
#include <fstream>
#include <iostream>
#include "Debugger.h"
#include "SymbolNode.h"

class SymbolTable{
public:
  ~SymbolTable();
  static SymbolTable* getInstance();
  void pushTable(std::map<std::string, SymbolNode*>);
  void pushTable();
  void popTable();

  bool insertSymbol(const std::string&, SymbolNode*);

  SymbolNode* lookupTopTable(const std::string&);
  SymbolNode* lookUpShadowedSymbol(const std::string& key);
  SymbolNode* lookupSymbol(const std::string&);

  void writeFile();
  void setFileName(const std::string filename);
  Debugger* getDebugger() const;

private:
  SymbolTable();
  static SymbolTable* instance;
  Debugger* debugger;
  std::stack< std::map<std::string, SymbolNode*> > symTables;
  std::string filename;
};

#endif