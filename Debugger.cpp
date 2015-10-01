#include "Debugger.h"
Debugger::Debugger(){
  m_debug = false;
}
void Debugger::setDebug(bool debug){
  m_debug = debug;
}
void Debugger::debug(const std::string& message){
  if(m_debug){
      std::cout << message << std::endl;
  }
}