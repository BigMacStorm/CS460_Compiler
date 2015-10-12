#include "Type.h"
Type::Type(TypeName::TypeKind tk, TypeName::Storage sc, TypeName::Qualifier tq){
  this->typekind = tk;
  this->storage = sc;
  this->qualifier = tq;
}

void Type::setTypeKind(TypeName::TypeKind typekind){
  this->typekind = typekind;
}
void Type::setStorage(TypeName::Storage storage){
  this->storage = storage;
}
void Type::setQualifier(TypeName::Qualifier qualifier){
  this->qualifier = qualifier;
}
std::string Type::getTypeStr() const{
  std::stringstream ss;
  ss << "TypeKind: "<< getTypeKindStr() << "| "
     << "StorageClass: "<< getStorageClassStr() << "| "
     << "TypeQualifier: "<< getTypeQualifierStr() << "| ";
  return ss.str();
}
std::string Type::getTypeKindStr() const{
  std::string result;
  if(this->typekind == TypeName::Basic){
    result = "basic";
  }
  else if(this->typekind == TypeName::Pointer){
    result = "pointer";
  }
  else if(this->typekind == TypeName::Array){
    result = "array";
  }
  else if(this->typekind == TypeName::Struct){
    result = "struct";
  }
  else if(this->typekind == TypeName::Union){
    result = "union";
  }
  else if(this->typekind == TypeName::Function){
    result = "function";
  }
  else if(this->typekind == TypeName::Enum){
    result = "enum";
  }
  else if(this->typekind == TypeName::TypeName){
    result = "typename";
  }
  else{
    std::cout << "Error: invalid type kind" << std::endl;
  }
  return result;
}
std::string Type::getStorageClassStr() const{
  std::string result;
  if(this->storage == TypeName::Extern){
    result = "extern";
  }
  else if(this->storage == TypeName::Static){
    result = "static";
  }
  else if(this->storage == TypeName::Auto){
    result = "auto";
  }
  else if(this->storage == TypeName::Register){
    result = "register";
  }
  else if(this->storage == TypeName::Typedef){
    result = "typedef";
  }
  else{
    std::cout << "Error: invalid storage class" << std::endl;
  }
  return result;
}
std::string Type::getTypeQualifierStr() const{
  std::string result;
  if(this->qualifier == TypeName::Const){
    result = "const";
  }
  else if(this->qualifier == TypeName::Volatile){
    result = "volatile";
  }
  else if(this->qualifier == TypeName::ConstVolatile){
    result = "const volatile";
  }
  else{
    std::cout << "Error: invalid type qualifier" << std::endl;
  }
  return result;
}

// Basic -------------------------------------------------------------------
TypeBasic::TypeBasic(TypeName::BaseType baseType){
  this->typekind = TypeName::Basic;
  this->baseType = baseType;
}
void TypeBasic::setBaseType(TypeName::BaseType baseType){
  this->baseType = baseType;
}
std::string TypeBasic::getTypeKindStr() const{
  std::string result;
  if(this->baseType == TypeName::Void){
    result = "void";
  }
  else if(this->baseType == TypeName::Char){
    result = "char";
  }
  else if(this->baseType == TypeName::UChar){
    result = "unsigned char";
  }
  else if(this->baseType == TypeName::SChar){
    result = "signed char";
  }
  else if(this->baseType == TypeName::Int){
    result = "int";
  }
  else if(this->baseType == TypeName::UInt){
    result = "unsigned int";
  }
  else if(this->baseType == TypeName::Short){
    result = "short";
  }
  else if(this->baseType == TypeName::UShort){
    result = "unsigned short";
  }
  else if(this->baseType == TypeName::Long){
    result = "long";
  }
  else if(this->baseType == TypeName::ULong){
    result = "unsigned long";
  }
  else if(this->baseType == TypeName::LLong){
    result = "long long";
  }
  else if(this->baseType == TypeName::ULLong){
    result = "unsigned long long";
  }
  else if(this->baseType == TypeName::Float){
    result = "float";
  }
  else if(this->baseType == TypeName::Double){
    result = "double";
  }
  else if(this->baseType == TypeName::LDouble){
    result = "long double";
  }
  else{
    std::cout << "Error: invalid type kind" << std::endl;
  }
  return result;
}

// enum  ------------------------------------------------------------------
TypeEnum::TypeEnum(): nextNumber(0){
  this->typekind = TypeName::Enum;
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
TypeArray::TypeArray(Type *elemType, int size){
  this->typekind = TypeName::Array;
  this->elemType = elemType;
  this->size = size;
}
Type* TypeArray::getElemType() const{
  return this->elemType;
}
int TypeArray::getSize() const{
  return this->size;
}

// function ------------------------------------------------------------------
TypeFunction::TypeFunction(Type *returnType){
  this->typekind = TypeName::Function;
  this->returnType = returnType;
}
void TypeFunction::insertArg(Type *argType){
  this->argTypes.push_back(argType);
}
Type* TypeFunction::getReturnType() const{
  return this->returnType;
}
int TypeFunction::getArgSize() const{
  return this->argTypes.size();
}
Type* TypeFunction::getArgType(int nth) const{
  return this->argTypes[nth];
}
// typedef  ------------------------------------------------------------------
TypeTypeName::TypeTypeName(Type *baseType){
  this->typekind = TypeName::TypeName;
 this->baseType = baseType;
}
Type* TypeTypeName::getBaseType() const{
  return this->baseType;
}
// pointer ------------------------------------------------------------------
TypePointer::TypePointer (Type *baseType){
  this->typekind = TypeName::Pointer;
 this->baseType = baseType;
}
Type* TypePointer::getBaseType() const{
  return this->baseType;
}
// Struct -------------------------------------------------------------------
TypeStruct::TypeStruct(){
  this->typekind = TypeName::Struct;
}
void TypeStruct::addMember(std::string name, Type* type){
    this->members[name] = type;
}
Type* TypeStruct::findMember(std::string name){
  if(this->members.find(name) != this->members.end()){
     return this->members[name];
    }
    return NULL;
}
// Union ------------------------------------------------------------------
TypeUnion::TypeUnion(){
  this->typekind = TypeName::Union;
}
void TypeUnion::addMember(std::string name, Type* type){
    this->members[name] = type;
}
Type* TypeUnion::findMember(std::string name){
  if(this->members.find(name) != this->members.end()){
     return this->members[name];
    }
    return NULL;
}