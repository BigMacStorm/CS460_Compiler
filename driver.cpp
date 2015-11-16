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
CodeDumper codeGenerator;
Debugger lexDebugger;
Debugger lexSymbolDebugger;
Debugger reductionDebugger;

extern std::string listFileName;

int main(int argc, char** argv){
  bool sdebug = false, ldebug = false, pdebug = false, genAST = false;
  bool gen3AC = false, genAssembly = false, compileAssemble = false;

  std::string logFile = "log.txt";
  const std::string symTableLogFile = "symTableLog.txt";
  const std::string LEX_FILE = "list_file";
  const std::string GRAPH_DOT_FILE = "graph.dot";
  const std::string AST_LOG = "astlog.txt";
  const std::string CODE_LOG = "3aclog.txt";

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
       else if (args[arg] == "-c"){
         printf("'-c' flag to compile and assemble not implemented\n");
       }
       else if (args[arg] == "-a"){
         genAST = true;
       }
       else if (args[arg] == "-q"){
         gen3AC = true;
       }
       else if (args[arg] == "-S"){
         printf("'-S' flag, assembly language not implemented\n");
       }
   }

  // Get source code file
  std::stringstream sourceFileName(args[args.size()-1]);
  yyin = fopen(sourceFileName.str().c_str(), "r");

  // Make .list file from source name
  getline(sourceFileName, listFileName, '.');
  listFileName += ".list";

  std::cout << listFileName << std::endl;

  // remove logs
  std::remove(logFile.c_str());
  std::remove(symTableLogFile.c_str());
  std::remove(listFileName.c_str());
  std::remove(LEX_FILE.c_str());
  std::remove(GRAPH_DOT_FILE.c_str());
  std::remove(AST_LOG.c_str());
  std::remove(CODE_LOG.c_str());

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
  visualizer.setDebug(genAST);
  visualizer.startBuild();

  codeGenerator.setFileName(CODE_LOG);
  codeGenerator.setDebug(gen3AC);

  symTable.pushTable();
  yyparse();
  symTable.popTable();
  // sometimes cause seg fault around the end?

  return 0;
}
