#include "SymbolTable.h"
#include "Debugger.h"
#include "CodeDumper.h"
#include "graph.h"
#include "AST/ast_node.h"
#include "ASM/ASMGenerator.h"
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

SymbolTable *symTable;
Graph visualizer;
CodeDumper codeGenerator;
Debugger lexDebugger;
Debugger lexSymbolDebugger;
Debugger reductionDebugger;

extern std::string listFileName;

int main(int argc, char** argv){
  ASMGenerator *asmGenerator = NULL;
  symTable = new SymbolTable();

  // flags
  bool sdebug = false, ldebug = false, pdebug = false, genAST = false;
  bool gen3AC = false, genAssembly = false, compileAssemble = false;

  // filenames
  std::string logFile = "log.txt";
  const std::string symTableLogFile = "symTableLog.txt";
  const std::string LEX_FILE = "list_file";
  const std::string GRAPH_DOT_FILE = "graph.dot";
  const std::string AST_LOG = "astlog.txt";
  std::string tac_file;
  std::string asm_file;

  // arguments handling
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
        compileAssemble = true;
       }
   }

  // Get source code file
  std::stringstream sourceFileName(args[args.size()-1]);
  std::string cfilename;
  yyin = fopen(sourceFileName.str().c_str(), "r");

  // Make files from source name
  getline(sourceFileName, cfilename, '.');
  listFileName = cfilename + ".list";
  tac_file = cfilename + "_3ac.txt";
  asm_file = cfilename + "_mips.s";

  std::cout << listFileName << std::endl;
  std::cout << tac_file << std::endl;
  std::cout << asm_file << std::endl;

  // remove existing files
  std::remove(logFile.c_str());
  std::remove(symTableLogFile.c_str());
  std::remove(listFileName.c_str());
  std::remove(LEX_FILE.c_str());
  std::remove(GRAPH_DOT_FILE.c_str());
  std::remove(AST_LOG.c_str());
  std::remove(tac_file.c_str());
  std::remove(asm_file.c_str());

  lexDebugger.setFileName(logFile);
  lexDebugger.setDebug(ldebug);
  lexSymbolDebugger.setFileName(logFile);
  lexSymbolDebugger.setDebug(ldebug);

  reductionDebugger.setFileName(logFile);
  reductionDebugger.setDebug(pdebug);

  symTable->setFileName(symTableLogFile);
  symTable->getDebugger()->setFileName(logFile);
  symTable->getDebugger()->setDebug(sdebug);

  visualizer.setVisualizer(true);
  visualizer.setDebug(genAST);
  visualizer.startBuild();

  codeGenerator.setFileName(tac_file);
  codeGenerator.setDebug(gen3AC);

  symTable->pushTable();
  yyparse();
  // sometimes cause seg fault around the end?

  // close files
  codeGenerator.close();
  lexDebugger.close();
  lexSymbolDebugger.close();
  reductionDebugger.close();

  asmGenerator = new ASMGenerator();
  asmGenerator->setTACFileName(tac_file);
  asmGenerator->setASMFileName(asm_file);
  asmGenerator->build();
  delete asmGenerator;

  return 0;
}
