#include "Type.h"
Type::Type(TypeName::TypeKind tk, TypeName::Storage sc,
  TypeName::Qualifier tq){
  this->typekind = tk;
  this->storage = sc;
  this->qualifier = tq;
}

std::string Type::getTypeKindStr(){
  std::string result;
  if(this->typekind == TypeName::Char){
    result += "char";
  }
  else if(this->typekind == TypeName::UChar){
    result += "unsigned char";
  }
  else if(this->typekind == TypeName::SChar){
    result += "signed char";
  }
  else if(this->typekind == TypeName::Int){
    result += "int";
  }
  else if(this->typekind == TypeName::UInt){
    result += "unsigned int";
  }
  else if(this->typekind == TypeName::Short){
    result += "short";
  }
  else if(this->typekind == TypeName::UShort){
    result += "unsigned short";
  }
  else if(this->typekind == TypeName::Long){
    result += "long";
  }
  else if(this->typekind == TypeName::ULong){
    result += "unsigned long";
  }
  else if(this->typekind == TypeName::LLong){
    result += "long long";
  }
  else if(this->typekind == TypeName::ULLong){
    result += "unsigned long long";
  }
  else if(this->typekind == TypeName::Float){
    result += "float";
  }
  else if(this->typekind == TypeName::Double){
    result += "double";
  }
  else if(this->typekind == TypeName::LDouble){
    result += "long double";
  }
  else{
    std::cout << "Error: invalid type kind" << std::endl;
  }
  return result;
}
std::string Type::getStorageClassStr(){
  std::string result;
  if(this->storage == TypeName::Extern){
    result += "extern";
  }
  else if(this->storage == TypeName::Static){
    result += "static";
  }
  else if(this->storage == TypeName::Auto){
    result += "auto";
  }
  else if(this->storage == TypeName::Register){
    result += "register";
  }
  else{
    std::cout << "Error: invalid storage class" << std::endl;
  }
  return result;
}
std::string Type::getTypeQualifierStr(){
  std::string result;
  if(this->qualifier == TypeName::NoQualifier){

  }
  else if(this->qualifier == TypeName::Const){
    result += "const";
  }
  else if(this->qualifier == TypeName::Volatile){
    result += "volatile";
  }
  else{
    std::cout << "Error: invalid type qualifier" << std::endl;
  }
  return result;
}