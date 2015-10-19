#include "Spec.h"
Spec::Spec(SpecName::TypeKind tk, SpecName::Storage sc,
  SpecName::Qualifier tq, SpecName::Sign sign){
  this->typekind = tk;
  this->storage = sc;
  this->qualifier = tq;
  this->sign = sign;
  this->baseType = SpecName::NoType;
}
Spec::~Spec(){}
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
std::string Spec::toString() const{
  std::stringstream ss;
  ss << "TypeKind: "<< this->getTypeKindStr()
     << " Storage: "<< this->getStorageClassStr()
     << " Qualifier: "<< this->getTypeQualifierStr()
     << " Sign: "<< this->getSignStr();
  return ss.str();
}
std::string Spec::getTypeKindStr() const{
  std::string result;
  if(this->typekind == SpecName::NoKind){
    // none
  }
  else if(this->typekind == SpecName::Basic){
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
  if(this->storage == SpecName::NoStorage){
    // none
  }
  else if(this->storage == SpecName::Extern){
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
  else if(this->storage == SpecName::NoStorage){}
  else{
    std::cout << "Error: invalid storage class" << std::endl;
  }
  return result;
}
std::string Spec::getTypeQualifierStr() const{
  std::string result;
  if(this->qualifier == SpecName::NoQualifier){
    // none
  }
  else if(this->qualifier == SpecName::Const){
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
std::string Spec::getSignStr() const{
  std::string result;
  if(this->sign == SpecName::NoSign){
    // none
  }
  else if(this->sign == SpecName::Signed){
    result = "signed";
  }
  else if(this->sign == SpecName::Unsigned){
    result = "unsigned";
  }
  else{
    std::cout << "Error: invalid sign" << std::endl;
  }
  return result;
}
// Basic -------------------------------------------------------------------
TypeBasic::TypeBasic(SpecName::Storage sc,SpecName::Qualifier tq, SpecName::Sign sign){
  this->typekind = SpecName::Basic;
  this->storage = sc;
  this->qualifier = tq;
  this->sign = sign;
  this->baseType = SpecName::NoType;
}
TypeBasic::~TypeBasic(){}
std::string TypeBasic::toString() const{
  std::stringstream ss;
  std::string temp;
  temp = this->getTypeName();
  if(!temp.empty()){
    ss << temp;
  }
  temp = this->getStorageClassStr();
  if(!temp.empty()){
    ss << " " + temp;
  }
  temp = this->getTypeQualifierStr();
  if(!temp.empty()){
    ss << " " + temp;
  }
  return ss.str();
}
std::string TypeBasic::basetToStr(SpecName::BaseType basetype) const{
  std::string result;
  if(basetype == SpecName::Void){
    result = "void";
  }
  else if(basetype == SpecName::Char){
    result = "char";
  }
  else if(basetype == SpecName::Int){
    result = "int";
  }
  else if(basetype == SpecName::Short){
    result = "short";
  }
  else if(basetype == SpecName::Long){
    result = "long";
  }
  else if(basetype == SpecName::LLong){
    result = "long long";
  }
  else if(basetype == SpecName::Float){
    result = "float";
  }
  else if(basetype == SpecName::Double){
    result = "double";
  }
  else if(basetype == SpecName::LDouble){
    result = "long double";
  }
  else{
    std::cout << "Error: invalid base type" << std::endl;
  }
  return result;
}
std::string TypeBasic::getBaseTypeStr() const{
  return basetToStr(this->baseType);
}
std::string TypeBasic::getTypeName() const{
  std::string result = basetToStr(this->baseType);
  std::string temp = this->getSignStr();
  if(!temp.empty()){
    result = temp + " " + result;
  }
  return result;
}
SpecName::BaseType TypeBasic::getBaseType() const{
  return this->baseType;
}
void TypeBasic::setBaseType(SpecName::BaseType baseType){
  this->baseType = baseType;
}
bool TypeBasic::isBase(SpecName::BaseType baseType){
  return this->baseType == baseType;
}

// enum  ------------------------------------------------------------------
TypeEnum::TypeEnum(SpecName::Storage sc,SpecName::Qualifier tq, SpecName::Sign sign){
  this->typekind = SpecName::Enum;
  this->storage = sc;
  this->qualifier = tq;
  this->sign = sign;
  this->baseType = SpecName::NoType;
  this->nextNumber = 0;
}
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
TypeArray::TypeArray(SpecName::Storage sc,SpecName::Qualifier tq, SpecName::Sign sign){
  this->typekind = SpecName::Array;
  this->storage = sc;
  this->qualifier = tq;
  this->sign = sign;
}
std::string TypeArray::toString() const{
  std::stringstream ss;
  std::string temp;
  ss << this->elemType;
  for(int dim = 0; dim < this->arraySizes.size(); dim++){
    ss << "[" << this->arraySizes[dim] << "]";
  }
  temp = this->getStorageClassStr();
  if(!temp.empty()){
    ss << " " + temp;
  }
  temp = this->getTypeQualifierStr();
  if(!temp.empty()){
    ss << " " + temp;
  }
  return ss.str();
}
void TypeArray::setElemType(std::string elemType){
  this->elemType = elemType;
}
void TypeArray::setArraySizes(std::vector<int>& arraySizes){
  this->arraySizes = arraySizes;
}
std::string TypeArray::getElemType() const{
  return this->elemType;
}
int TypeArray::getSize(int dim) const{
  return this->arraySizes[dim];
}
int TypeArray::getDim() const{
  return this->arraySizes.size();
}

// function ------------------------------------------------------------------
TypeFunction::TypeFunction(SpecName::Storage sc,SpecName::Qualifier tq, SpecName::Sign sign){
  this->typekind = SpecName::Function;
  this->storage = sc;
  this->qualifier = tq;
  this->sign = sign;
}
std::string TypeFunction::toString() const{
  std::stringstream ss;
  std::string temp;
  ss << this->returnType + "(";
  for(int arg = 0; arg < this->argTypes.size(); arg++){
    ss << this->argTypes[arg];
    if(arg < this->argTypes.size()-1){
      ss << ", ";
    }
  }
  ss << ")";
  temp = this->getStorageClassStr();
  if(!temp.empty()){
    ss << " " + temp;
  }
  temp = this->getTypeQualifierStr();
  if(!temp.empty()){
    ss << " " + temp;
  }
  return ss.str();
}
void TypeFunction::insertArg(std::string argType){
  this->argTypes.push_back(argType);
}
void TypeFunction::setReturnType(std::string  returnType){
  this->returnType = returnType;
}
std::string  TypeFunction::getReturnType() const{
  return this->returnType;
}
int TypeFunction::getArgSize() const{
  return this->argTypes.size();
}
std::string  TypeFunction::getArgType(int nth) const{
  return this->argTypes[nth];
}
// typename  ------------------------------------------------------------------
TypeTypeName::TypeTypeName(SpecName::Storage sc,SpecName::Qualifier tq, SpecName::Sign sign){
  this->typekind = SpecName::TypeName;
  this->storage = sc;
  this->qualifier = tq;
  this->sign = sign;
  this->baseSpec = NULL;
}
Spec* TypeTypeName::getBaseSpec() const{
  return this->baseSpec;
}
// pointer ------------------------------------------------------------------
TypePointer::TypePointer(SpecName::Storage sc,SpecName::Qualifier tq, SpecName::Sign sign){
  this->typekind = SpecName::Pointer;
  this->storage = sc;
  this->qualifier = tq;
  this->sign = sign;
}
std::string TypePointer::toString() const{
  std::stringstream ss;
  std::string temp;
  ss << this->targetType;
  for(int level = 0; level < this->levels; level++){
    ss << "*";
  }
  temp = this->getStorageClassStr();
  if(!temp.empty()){
    ss << " " + temp;
  }
  temp = this->getTypeQualifierStr();
  if(!temp.empty()){
    ss << " " + temp;
  }
  return ss.str();
}
std::string TypePointer::getTargetType() const{
  return this->targetType;
}
int TypePointer::getLevels() const{
  return this->levels;
}
void TypePointer::setTargetType(std::string targetType){
  this->targetType = targetType;
}
void TypePointer::setLevels(int levels){
  this->levels = levels;
}
void TypePointer::incLevel(){
  this->levels++;
}
// Struct -------------------------------------------------------------------
TypeStruct::TypeStruct(SpecName::Storage sc,SpecName::Qualifier tq, SpecName::Sign sign){
  this->typekind = SpecName::Struct;
  this->storage = sc;
  this->qualifier = tq;
  this->sign = sign;
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
TypeUnion::TypeUnion(SpecName::Storage sc,SpecName::Qualifier tq, SpecName::Sign sign){
  this->typekind = SpecName::Union;
  this->storage = sc;
  this->qualifier = tq;
  this->sign = sign;
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