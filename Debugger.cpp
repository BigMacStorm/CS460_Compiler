#include "Debugger.h"
Debugger::Debugger(){
  this->m_debug = false;
}
Debugger::~Debugger(){
  this->close();
}
void Debugger::close(){
  if(this->pfout != NULL){
    if(this->pfout->is_open()){
      this->pfout->close();
    }
    delete pfout;
    pfout = NULL;
  }
}
void Debugger::create(){
  this->close();
  this->pfout = new std::ofstream();
  this->pfout->open(this->filename.c_str(), std::ofstream::app);
}
void Debugger::setDebug(bool debug){
  this->m_debug = debug;
  if(debug == true){
    this->create();
  }else{
    this->close();
  }
}
void Debugger::setFileName(const std::string& filename){
 this->filename = filename;
}
void Debugger::debug(const std::string& message){
  if(this->m_debug){
      *(this->pfout) << message << std::endl;
    }
}
