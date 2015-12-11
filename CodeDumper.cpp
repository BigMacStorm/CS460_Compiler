#include "CodeDumper.h"
CodeDumper::CodeDumper(): Debugger(){
  this->codeLineNum = 0;
}
void CodeDumper::debug(const std::string& message){
  if(this->m_debug){
      *(this->pfout) << codeLineNum << " " << message;
      codeLineNum++;
  }
}