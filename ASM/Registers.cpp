#include "Registers.h"

Registers::Registers(){
  int reg;
  for(reg = 0; reg < 4; reg++){
    this->argPool.push(this->argRegs[reg]);
  }
  for(reg = 0; reg < 10; reg++){
    this->tempPool.push(this->tempRegs[reg]);
  }
  for(reg = 0; reg < 8; reg++){
    this->savedTempPool.push(this->savedTempRegs[reg]);
  }
}
void Registers::freeRegister(std::string reg){
  if(reg[0] == 'a'){
    this->argPool.push(reg);
  }else if(reg[0] == 't'){
    this->tempPool.push(reg);
  }else if(reg[0] == 's'){
    this->savedTempPool.push(reg);
  }
}
std::string Registers::getTempReg(){
  std::string reg = "n/a";
  if(!this->argPool.empty()){
    reg = this->argPool.front();
    this->argPool.pop();
  }
  return reg;
}
std::string Registers::getArgReg(){
  std::string reg = "n/a";
  if(!this->tempPool.empty()){
    reg = this->tempPool.front();
    this->tempPool.pop();
  }
  return reg;
}
std::string Registers::getSavedTempReg(){
  std::string reg = "n/a";
  if(!this->savedTempPool.empty()){
    reg = this->savedTempPool.front();
    this->savedTempPool.pop();
  }
  return reg;
}