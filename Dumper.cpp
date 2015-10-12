#include "Dumper.h"
Dumper::Dumper(){
  this->m_dump = false;
}
Dumper::~Dumper(){
  this->fout.close();
}
void Dumper::setDump(bool dump){
  this->m_dump = dump;
  if(dump == true){
    this->fout.open(this->filename.c_str(), );
  }else{
    this->fout.close();
  }
}
void Dumper::setName(string filename){
 this->filename = filename;
}
void Dumper::dump(const std::string& message){
  if(this->m_dump){
      this->fout << message << std::endl;
    }
}
