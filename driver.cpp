#include "SymbolTable.h"
#include "Debugger.h"

extern "C"{
  int yyparse();
  int yylex();
}
SymbolTable symTable = *SymbolTable::getInstance();
Debugger reductionDebugger;
Debugger warningDebugger;
extern FILE* yyin;

int main(int argc, char** argv){
  reductionDebugger.setDebug(true);
  warningDebugger.setDebug(true);
  symTable.setDebug(true);

  std::remove("symbolTableOut.txt");

  symTable.pushTable();
  yyparse();
  symTable.popTable();

  return 0;
}
