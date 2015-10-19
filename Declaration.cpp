#include "Declaration.h"
Declaration::Declaration():mode(DeclMode::NoMode), levels(0), argSize(0){}
Declaration::~Declaration(){}

// change states of declaration ***********************************************
void Declaration::pushID(std::string id){
  this->ids.push_back(id);
}
void Declaration::pushPos(int pos){
  this->pos.push_back(pos);
}
void Declaration::pushKind(SpecName::TypeKind typekind){
  int size = this->kinds.size();
  if(size <= 0){
    this->kinds.push_back(typekind);
  }
  else{
    if(typekind != this->kinds[size-1]){
      this->kinds.push_back(typekind);
    }
  }
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
void Declaration::incArgSize(){
  this->argSize++;
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
 bool Declaration::isMode(DeclMode::Mode mode) const{
  return this->mode == mode;
 }
int Declaration::getArgSize() const{
  return this->argSize;
 }
 std::vector<SymbolNode*> Declaration::getArgSymbolNodes() const{
  return this->argSymbolNodes;
 }

// base type *****************************************************************
 bool Declaration::setBaseType(TypeBasic *base, SpecName::BaseType basetype){
  SpecName::BaseType currentBaseType = base->getBaseType();
  //std::cout << "?: "<< currentBaseType << "->" << basetype << std::endl;

  // sign check (no double and float)
  if(base->isSign(SpecName::Signed) || base->isSign(SpecName::Unsigned)){
    if(checkSigned(basetype)){
    }
    else{
      return false;
    }
  }

  // no type
  if(currentBaseType == SpecName::NoType){
    // otherwise
    base->setBaseType(basetype);
    return true;
  }

  // int check
  if(basetype == SpecName::Int){
    if(currentBaseType == SpecName::Short ||
       currentBaseType == SpecName::Long  ||
       currentBaseType == SpecName::LLong){
        // no change
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
  //std::cout << "Set sign " << this->signs[sign] << std::endl;
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
  // double storage
  if(this->spec.getStorage() != SpecName::NoStorage){
    error("[P]: ERROR: Storage already exists");
    return false;
  }
  // function declarator
  else if(isMode(DeclMode::FunctionArg)){
    if(storage != SpecName::Register){
      error("[P]: ERROR: invalid storage class specifier in function declarator");
      return false;
    }
  }
  // top level
  else if(symTable.getLevel() == 1){
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
  std::string name = this->ids[0];
  //std::cout << "Identifier \'" << name << "\' is processed ..."<< std::endl;

  // default: basic mode (no mode)
  if(isMode(DeclMode::NoMode)){
    complete = pushBasic(name);
  }
  else if(isMode(DeclMode::Array)){
    complete = pushArray(name);
  }
  else if(isMode(DeclMode::Pointer)){
    complete = pushPointer(name);
  }
  else if(isMode(DeclMode::Enum)){

  }
  else if(isMode(DeclMode::Struct)){

  }
  else if(isMode(DeclMode::Union)){

  }
  else if(isMode(DeclMode::Function)){
    complete = pushFunction(name);
  }
  else if(isMode(DeclMode::FunctionCall)){

  }
  this->ids.clear();
  this->pos.clear();
  this->arraySizes.clear();
  this->levels = 0;
  return complete;
}
void Declaration::clear(){
  //std::cout << "Declaration is correctly cleared" << std::endl;
  mode = DeclMode::NoMode;
  this->spec = Spec();

  this->arraySizes.clear();
  this->levels = 0;

  this->pos.clear();
  this->ids.clear();
  this->kinds.clear();
  this->bases.clear();
  this->signs.clear();
  this->storages.clear();

  clearArgs();
}
void Declaration::clearArgs(){
  this->argSize = 0;
  this->argSymbolNodes.clear();
}
TypeBasic* Declaration::makeBasicType(){
    // set sign
    int sign = 0;
    while(sign < this->signs.size() && this->signs[sign] != 0){
      if(!setSign(this->signs[sign])){
        return NULL;
      }
      sign++;
    } // end sign

    TypeBasic *basetype = new TypeBasic(this->spec.getStorage(),this->spec.getQualifier(),this->spec.getSign());

    // set basetype
    int base = 0;
    while(base < this->bases.size() && this->bases[base] != 0){
      if(!setBaseType(basetype,this->bases[base])){
        delete basetype;
        return NULL;
      }
      base++;
    } // end basetype

  return basetype;
}
bool Declaration::pushBasic(std::string name){
  // set storage
  int storage = 0;
  while(storage < this->storages.size() && this->storages[storage] != 0){
    if(!setStorage(this->storages[storage])){
      return false;
    }
    storage++;
  } // end storage

  // local variable has auto by default
  if(this->spec.getStorage() == SpecName::NoStorage && symTable.getLevel() > 1){
    this->spec.setStorage(SpecName::Auto);
  }

  TypeBasic *base = makeBasicType();
  if(base == NULL){
    return false;
  }

  // no void
  if(base->getBaseType() == SpecName::Void){
    error("[P]: ERROR: variable has incomplete type \'void\'");
  }

  // insert basic
  SymbolNode *val = new SymbolNode(name,base,base->toString(),this->pos[0]);
  return insertSymbol(name,val);
}

bool Declaration::pushArray(std::string name){
  // check array size
  for(int dim = 0; dim < this->arraySizes.size(); dim++){
    if(this->arraySizes[dim] < 0){
      error("[P]: ERROR: an array with a negative size");
      return false;
    }
  }
  // set storage
  int storage = 0;
  while(storage < this->storages.size() && this->storages[storage] != 0){
    if(!setStorage(this->storages[storage])){
      return false;
    }
    storage++;
  } // end storage

  // local variable has auto by default
  if(this->spec.getStorage() == SpecName::NoStorage && symTable.getLevel() > 1){
    this->spec.setStorage(SpecName::Auto);
  }

  TypeArray *array = new TypeArray(this->spec.getStorage(),this->spec.getQualifier(),this->spec.getSign());

  // basic type
  if(this->kinds[0] == SpecName::Basic){
    TypeBasic *base = makeBasicType();
    if(base == NULL){
      return false;
    }
    array->setElemType(base->getTypeName());
    array->setArraySizes(this->arraySizes);
  }

  // typedef

  // pointer

  // insert array
  SymbolNode *val = new SymbolNode(name,array,array->toString(),this->pos[0]);
  return insertSymbol(name, val);
}
bool Declaration::pushPointer(std::string name){

  // local variable has auto by default
  if(this->spec.getStorage() == SpecName::NoStorage && symTable.getLevel() > 1){
    this->spec.setStorage(SpecName::Auto);
  }

  TypePointer *pointer = new TypePointer(this->spec.getStorage(),this->spec.getQualifier(),this->spec.getSign());
  pointer->setLevels(this->levels);

  // basic type
  if(this->kinds[0] == SpecName::Basic){
    TypeBasic *base = makeBasicType();
    if(base == NULL){
      return false;
    }
    pointer->setTargetType(base->getTypeName());
  }
  // typedef

  // insert pointer
  SymbolNode *val = new SymbolNode(name,pointer,pointer->toString(),this->pos[0]);
  return insertSymbol(name, val);
}
bool Declaration::pushFunction(std::string name){
  TypeFunction *function = new TypeFunction(this->spec.getStorage(),this->spec.getQualifier(),this->spec.getSign());
  int kind = 0;
  int sign = 0;
  int base = 0;
  int storage = 0;

  bool arg_definition_mode = false;
  int arg = 0;

  // return type  ===========================================================
  {
    while(this->kinds[kind] != 0){

      // basic ---------------------------------------------------
      if(this->kinds[kind] == SpecName::Basic){
        // set sign
        while(sign < this->signs.size() && this->signs[sign] != 0){
          if(!setSign(this->signs[sign])){
            return false;
          }
          sign++;
        } // end sign

        // set storage
        while(storage < this->storages.size() && this->storages[storage] != 0){
          if(!setStorage(this->storages[storage])){
            return false;
          }
          storage++;
        } // end storage

        TypeBasic *basetype = new TypeBasic();
        basetype->setSign(this->spec.getSign());

        // set basetype
        while(base < this->bases.size() && this->bases[base] != 0){
          if(!setBaseType(basetype,this->bases[base])){
            delete basetype;
            basetype = NULL;
            return false;
          }
          base++;
        } // end basetype
        function->setReturnType(basetype->getTypeName());
      } // end basic ---------------------------------------------------

      kind++;

    } // end loop
  } // end return type  ======================================================

  // reset spec
  this->spec = Spec();

  // function arguments mode
  setMode(DeclMode::FunctionArg); // better to check if an arg exists

  // check if arg has id
  if(ids.size()*2 == kinds.size()){ // not quite right way
    arg_definition_mode = true;
    arg = 1;
  }

  // argment types ===========================================================
  for( ; kind < this->kinds.size(); kind++){
    // new kind
    if(this->kinds[kind] != 0){
      //std::cout << "Figuring out a new argment type ..." << std::endl;

      // ignore dummy values
      if(this->bases[base] == 0){base++;}
      if(this->signs[sign] == 0){sign++;}
      if(this->storages[storage] == 0){storage++;}

      // basic ---------------------------------------------------
      if(this->kinds[kind] == SpecName::Basic){
        // set sign
        while(sign < this->signs.size() && this->signs[sign] != 0){
          if(!setSign(this->signs[sign])){
            return false;
          }
          sign++;
        } // end sign

        // set storage
        while(storage < this->storages.size() && this->storages[storage] != 0){
          if(!setStorage(this->storages[storage])){
            return false;
          }
          storage++;
        } // end storage

        TypeBasic *basetype = new TypeBasic();
        basetype->setSign(this->spec.getSign());
        basetype->setStorage(this->spec.getStorage());

        // set base
        while(base < this->bases.size() && this->bases[base] != 0){
          if(!setBaseType(basetype,this->bases[base])){
            delete basetype;
            basetype = NULL;
            return false;
          }
          base++;
        } // end base

        // arg_definition_mode
        if(arg_definition_mode){
          if(basetype->getStorage() == SpecName::NoStorage){basetype->setStorage(SpecName::Auto);}
          this->argSymbolNodes.push_back(new SymbolNode(this->ids[arg], basetype, basetype->toString(), this->pos[arg]));
          arg++;
        }

        function->insertArg(basetype->getTypeName());
      } // end basic ---------------------------------------------------

    } // end kind
    this->spec = Spec();
  } // end argment types  ====================================================

  // insert function
  SymbolNode *val = new SymbolNode(name, function, function->toString(), this->pos[0]);
  return insertSymbol(name, val);
}

bool Declaration::insertSymbol(std::string name, SymbolNode* val){
  if(symTable.lookupTopTable(name)){
    error("[S]: ERROR: Redefinition of \'"+name+"\'");
  }
  else if(symTable.lookUpShadowedSymbol(name)) {
    std::cout << "[S]: WARNING: Symbol \'"+name+"\' shadows another in parent level\n";
  }

  return symTable.insertSymbol(name, val);
}
// debug ********************************************************************
void Declaration::showIDs() const{
   for(int id = 0;id < this->ids.size(); id++){
     std::cout << id << ": " << this->ids[id] << std::endl;
   }
}
void Declaration::showSigns() const{
  for(int n = 0; n < this->signs.size(); n++){
    std::cout << this->signs[n] << std::endl;
  }
}
void Declaration::showKinds() const{
  for(int n = 0; n < this->kinds.size(); n++){
    std::cout << this->kinds[n] << std::endl;
  }
}
void Declaration::showBases() const{
  for(int n = 0; n < this->bases.size(); n++){
    std::cout << this->bases[n] << std::endl;
  }
}
void Declaration::showStorages() const{
  for(int n = 0; n < this->storages.size(); n++){
    std::cout << this->storages[n] << std::endl;
  }
}