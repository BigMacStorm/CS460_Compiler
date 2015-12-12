#include "ASMGenerator.h"

ASMGenerator::ASMGenerator(){
  this->isMain = false;
}
void ASMGenerator::build(){
  readASM();
  makeDataSegment();
  //replaceTempsByRegs();
  buildASM();
  writeASM();
}
void ASMGenerator::makeDataSegment(){
  // make data segment:
  // 1. labeling .data
  // 2. declaring or initializing global variables at memory
  // 3. labeling .text

  int line;
  int space;
  bool inGlobal = true;
  std::stringstream ss;

  this->asmWriter.debug(".data\n");
  for(line = 0; line < this->tacLines.size(); line++){

    // split
    std::vector<std::string> linevec = split(this->tacLines[line]);

    // check global
    if(linevec[1] == "BeginFunc"){
      inGlobal = false;
    }
    else if(linevec[1] == "EndFunc"){
      inGlobal = true;
    }

    if(inGlobal && (linevec[1] == "Init:" || linevec[1] == "Decl:")){
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
  } // end for loop
  this->asmWriter.debug(".text\n");
}
void ASMGenerator::buildASM(){
  int line;
  for(line = 0; line < this->tacLines.size(); line++){
    this->asmLines.push_back(toASM(this->tacLines[line])+"\n");
  }
}
std::string ASMGenerator::toASM(std::string aTacLine){
  std::stringstream ss;
  std::vector<std::string> linevec = split(aTacLine);
  ss << "#" << aTacLine << "\n";

  if(std::regex_match(linevec[1],std::regex("(_LABEL)([0-9]+):"))){
    ss << linevec[1];
  }
  else if(linevec[1] == "FuncCall"){
    if(linevec[2] == "print_int"){
      // called with integer pushed on the stack
      ss << "li $v0, 1\n"
         << "lw $a0, 0(sp)\n"
         << "syscall\n";
    }
    else if(linevec[2] == "print_string"){
      // called with the address of string pushed on the stack
      ss << "li $v0, 4\n"
         << "lw $a0, 0(sp)\n"
         << "syscall\n";
    }else{
      ss << "jal " << linevec[2] << "\n";
    }
  }
  else if(linevec[1] == "PushParam"){
    ss << "sq " << linevec[2] << " -" << 4 << "(sp)\n"
       << "la $sp," << " -" <<  4 << "(sp)\n";
  }
  else if(linevec[1] == "goto"){
    ss << "j " << linevec[2];
  }
  else if(linevec[1] == "Function:"){
    if(linevec[2] == "main"){
      this->isMain = true;
    }
    ss << linevec[2] << ":";
  }
  else if(linevec[1] == "EndFunc"){
    if(this->isMain){
      ss << "li $v0, 10     # set up for exit\n"
         << "syscall        # exit";
      this->isMain = false;
    }else{
      ss << "jr $ra     # return";
    }
  }
  else if(linevec[1] == "if"){
    if(linevec[3] == "<="){
        ss << "ble " << linevec[2] << ", " << linevec[4] << ", " << linevec[6];
    }else if(linevec[3] == ">="){
        ss << "bge " << linevec[2] << ", " << linevec[4] << ", " << linevec[6];
    }else if(linevec[3] == ">"){
        ss << "bgt " << linevec[2] << ", " << linevec[4] << ", " << linevec[6];
    }else if(linevec[3] == "<"){
        ss << "blt " << linevec[2] << ", " << linevec[4] << ", " << linevec[6];
    }else if(linevec[3] == "=="){
        ss << "beq " << linevec[2] << ", " << linevec[4] << ", " << linevec[6];
    }else if(linevec[3] == "!="){
        ss << "bne " << linevec[2] << ", " << linevec[4] << ", " << linevec[6];
    }else{
      // assume it is a single condition
        ss << "beq " << linevec[2] << ", 1 " << linevec[4];
    }
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