#include "ASMGenerator.h"

ASMGenerator::ASMGenerator(){
}
void ASMGenerator::build(){
  readASM();
  makeDataSegment();
  buildASM();
  writeASM();
}
void ASMGenerator::makeDataSegment(){
  int line, space;
  std::stringstream ss;

  this->asmWriter.debug(".data\n");
  for(line = 0; line < this->tacLines.size(); line++){

    // split
    std::vector<std::string> linevec = split(this->tacLines[line]);

    if(this->tacLines[line].size() > 2){ // idk why there is an extra line....

      if(linevec[1] == "Init:" || linevec[1] == "Decl:"){
        this->asmWriter.debug("#" + this->tacLines[line]);
        // array
        if(linevec[3] == "array"){
          if(linevec[1] == "Decl:"){
            space = stoi(linevec[4]) * typeToSize(linevec[5]);
            ss << linevec[2] << ": .space " << space;
          }
          else{
            ss << linevec[2] << ": .word " << linevec[6];
          }
        }
        // basic variable
        else{
          if(linevec[1] == "Decl:"){
            space = typeToSize(linevec[3]);
            ss << linevec[2] << ": .space " << space;
          }
          else{
            ss << linevec[2] << ": .word " << linevec[4];
          }
        }
        this->asmWriter.debug(ss.str()+"\n");
        ss.str("");
      } // end init/decl case
    } // care extra line (have to remove later)
  } // end for loop
  this->asmWriter.debug(".text\n");
}
void ASMGenerator::buildASM(){
  int line;
  for(line = 0; line < this->tacLines.size(); line++){
    this->asmLines.push_back(toASM(this->tacLines[line]));
  }
}
std::string ASMGenerator::toASM(std::string aTacLine){
  std::stringstream ss;
  std::vector<std::string> linevec = split(aTacLine);
  ss << "#" << aTacLine << "\n";

  if(linevec[1] == "Function:"){
    ss << linevec[2] << ":" << "\n";
  }
  else if(linevec[1] == "if"){
    if(linevec[3] == "<=")
        ss << "ble, ";
    else if(linevec[3] == ">=")
        ss << "bge, ";
    else if(linevec[3] == ">")
        ss << "bgt, ";
    else if(linevec[3] == "<")
        ss << "blt, ";
    else if(linevec[3] == "==")
        ss << "beq, ";
    else if(linevec[3] == "!=")
        ss << "bne, ";
  }
  return ss.str();
}
void ASMGenerator::readASM(){
  std::ifstream fin;
  std::string line;
  fin.open(this->tacFileName);
  while(fin.good()){
    getline(fin,line);
    if(line != ""){
      this->tacLines.push_back(line);
    }
  }
  fin.close();
}
void ASMGenerator::writeASM(){
  int asmIdx;
  for(asmIdx = 0; asmIdx < this->asmLines.size(); asmIdx++){
    this->asmWriter.debug(this->asmLines[asmIdx]);
  }
}
void ASMGenerator::setTACFileName(std::string filename){
  this->tacFileName = filename;
}
void ASMGenerator::setASMFileName(std::string filename){
  this->asmWriter.setFileName(filename);
  this->asmWriter.setDebug(true);
}
void ASMGenerator::showTacLines(){
  int line;
  for (line = 0; line < this->tacLines.size(); line++){
    std::cout << this->tacLines[line] << std::endl;
  }
}
int ASMGenerator::typeToSize(std::string type){
  if(type == "int"){
    return 4;
  }
  return 0;
}
std::string ASMGenerator::vecToStr(std::vector<std::string> vec ){
  int tok;
  std::string result;
  for(tok = 0; tok < vec.size(); tok++){
    result += vec[tok];
  }
  return result;
}
std::vector<std::string> ASMGenerator::split(std::string line){
  std::string tok;
  std::stringstream ss(line);
  std::vector<std::string> linevec;
  while(getline(ss, tok,' ')) {
      linevec.push_back(tok);
  }
  return linevec;
}