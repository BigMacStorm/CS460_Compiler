#include "SymbolTable.h"
#include "Debugger.h"

extern "C"{
  int yyparse();
  int yylex();
}
SymbolTable symTable = *SymbolTable::getInstance();
Debugger lexDebugger;
Debugger lexSymbolDebugger;
Debugger reductionDebugger;
Debugger warningDebugger;

int main(int argc, char** argv){
  bool debug = false;
  std::string logFile = "log.txt";
  std::string symTableLogFile = "symTableLog.txt";

  std::vector<std::string> args(argv, argv+argc);
  for (int arg = 1; arg < args.size(); ++arg) {
       if (args[arg] == "-o"){
         logFile = args[arg+1];
       }
       else if (args[arg] == "-d"){
         debug = true;
       }
   }

  std::remove(logFile.c_str());
  std::remove(symTableLogFile.c_str());

  lexDebugger.setFileName(logFile);
  lexDebugger.setDebug(debug);
  lexSymbolDebugger.setFileName(logFile);
  lexSymbolDebugger.setDebug(debug);
  reductionDebugger.setFileName(logFile);
  reductionDebugger.setDebug(debug);
  symTable.setFileName(symTableLogFile);
  symTable.getDebugger()->setFileName(logFile);
  symTable.getDebugger()->setDebug(debug);

  symTable.pushTable();
  yyparse();
  symTable.popTable();

  return 0;
}
