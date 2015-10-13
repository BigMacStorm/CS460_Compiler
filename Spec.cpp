#include "Spec.h"
Spec::Spec(SpecName::TypeKind tk, SpecName::Storage sc,
  SpecName::Qualifier tq, SpecName::Sign sign){
  this->typekind = tk;
  this->storage = sc;
  this->qualifier = tq;
  this->sign = sign;
}

SpecName::TypeKind Spec::getTypeKind() const{
  return this->typekind;
}
SpecName::Storage Spec::getStorage() const{
  return this->storage;
}
SpecName::Qualifier Spec::getQualifier() const{
  return this->qualifier;
}
SpecName::Sign Spec::getSign() const{
  return this->sign;
}

void Spec::setTypeKind(SpecName::TypeKind typekind){
  this->typekind = typekind;
}
void Spec::setStorage(SpecName::Storage storage){
  this->storage = storage;
}
void Spec::setQualifier(SpecName::Qualifier qualifier){
  this->qualifier = qualifier;
}
void Spec::setSign(SpecName::Sign sign){
  this->sign = sign;
}

bool Spec::isTypeKind(SpecName::TypeKind type) const {
  return this->typekind == type;
}
bool Spec::isStorageClass(SpecName::Storage type) const {
  return this->storage == type;
}
bool Spec::isTypeQualifier(SpecName::Qualifier type) const {
  return this->qualifier == type;
}
bool Spec::isSign(SpecName::Sign type) const {
  return this->sign == type;
}

std::string Spec::getSpecStr() const{
  std::stringstream ss;
  ss << "TypeKind: "<< getTypeKindStr() << "| "
     << "StorageClass: "<< getStorageClassStr() << "| "
     << "TypeQualifier: "<< getTypeQualifierStr() << "| ";
  return ss.str();
}
std::string Spec::getTypeKindStr() const{
  std::string result;
  if(this->typekind == SpecName::Basic){
    result = "basic";
  }
  else if(this->typekind == SpecName::Pointer){
    result = "pointer";
  }
  else if(this->typekind == SpecName::Array){
    result = "array";
  }
  else if(this->typekind == SpecName::Struct){
    result = "struct";
  }
  else if(this->typekind == SpecName::Union){
    result = "union";
  }
  else if(this->typekind == SpecName::Function){
    result = "function";
  }
  else if(this->typekind == SpecName::Enum){
    result = "enum";
  }
  else if(this->typekind == SpecName::TypeName){
    result = "typename";
  }
  else{
    std::cout << "Error: invalid type kind" << std::endl;
  }
  return result;
}
std::string Spec::getStorageClassStr() const{
  std::string result;
  if(this->storage == SpecName::Extern){
    result = "extern";
  }
  else if(this->storage == SpecName::Static){
    result = "static";
  }
  else if(this->storage == SpecName::Auto){
    result = "auto";
  }
  else if(this->storage == SpecName::Register){
    result = "register";
  }
  else if(this->storage == SpecName::Typedef){
    result = "typedef";
  }
  else{
    std::cout << "Error: invalid storage class" << std::endl;
  }
  return result;
}
std::string Spec::getTypeQualifierStr() const{
  std::string result;
  if(this->qualifier == SpecName::Const){
    result = "const";
  }
  else if(this->qualifier == SpecName::Volatile){
    result = "volatile";
  }
  else if(this->qualifier == SpecName::ConstVolatile){
    result = "const volatile";
  }
  else{
    std::cout << "Error: invalid type qualifier" << std::endl;
  }
  return result;
}
// Basic -------------------------------------------------------------------
TypeBasic::TypeBasic(SpecName::BaseType baseType){
  this->typekind = SpecName::Basic;
  this->baseType = baseType;
}
void TypeBasic::setBaseType(SpecName::BaseType baseType){
  this->baseType = baseType;
}
std::string TypeBasic::getTypeKindStr() const{
  std::string result;
  if(this->baseType == SpecName::Void){
    result = "void";
  }
  else if(this->baseType == SpecName::Char){
    result = "char";
  }
  else if(this->baseType == SpecName::UChar){
    result = "unsigned char";
  }
  else if(this->baseType == SpecName::SChar){
    result = "signed char";
  }
  else if(this->baseType == SpecName::Int){
    result = "int";
  }
  else if(this->baseType == SpecName::UInt){
    result = "unsigned int";
  }
  else if(this->baseType == SpecName::Short){
    result = "short";
  }
  else if(this->baseType == SpecName::UShort){
    result = "unsigned short";
  }
  else if(this->baseType == SpecName::Long){
    result = "long";
  }
  else if(this->baseType == SpecName::ULong){
    result = "unsigned long";
  }
  else if(this->baseType == SpecName::LLong){
    result = "long long";
  }
  else if(this->baseType == SpecName::ULLong){
    result = "unsigned long long";
  }
  else if(this->baseType == SpecName::Float){
    result = "float";
  }
  else if(this->baseType == SpecName::Double){
    result = "double";
  }
  else if(this->baseType == SpecName::LDouble){
    result = "long double";
  }
  else{
    std::cout << "Error: invalid type kind" << std::endl;
  }
  return result;
}

// enum  ------------------------------------------------------------------
TypeEnum::TypeEnum(): nextNumber(0){
  this->typekind = SpecName::Enum;
};
int TypeEnum::getSize() const{
  return constants.size();
}
void TypeEnum::addConst(std::string name, int number){
  constants[name] = number;
  this->nextNumber = ++number;
}
int TypeEnum::getNextNumber() const{
  return this->nextNumber;
}

// array -----------------------------------------------
TypeArray::TypeArray(Spec*elemType, int size){
  this->typekind = SpecName::Array;
  this->elemType = elemType;
  this->size = size;
}
Spec* TypeArray::getElemType() const{
  return this->elemType;
}
int TypeArray::getSize() const{
  return this->size;
}

// function ------------------------------------------------------------------
TypeFunction::TypeFunction(Spec*returnType){
  this->typekind = SpecName::Function;
  this->returnType = returnType;
}
void TypeFunction::insertArg(Spec*argType){
  this->argTypes.push_back(argType);
}
Spec* TypeFunction::getReturnType() const{
  return this->returnType;
}
int TypeFunction::getArgSize() const{
  return this->argTypes.size();
}
Spec* TypeFunction::getArgType(int nth) const{
  return this->argTypes[nth];
}
// typedef  ------------------------------------------------------------------
TypeTypeName::TypeTypeName(Spec*baseType){
  this->typekind = SpecName::TypeName;
 this->baseType = baseType;
}
Spec* TypeTypeName::getBaseType() const{
  return this->baseType;
}
// pointer ------------------------------------------------------------------
TypePointer::TypePointer (Spec*baseType){
  this->typekind = SpecName::Pointer;
 this->baseType = baseType;
}
Spec* TypePointer::getBaseType() const{
  return this->baseType;
}
// Struct -------------------------------------------------------------------
TypeStruct::TypeStruct(){
  this->typekind = SpecName::Struct;
}
void TypeStruct::addMember(std::string name, Spec* type){
    this->members[name] = type;
}
Spec* TypeStruct::findMember(std::string name){
  if(this->members.find(name) != this->members.end()){
     return this->members[name];
    }
    return NULL;
}
// Union ------------------------------------------------------------------
TypeUnion::TypeUnion(){
  this->typekind = SpecName::Union;
}
void TypeUnion::addMember(std::string name, Spec* type){
    this->members[name] = type;
}
Spec* TypeUnion::findMember(std::string name){
  if(this->members.find(name) != this->members.end()){
     return this->members[name];
    }
    return NULL;
}