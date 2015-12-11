#ifndef __ASMGENERATOR__H__
#define __ASMGENERATOR__H__
#include "../Debugger.h"
#include "Registers.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

class ASMGenerator{
public:
  ASMGenerator();
  void build();
  void setTACFileName(std::string filename);
  void setASMFileName(std::string filename);

private:
  void readASM();
  void makeDataSegment();
  void buildASM();
  std::string toASM(std::string aTacLine);
  void writeASM();
  void showTacLines();
  int typeToSize(std::string type);
  std::string vecToStr(std::vector<std::string> vec);
  std::vector<std::string> split(std::string line);

  Registers registers;
  Debugger asmWriter;
  std::string tacFileName;
  std::vector<std::string> tacLines;
  std::vector<std::string> asmLines;
};
#endif