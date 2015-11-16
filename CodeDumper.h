#ifndef __CODE_DUMPER__H__
#define __CODE_DUMPER__H__
class CodeDumper: public Debugger{
public:
  CodeDumper(): Debugger(){}
  void debug(const std::string& message){
    if(this->m_debug){
        *(this->pfout) << message;
    }
  }
};
#endif