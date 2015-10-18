#include "Declaration.h"
Declaration::Declaration():mode(DeclMode::NoMode), levels(0){}
Declaration::~Declaration(){}

// change states of declaration ***********************************************
void Declaration::pushID(std::string id){
  this->ids.push_back(id);
}
void Declaration::pushKind(SpecName::TypeKind typekind){
  this->kinds.push_back(typekind);
}
void Declaration::pushBase(SpecName::BaseType basetype){
  this->bases.push_back(basetype);
}
void Declaration::pushQualifier(SpecName::Qualifier qualifier){
  this->qualifiers.push_back(qualifier);
}
void Declaration::pushStorage(SpecName::Storage storage){
  this->storages.push_back(storage);
}
void Declaration::pushSign(SpecName::Sign sign){
  this->signs.push_back(sign);
}
void Declaration::pushArraySize(int size){
  this->arraySizes.push_back(size);
}
void Declaration::incLevels(){
  this->levels++;
}
void Declaration::setMode(DeclMode::Mode mode){
 this->mode = mode;
}

void Declaration::setSpec(Spec& spec){
 this->spec = spec;
}

bool Declaration::setType(SpecName::TypeKind typekind){
 if(this->spec.getTypeKind() != SpecName::NoKind){
   error("[P]: ERROR: Type kind already exists");
   return false;
 }
 return true;
}

// getters  ******************************************************
 Spec* Declaration::getSpec(){
  return &this->spec;
}
std::string Declaration::getID(int idx) const{
   return this->ids[idx];
 }
 std::string Declaration::getSpecStr(int idx) const{
   return this->specs[idx];
 }

 void Declaration::summary() const{
    std::cout << "IDs:" << std::endl;
    for(int id = 0;id < this->ids.size(); id++){
      std::cout << id << ": " << this->ids[id] << std::endl;
    }
    std::cout << "Specs:" << std::endl;
    for(int spec = 0; spec < this->specs.size(); spec++){
      std::cout << spec << ": "<< this->specs[spec] << std::endl;
    }
 }

 bool Declaration::isMode(DeclMode::Mode mode) const{
  return this->mode == mode;
 }

// base type *****************************************************************
 bool Declaration::setBaseType(TypeBasic *base, SpecName::BaseType basetype){
  SpecName::BaseType currentBaseType = base->getBaseType();

  // sign check (no double and float)
  if(base->isSign(SpecName::Signed) || base->isSign(SpecName::Unsigned)){
    if(checkSigned(basetype)){
      base->setBaseType(basetype);
      return true;
    }
    return false;
  }

  // no type
  if(currentBaseType == SpecName::NoType){
    // otherwise
    base->setBaseType(basetype);
    return true;
  }

  // int check
  if(basetype == SpecName::Int){
    if(currentBaseType == SpecName::Short || currentBaseType == SpecName::Long || currentBaseType == SpecName::LLong){
        // keep current type
        return true;
    }
    error("[P]: ERROR: \'"+base->getBaseTypeStr()+" "+base->basetToStr(basetype)+"\' is invalid");
    return false;
  }

  // short check
  if(basetype == SpecName::Short){
    if(currentBaseType == SpecName::Int){
      base->setBaseType(basetype);
      return true;
    }
    error("[P]: ERROR: \'"+base->getBaseTypeStr()+" "+base->basetToStr(basetype)+"\' is invalid");
    return false;
  }

  // long check
  if(basetype == SpecName::Long){
    if(currentBaseType == SpecName::Long){
      base->setBaseType(SpecName::LLong);
      return true;
    }
    else if(currentBaseType == SpecName::Int){
      base->setBaseType(SpecName::Long);
      return true;
    }
    else if(currentBaseType == SpecName::Double){
      base->setBaseType(SpecName::LDouble);
      return true;
    }
    error("[P]: ERROR: \'"+base->getBaseTypeStr()+" "+base->basetToStr(basetype)+"\' is invalid");
    return false;
  }
  // check double
  if(basetype == SpecName::Double){
    if(currentBaseType == SpecName::Long){
      base->setBaseType(SpecName::LDouble);
      return true;
    }
  }
  // other invalid combination
  error("[P]: ERROR: \'"+base->getBaseTypeStr()+" "+base->basetToStr(basetype)+"\' is invalid");
  return false;
 }
 // sign ********************************************************************
 bool Declaration::setSign(SpecName::Sign sign){
  if(this->spec.getSign() != SpecName::NoSign){
    error("[P]: ERROR: Sign already exists");
    return false;
  }
  this->spec.setSign(sign);
  return true;
 }
bool Declaration::checkSigned(SpecName::BaseType type) const{
  if(type == SpecName::Double || type == SpecName::LDouble){
    error("[P]: ERROR: \'double\' cannot be signed or unsigned");
    return false;
  }
  else if(type == SpecName::Float){
    error("[P]: ERROR: \'float\' cannot be signed or unsigned");
    return false;
  }
  return true;
}
 // storage ******************************************************************
 bool Declaration::setStorage(SpecName::Storage storage){
  if(this->spec.getStorage() != SpecName::NoStorage){
    error("[P]: ERROR: Sign already exists");
    return false;
  }
  if(symTable.getLevel() == 1){
    if(storage == SpecName::Auto || storage == SpecName::Register){
      error("[P]: ERROR: illegal storage class on file-scoped variable");
      return false;
    }
  }
  this->spec.setStorage(storage);
  return true;
 }

 // qualifier *****************************************************************
 bool Declaration::setQualifier(SpecName::Qualifier qualifier){
  SpecName::Qualifier currentQualifier = this->spec.getQualifier();
  if(currentQualifier != SpecName::NoQualifier){
    if( (qualifier == SpecName::Const && currentQualifier == SpecName::Volatile) ||
      (qualifier == SpecName::Volatile && currentQualifier == SpecName::Const)){
      this->spec.setQualifier(SpecName::ConstVolatile);
      return true;
    }
    return false;
  }
  this->spec.setQualifier(qualifier);
  return true;
 }

// push to symbol table ****************************************************
bool Declaration::complete(){
  bool complete = false;
  // default: basic mode (no mode)
  if(isMode(DeclMode::NoMode)){
    complete = pushBasic(this->ids[0]);
  }
  else if(isMode(DeclMode::Array)){
    complete = pushArray(this->ids[0]);
  }
  else if(isMode(DeclMode::Pointer)){
    complete = pushPointer(this->ids[0]);
  }
  else if(isMode(DeclMode::Enum)){

  }
  else if(isMode(DeclMode::Struct)){

  }
  else if(isMode(DeclMode::Union)){

  }
  else if(isMode(DeclMode::Function)){
    complete = pushFunction(this->ids[0]);
  }
  else if(isMode(DeclMode::FunctionCall)){

  }
  this->ids.clear();
  this->arraySizes.clear();
  this->levels = 0;
  return complete;
}
void Declaration::clear(){
  mode = DeclMode::NoMode;
  this->spec = Spec();
  this->ids.clear();
  this->kinds.clear();
  this->bases.clear();
  this->arraySizes.clear();
  this->levels = 0;
}
TypeBasic* Declaration::makeBasicType(){
  TypeBasic *base = new TypeBasic(this->spec.getStorage(),this->spec.getQualifier(),this->spec.getSign());
  for(int n = 0; n < this->bases.size(); n++){
    if(!setBaseType(base,this->bases[n])){
      delete base;
      base = NULL;
    }
  }
  return base;
}
bool Declaration::pushBasic(std::string name){
  TypeBasic *base = makeBasicType();
  SymbolNode *val = symTable.lookupSymbol(name);
  if(val != NULL){
    val->setSpec(base->toString());
  }
  return symTable.insertSymbol(name, val);
}

bool Declaration::pushArray(std::string name){
  // check array size
  for(int dim = 0; dim < this->arraySizes.size(); dim++){
    if(this->arraySizes[dim] < 0){
      error("[P]: ERROR: an array with a negative size");
      return false;
    }
  }

  TypeArray array = TypeArray(this->spec.getStorage(),this->spec.getQualifier(),this->spec.getSign());

  // basic type
  if(this->kinds[0] == SpecName::Basic){
    TypeBasic *base = makeBasicType();
    if(base == NULL){
      return false;
    }
    array.setElemType(base->getTypeName());
    array.setArraySizes(this->arraySizes);
  }

  // typedef

  // pointer

  // insert array
  SymbolNode *val = symTable.lookupSymbol(name);
  if(val != NULL){
    val->setSpec(array.toString());
  }
  return symTable.insertSymbol(name, val);
}
bool Declaration::pushPointer(std::string name){
  TypePointer pointer = TypePointer(this->spec.getStorage(),this->spec.getQualifier(),this->spec.getSign());
  pointer.setLevels(this->levels);

  // basic type
  if(this->kinds[0] == SpecName::Basic){
    TypeBasic *base = makeBasicType();
    if(base == NULL){
      return false;
    }
    pointer.setTargetType(base->getTypeName());
  }
  // typedef

  // insert pointer
  SymbolNode *val = symTable.lookupSymbol(name);
  if(val != NULL){
    val->setSpec(pointer.toString());
  }
  return symTable.insertSymbol(name, val);
}
bool Declaration::pushFunction(std::string name){

  return true;
}