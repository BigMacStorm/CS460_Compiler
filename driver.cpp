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

int main(int argc, char** argv){
  bool sdebug = false, ldebug = false, pdebug = false;
  std::string logFile = "log.txt";
  std::string symTableLogFile = "symTableLog.txt";
  const std::string LIST_FILE = "list_file";
  const std::string LEX_FILE = "list_file";

  std::vector<std::string> args(argv, argv+argc);
  for (int arg = 1; arg < args.size(); ++arg) {
       if (args[arg] == "-o"){
         logFile = args[arg+1];
       }
       else if (args[arg] == "-d"){
         if(args[arg+1].find("s") != std::string::npos){
          sdebug = true;
         }
         if(args[arg+1].find("l") != std::string::npos){
          ldebug = true;
         }
         if(args[arg+1].find("p") != std::string::npos){
          pdebug = true;
         }
       }
   }

  std::remove(logFile.c_str());
  std::remove(symTableLogFile.c_str());
  std::remove(LIST_FILE.c_str());
  std::remove(LEX_FILE.c_str());

  lexDebugger.setFileName(logFile);
  lexDebugger.setDebug(ldebug);
  lexSymbolDebugger.setFileName(logFile);
  lexSymbolDebugger.setDebug(ldebug);

  reductionDebugger.setFileName(logFile);
  reductionDebugger.setDebug(pdebug);

  symTable.setFileName(symTableLogFile);
  symTable.getDebugger()->setFileName(logFile);
  symTable.getDebugger()->setDebug(sdebug);

  symTable.pushTable();
  yyparse();
  symTable.popTable();

  return 0;
}
