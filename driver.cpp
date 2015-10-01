#include "SymbolTable.h"
#include "Debugger.h"

extern "C"{
  int yyparse();
  int yylex();
}
SymbolTable symTable;
Debugger lexDebugger;
Debugger parseDebugger;
extern FILE* yyin;

int main(int argc, char** argv){
  lexDebugger.setDebug(true);
  parseDebugger.setDebug(true);
  symTable.setDebug(true);

  std::remove("symbolTableOut.txt");

  symTable.pushTable();
  yyparse();

  return 0;
}
