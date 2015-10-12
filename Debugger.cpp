#include "Debugger.h"
Debugger::Debugger(){
  this->m_debug = false;
}
void Debugger::setDebug(bool debug){
  this->m_debug = debug;
}
void Debugger::debug(const std::string& message) const{
  if(this->m_debug){
      std::cout << message << std::endl;
    }
}