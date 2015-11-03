#include "SymbolTable.h"
#include "Debugger.h"
#include "AST/ast_node.h"
#include "graph.h"
#include <sstream>
#include <iostream>

extern "C"{
  int yyparse();
  int yylex();
}

extern FILE* yyin;

int ast_node::tempNum;
int ast_node::labelNum;
int ast_node::unique_id;

SymbolTable symTable = *SymbolTable::getInstance();
Graph visualizer;
Debugger lexDebugger;
Debugger lexSymbolDebugger;
Debugger reductionDebugger;

extern std::string listFileName;

int main(int argc, char** argv){
  bool sdebug = false, ldebug = false, pdebug = false;
  std::string logFile = "log.txt";
  const std::string symTableLogFile = "symTableLog.txt";
  const std::string LEX_FILE = "list_file";
  const std::string GRAPH_DOT_FILE = "graph.dot";

  std::vector<std::string> args(argv, argv+argc);
  for (int arg = 1; arg < (int)args.size()-1; ++arg) {
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

  // Get source code file
  std::stringstream sourceFileName(args[args.size()-1]);
  yyin = fopen(sourceFileName.str().c_str(), "r");

  // Make .list file from source name
  getline(sourceFileName, listFileName, '.');
  listFileName += ".list";

  std::cout << listFileName << std::endl;

  std::remove(logFile.c_str());
  std::remove(symTableLogFile.c_str());
  std::remove(listFileName.c_str());
  std::remove(LEX_FILE.c_str());
  std::remove(GRAPH_DOT_FILE.c_str());

  lexDebugger.setFileName(logFile);
  lexDebugger.setDebug(ldebug);
  lexSymbolDebugger.setFileName(logFile);
  lexSymbolDebugger.setDebug(ldebug);

  reductionDebugger.setFileName(logFile);
  reductionDebugger.setDebug(pdebug);

  symTable.setFileName(symTableLogFile);
  symTable.getDebugger()->setFileName(logFile);
  symTable.getDebugger()->setDebug(sdebug);

  visualizer.setVisualizer(true);
  visualizer.startBuild();

  symTable.pushTable();
  yyparse();
  symTable.popTable();

  return 0;
}
