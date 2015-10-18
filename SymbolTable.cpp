#include "SymbolTable.h"
SymbolTable* SymbolTable::instance = NULL;

SymbolTable::SymbolTable(): levels(0){
  this->debugger = new Debugger();
}
SymbolTable::~SymbolTable(){
  delete this->debugger;
  debugger = NULL;
}
SymbolTable* SymbolTable::getInstance(){
  if(SymbolTable::instance == NULL){
    SymbolTable::instance = new SymbolTable();
  }
  return SymbolTable::instance;
}
int SymbolTable::getLevel() const{
  return this->levels;
}
void SymbolTable::pushTable(std::map<std::string,SymbolNode*> newSymTable){
  this->levels++;
  this->symTables.push_back(newSymTable);
  this->debugger->debug("[S]: A new symbol table is pushed on ===========================================");
}

void SymbolTable::pushTable(){
  std::map<std::string,SymbolNode*> newSymTable;
  this->levels++;
  this->symTables.push_back(newSymTable);
  this->debugger->debug("[S]: A new symbol table is pushed on ===========================================");
}

void SymbolTable::popTable(){
  this->levels--;
  this->symTables.pop_back();
  this->debugger->debug("[S]: The top symbol table is popped off ========================================");
}
bool SymbolTable::empty() const{
  if(this->levels <= 0){
    this->debugger->debug("[S]: No Symbol Table");
    return true;
  }
  return false;
}
bool SymbolTable::insertSymbol(const std::string& key, SymbolNode* val){
  if(empty()){
    return false;
  }
  // declarations/initializations
  SymbolNode* content = lookupTopTable(key);

  this->symTables[this->levels-1][key] = val;
  if(content == NULL){
    content = lookUpShadowedSymbol(key);
    if(content == NULL){
      this->debugger->debug("[S]: Symbol "+key+" is inserted at top level");
    }
    else{
      this->debugger->debug("[S]: Symbol "+key+" shadows another in parent level");
    }
    return true;
  }
  else{
    this->debugger->debug("[S]: Symbol "+key+" is updated");
    return false;
  }
}

SymbolNode* SymbolTable::lookupTopTable(const std::string& key)
/* looks up the top level and returns the content if the key is found;
otherwise, it returns NULL.
*/
{
  if(empty()){
    return NULL;
  }

  // declarations/initializations
  SymbolNode * val = NULL;

  if(this->symTables[this->levels-1].find(key) != this->symTables[this->levels-1].end()){
      val = this->symTables[this->levels-1][key];
    }
  if(val != NULL){
    this->debugger->debug("[S]: Symbol "+key+" is found at top level");
  }
  else{
    this->debugger->debug("[S]: Symbol "+key+" is not found at top level");
  }
  return val;
}
SymbolNode* SymbolTable::lookUpShadowedSymbol(const std::string& key)
/* looks up the parent levels and returns the content of the shadowed symbol if
it finds; otherwise, it returns NULL.
*/
{
  if(empty()){
    return NULL;
  }

  // declarations/initializations
  SymbolNode* val = NULL;
  bool found = false;
  int level = 2;

  //ignore the top level
  for(int level = this->levels - 2; level >= 0; --level){
    if(symTables[level].find(key) != symTables[level].end()){
      val = symTables[level][key];
      found = true;
    }
  }

  if(found){
    this->debugger->debug("[S]: Symbol "+key+" is found at level "+ std::to_string(level));
  }
  else{
    this->debugger->debug("[S]: Symbol "+key+" is not found at any parent level");
  }

  return val;
}
SymbolNode* SymbolTable::lookupSymbol(const std::string& key)
/* looks up the all levels and returns the content
if the key is found; otherwise, it returns NULL.
*/
{
  SymbolNode* val = NULL;
  if((val = lookupTopTable(key)) == NULL){
    val = lookUpShadowedSymbol(key);
  }
  return val;
}
void SymbolTable::writeFile(){
  if(empty()){
    return;
  }
  // declarations/initializations
  std::ofstream fout;
  std::map<std::string,SymbolNode*>::iterator iter;
  int level;

  fout.open(filename.c_str(), std::ofstream::app);
  fout << "Symbol Tables\n"
       << "====================================================" << std::endl;
  level = 1;

  // dump symbol tables
  for(int level = this->levels - 1; level >= 0; --level){
      fout << "[Symbol table #" << level << "]"<< std::endl;

      for(iter = this->symTables[level].begin(); iter != this->symTables[level].end(); ++iter){
        fout << "Symbol: " << iter->first << ", ";
        fout << (*iter->second).getSpec() << ", ";
        fout << (*iter->second).getPos() << ",";
        fout << "\n";
      }
      fout << "--------------------------------------------------" << std::endl;
    }
    fout << "====================================================\n\n" << std::endl;

  fout.close();
}
Debugger* SymbolTable::getDebugger() const{
  return this->debugger;
}
void SymbolTable::setFileName(const std::string filename){
  this->filename = filename;
}