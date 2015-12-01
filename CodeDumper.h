#ifndef __CODE_DUMPER__H__
#define __CODE_DUMPER__H__
#include "Debugger.h"
class CodeDumper: public Debugger{
public:
  CodeDumper();
  void debug(const std::string& message);
private:
  int codeLineNum;
};
#endif