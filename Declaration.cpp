#include "Declaration.h"
Declaration::Declaration():mode(DeclMode::NoMode), levels(0), argSize(0), hasType(false){
}
Declaration::~Declaration(){}

// change states of declaration ***********************************************
void Declaration::pushID(std::string id){
  this->ids.push_back(id);
}
void Declaration::pushPos(int pos){
  this->pos.push_back(pos);
}
void Declaration::pushKind(SpecName::TypeKind typekind){
  //std::cout << "Kind: " << typekind;
  if(typekind == SpecName::NoKind){
    this->kindsHolder.push_back(this->kinds);
    this->kinds.clear();
    //std::cout << " Size: " << this->kindsHolder.size();
  }
  else{
    if(this->kinds.empty()){
      this->kinds.push_back(typekind);
      //std::cout << " OK";
    }
    else if(typekind != this->kinds.back()){
      this->kinds.push_back(typekind);
      //std::cout << " OK";
    }
  }
  //std::cout << " " << std::endl;
}
void Declaration::pushBase(SpecName::BaseType basetype){
  //std::cout << "Base: " << basetype << std::endl;
  if(basetype == SpecName::NoType){
    this->basesHolder.push_back(this->bases);
    this->bases.clear();
  }
  else{
    this->bases.push_back(basetype);
  }
}
void Declaration::pushQualifier(SpecName::Qualifier qualifier){
  //std::cout << "Qualifier: " << qualifier << std::endl;
  if(qualifier == SpecName::NoQualifier){
    this->qualifiersHolder.push_back(this->qualifiers);
    this->qualifiers.clear();
  }
  else{
    this->qualifiers.push_back(qualifier);
  }
}
void Declaration::pushStorage(SpecName::Storage storage){
  //std::cout << storage << std::endl;
  if(storage == SpecName::NoStorage){
    this->storagesHolder.push_back(this->storages);
    this->storages.clear();
  }
  else{
    this->storages.push_back(storage);
  }
}
void Declaration::pushSign(SpecName::Sign sign){
  //std::cout << sign << std::endl;
  if(sign == SpecName::NoSign){
    this->signsHolder.push_back(this->signs);
    this->signs.clear();
    //std::cout << "-----"<< std::endl;
  }
  else{
    this->signs.push_back(sign);
  }
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
void Declaration::setHasType(){
  this->hasType = true;
}
// getters  ******************************************************
std::string Declaration::getID(int idx) const{
   return this->ids[idx];
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
 int Declaration::getBasesNum() const{
   return this->bases.size();
 }
// base type *****************************************************************
 bool Declaration::setBaseType(TypeBasic *base, SpecName::BaseType basetype){
  SpecName::BaseType currentBaseType = base->getBaseType();
  //std::cout << "?: "<< currentBaseType << "->" << basetype << std::endl;

  // sign check (no double and float)
  if(base->isSign(SpecName::Signed) || base->isSign(SpecName::Unsigned)){
    if(!checkSigned(basetype)){
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
bool Declaration::buildBase(Spec* spec, std::vector<SpecName::BaseType> bases){
  if(!bases.empty()){
    for(int base = 0; base < bases.size(); base++){
      if(!setBaseType((TypeBasic*) spec, bases[base])){
        return false;
      }
    }
  }
  return true;
}

 // sign ********************************************************************
 bool Declaration::setSign(Spec* spec, SpecName::Sign sign){
  if(spec->getSign() != SpecName::NoSign){
    error("[P]: ERROR: Sign already exists");
    return false;
  }
  spec->setSign(sign);
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
bool Declaration::buildSign(Spec* spec, std::vector<SpecName::Sign> signs){
  // set sign
  if(!signs.empty()){
    for(int sign = 0; sign < signs.size(); sign++){
      if(!setSign(spec, signs[sign])){
        return false;
      }
    } // end sign
  }
  return true;
}
 // storage ******************************************************************
 bool Declaration::setStorage(Spec* spec, SpecName::Storage storage){
  // double storage
  if(spec->getStorage() != SpecName::NoStorage){
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
  // file scope
  else if(symTable.getLevel() == 1){
    if(storage == SpecName::Auto || storage == SpecName::Register){
      error("[P]: ERROR: illegal storage class on file-scoped variable");
      return false;
    }
  }
  spec->setStorage(storage);
  return true;
 }
 bool Declaration::buildStorage(Spec* spec, std::vector<SpecName::Storage> storages){
   // local variable has auto by default
   if(spec->getStorage() == SpecName::NoStorage && symTable.getLevel() > 1){
     spec->setStorage(SpecName::Auto);
   }
   // check validness
   if(!storages.empty()){
    for(int storage = 0; storage < storages.size(); storage++){
      if(!setStorage(spec,storages[storage])){
        return false;
      }
    }
   }
   return true;
 }

 // qualifier *****************************************************************
 bool Declaration::setQualifier(Spec* spec, SpecName::Qualifier qualifier){
  SpecName::Qualifier currentQualifier = spec->getQualifier();
  if(currentQualifier != SpecName::NoQualifier){
    if( (qualifier == SpecName::Const && currentQualifier == SpecName::Volatile) ||
      (qualifier == SpecName::Volatile && currentQualifier == SpecName::Const)){
      spec->setQualifier(SpecName::ConstVolatile);
      return true;
    }
    return false;
  }
  spec->setQualifier(qualifier);
  return true;
 }
 bool Declaration::buildQualifier(Spec* spec, std::vector<SpecName::Qualifier> qualifiers){
  if(!qualifiers.empty()){
    for(int qualifier = 0; qualifier < qualifiers.size(); qualifier++){
      if(!setQualifier(spec,qualifiers[qualifier])){
        return false;
      }
    }
  }
   return true;
 }
// push to symbol table ****************************************************
bool Declaration::complete(){
  bool complete = false;
  std::string name = this->ids[0];
  std::cout << "Identifier \'" << name << "\' is processed ..."<< std::endl;
  //std::cout << "Mode: " << mode <<std::endl;

  if(isMode(DeclMode::Basic)){
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
  this->kinds.clear();
  this->bases.clear();
  this->signs.clear();
  this->qualifiers.clear();
  this->storages.clear();

  this->ids.clear();
  this->pos.clear();
  this->arraySizes.clear();
  this->levels = 0;
  return complete;
}
void Declaration::clear(){
  //std::cout << "Declaration is correctly cleared" << std::endl;
  mode = DeclMode::NoMode;

  this->arraySizes.clear();
  this->levels = 0;

  this->pos.clear();
  this->ids.clear();
  this->kinds.clear();

  this->signsHolder.clear();
  this->storagesHolder.clear();
  this->qualifiersHolder.clear();
  this->basesHolder.clear();
  this->kindsHolder.clear();

  clearArgs();
}
void Declaration::clearArgs(){
  this->argSize = 0;
  this->hasType = false;
  this->argSymbolNodes.clear();
}
TypeBasic* Declaration::makeBasicType(std::vector<SpecName::BaseType> bases, std::vector<SpecName::Sign>signs,
  std::vector<SpecName::Qualifier> qualifiers){
  //std::cout << "Building Basic Type ..." << std::endl;
  Spec spec;
  if(!buildSign(&spec,signs)){
    return NULL;
  }
  if(!buildQualifier(&spec, qualifiers)){
    return NULL;
  }
  TypeBasic *basetype = new TypeBasic(SpecName::NoStorage,spec.getQualifier(),spec.getSign());

  if(!buildBase(basetype, bases)){
    return NULL;
  }

  //std::cout << "Basic type: \'" << basetype->toTypeString() << "\' is created"<< std::endl;
  return basetype;
}
TypeBasic* Declaration::makeBasicVar(std::vector<SpecName::BaseType> bases,
  std::vector<SpecName::Sign>signs, std::vector<SpecName::Storage> storages,
   std::vector<SpecName::Qualifier> qualifiers){

  TypeBasic *base = makeBasicType(bases,signs,qualifiers);
  if(base == NULL){
    return NULL;
  }
  if(!buildStorage(base,storages)){
    return NULL;
  }
  if(base->getBaseType() == SpecName::Void){
    if(isMode(DeclMode::FunctionArg) && this->argSize > 1){
      error("[P]: ERROR: \'void\' must be the first and only parameter if specified");
    }
    else if(!isMode(DeclMode::Function) && !isMode(DeclMode::FunctionArg)){
      error("[P]: ERROR: variable has incomplete type \'void\'");
    }
  }
  return base;
}
bool Declaration::pushBasic(std::string name){
  TypeBasic* base = makeBasicVar(this->basesHolder[0],this->signsHolder[0],this->storagesHolder[0],this->qualifiersHolder[0]);
  SymbolNode *val = new SymbolNode(name,base,this->pos[0],true);
  return insertSymbol(name,val,this->pos[0]);
}

bool Declaration::pushArray(std::string name){
  Spec spec;
  // check array size
  for(int dim = 0; dim < this->arraySizes.size(); dim++){
    if(this->arraySizes[dim] < 0){
      error("[P]: ERROR: an array with a negative size");
      return false;
    }
  }
  if(!buildStorage(&spec,this->storagesHolder[0])){
    return false;
  }
  if(!buildQualifier(&spec, this->qualifiersHolder[0])){
    return false;
  }
  TypeArray *array = new TypeArray(spec.getStorage(),spec.getQualifier());
  int type = this->kindsHolder[0].size()-1;

  // basic type
  if(this->kindsHolder[0][type] == SpecName::Basic){
    TypeBasic *base = makeBasicType(this->basesHolder[0],this->signsHolder[0],this->qualifiersHolder[0]);
    if(base == NULL){
      return false;
    }
    array->setElemSpec(base);
    array->setArraySizes(this->arraySizes);
  }
  // pointer
  else if(this->kindsHolder[0][type] == SpecName::Pointer){
    TypePointer* pointer = makePointerType(this->kindsHolder[0][type-1], this->basesHolder[0],this->signsHolder[0],this->qualifiersHolder[0]);
    array->setElemSpec(pointer);
    array->setArraySizes(this->arraySizes);
  }
  // typedef

  // insert array
  SymbolNode *val = new SymbolNode(name,array,this->pos[0], true);
  return insertSymbol(name, val,this->pos[0]);
}
TypePointer* Declaration::makePointerType(SpecName::TypeKind typekind, std::vector<SpecName::BaseType> bases,
  std::vector<SpecName::Sign>signs, std::vector<SpecName::Qualifier> qualifiers){
    Spec spec;
    if(!buildQualifier(&spec, qualifiers)){
      return NULL;
    }
    TypePointer *pointer = new TypePointer(SpecName::NoStorage,spec.getQualifier());
    pointer->setLevels(this->levels);

    // basic type -------------------------------
    if(typekind == SpecName::Basic){
      TypeBasic *base = makeBasicType(bases,signs,qualifiers);
      if(base == NULL){
        return NULL;
      }
      pointer->setTargetSpec(base);
    }
    // typedef
    return pointer;
    /*
    TypePointer *pointer = new TypePointer();

    if(typekind == SpecName::Basic){
       int currentLevels = this->levels;
       if(this->levels > 1){
         this->levels--;
         TypePointer *another = makePointerType(typekind, bases,signs,qualifiers);
         if(another == NULL){
           return NULL;
         }
          pointer->setLevels(currentLevels);
          pointer->setTargetSpec(another);
          TypeBasic *base = makeBasicType(bases,signs,qualifiers);
          if(base == NULL){
            return NULL;
          }
          pointer->setTargetSpec(base);
        }
        else{
          pointer->setLevels(this->levels);
          TypeBasic *base = makeBasicType(bases,signs,qualifiers);
          if(base == NULL){
            return NULL;
          }
          pointer->setTargetSpec(base);
        }
      }
    return pointer;
     */
}
TypePointer* Declaration::makePointerVar(SpecName::TypeKind typekind, std::vector<SpecName::BaseType> bases,
  std::vector<SpecName::Sign>signs, std::vector<SpecName::Storage> storages,
   std::vector<SpecName::Qualifier> qualifiers){
  Spec spec;
  TypePointer *pointer = makePointerType(typekind,bases,signs,qualifiers);
  if(!buildStorage(pointer,storages)){
    return NULL;
  }
  return pointer;
}

bool Declaration::pushPointer(std::string name){
  TypePointer* pointer = makePointerVar(this->kindsHolder[0][0], this->basesHolder[0],this->signsHolder[0],this->storagesHolder[0],this->qualifiersHolder[0]);
  SymbolNode *val = new SymbolNode(name,pointer,this->pos[0]);
  return insertSymbol(name, val,this->pos[0]);
}
bool Declaration::pushFunction(std::string name){
  Spec spec;

  bool arg_definition_mode = false;
  int arg = 0;
  int type = 0;
  int kind = 0;

  if(!buildStorage(&spec,this->storagesHolder[type])){
    return false;
  }
  if(!buildQualifier(&spec, this->qualifiersHolder[type])){
    return false;
  }
  TypeFunction *function = new TypeFunction(spec.getStorage(),spec.getQualifier());

  // return type  ===========================================================
  if(!this->hasType){
    std::cout << "[P] WARNING: type specifier missing, defaults to \'int\'" << std::endl;
    TypeBasic* base = new TypeBasic();
    base->setBaseType(SpecName::Int);
    function->setReturnSpec(base);
  }
  else{
    Spec returnSpec;
    int num = this->kindsHolder[kind].size()-1;
    // basic ---------------------------------------------------
    if(this->kindsHolder[kind][num] == SpecName::Basic){
      TypeBasic* base = makeBasicType(this->basesHolder[num],this->signsHolder[type],this->qualifiersHolder[type]);
      if(base != NULL){
        function->setReturnSpec(base);
      }
    }
    // pointer -------------------------------------------------
    else if(this->kindsHolder[kind][num] == SpecName::Pointer){
      TypePointer* pointer = makePointerType(this->kindsHolder[kind][num-1],this->basesHolder[type],
        this->signsHolder[type],this->qualifiersHolder[type]);
      if(pointer != NULL){
        function->setReturnSpec(pointer);
      }
    }
  }

  // function arguments mode
  setMode(DeclMode::FunctionArg); // better to check if an arg exists

  // check if arg has id
  if(ids.size() == this->kindsHolder.size()){ // not quite right way ?
    arg_definition_mode = true;
    arg = 1;
  }

  // argment types ===========================================================
  for(kind++; kind < this->kindsHolder.size(); kind++){
    //std::cout << "Figuring out a new argment type ..." << std::endl;
      type++;

      int num = this->kindsHolder[kind].size()-1;
      // basic ---------------------------------------------------
      if(this->kindsHolder[kind][num] == SpecName::Basic){
        TypeBasic* base = makeBasicVar(this->basesHolder[type],this->signsHolder[type],this->storagesHolder[type],this->qualifiersHolder[type]);
        if(arg_definition_mode){
          this->argSymbolNodes.push_back(new SymbolNode(this->ids[arg], base, this->pos[arg],true));
          arg++;
        }
        function->insertArg(base);
      }
      // pointer ---------------------------------------------------
      else if(this->kindsHolder[kind][num] == SpecName::Pointer){
        TypePointer* pointer = makePointerVar(this->kindsHolder[kind][num-1], this->basesHolder[type],this->signsHolder[type],this->storagesHolder[type],this->qualifiersHolder[type]);
        if(arg_definition_mode){
          this->argSymbolNodes.push_back(new SymbolNode(this->ids[arg], pointer, this->pos[arg],true));
          arg++;
        }
        function->insertArg(pointer);
      }
  } // end argment types  ====================================================

  // insert function
  SymbolNode *val = new SymbolNode(name, function, this->pos[0]);
  return insertSymbol(name, val,this->pos[0]);
}
bool Declaration::insertSymbol(std::string name, SymbolNode* val, int pos){
  SymbolNode *sym = symTable.lookupTopTable(name);
  if(sym != NULL && sym->isDefined()){
    std::stringstream ss;
    ss << "[P]: ERROR: Redefinition of \'" << name << "\'" << "@" << pos;
    error(ss.str());
  }
  else if(symTable.lookUpShadowedSymbol(name)) {
    std::cout << "[P]: WARNING: Symbol \'"+name+"\' shadows another in parent level " << "@" << pos << std::endl;
  }
  return symTable.insertSymbol(name, val);
}
// debug ********************************************************************
void Declaration::showIDs() const{
   for(int id = 0;id < this->ids.size(); id++){
     std::cout << id << ": " << this->ids[id] << std::endl;
   }
}
void Declaration::showKinds() const{
    for(int n = 0; n < this->kindsHolder.size(); n++){
      for(int kind = 0; kind < this->kindsHolder[n].size(); kind++){
        std::cout << this->kindsHolder[n].at(kind) << std::endl;
      }
    }
  }
void Declaration::showSigns() const{
  for(int n = 0; n < this->signsHolder.size(); n++){
    for(int sign = 0; sign < this->signsHolder[n].size(); sign++){
      std::cout << this->signsHolder[n].at(sign) << std::endl;
    }
  }
}
void Declaration::showBases() const{
  for(int n = 0; n < this->basesHolder.size(); n++){
    for(int base = 0; base < this->basesHolder[n].size(); base++){
      std::cout << this->basesHolder[n].at(base) << std::endl;
    }
  }
}
void Declaration::showStorages() const{
  for(int n = 0; n < this->storagesHolder.size(); n++){
    for(int storage = 0; storage< this->storagesHolder[n].size(); storage++){
      std::cout << this->storagesHolder[n].at(storage) << std::endl;
    }
  }
}
void Declaration::showQualifiers() const{
  for(int n = 0; n < this->qualifiersHolder.size(); n++){
    for(int qualifier = 0; qualifier< this->qualifiersHolder[n].size(); qualifier++){
      std::cout << this->qualifiersHolder[n].at(qualifier) << std::endl;
    }
  }
}