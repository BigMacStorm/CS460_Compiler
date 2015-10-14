#include "SymbolTable.h"
SymbolTable* SymbolTable::instance = NULL;

SymbolTable::SymbolTable(){
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
void SymbolTable::pushTable(std::map<std::string,SymbolNode*> newSymTable){
  this->symTables.push(newSymTable);
}

void SymbolTable::pushTable(){
  std::map<std::string,SymbolNode*> newSymTable;
  this->symTables.push(newSymTable);
  this->debugger->debug("[S]: A new symbol table is pushed on ===============");
}

void SymbolTable::popTable(){
  this->symTables.pop();
  this->debugger->debug("[S]: The top symbol table is popped off ============");
}

bool SymbolTable::insertSymbol(const std::string& key, SymbolNode* val){
  SymbolNode* content;

  if(this->symTables.empty()){
    return false;
  }

  content = lookupTopTable(key);
  this->symTables.top()[key] = val;
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
  // declarations/initializations
  std::map<std::string,SymbolNode*> currentSymTable = this->symTables.top();
  SymbolNode * val = NULL;

  if(this->symTables.empty()){
    return NULL;
  }
  if(currentSymTable.find(key) != currentSymTable.end()){
      val = currentSymTable[key];
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
  // declarations/initializations
  std::stack< std::map<std::string,SymbolNode*> > tmpSymTables;
  std::map<std::string,SymbolNode*> currentSymTable;
  SymbolNode* val = NULL;
  bool found = false;
  int level = 2;

  if(this->symTables.empty()){
    return NULL;
  }

  // pop off the top level
  currentSymTable = this->symTables.top();
  this->symTables.pop();
  tmpSymTables.push(currentSymTable);

  while(!found && !this->symTables.empty()){
    currentSymTable = this->symTables.top();
    if(currentSymTable.find(key) != currentSymTable.end()){
      val = currentSymTable[key];
      found = true;
    }
    tmpSymTables.push(currentSymTable);
    this->symTables.pop();
    level++;
  }
  while(!tmpSymTables.empty()){
    this->symTables.push(tmpSymTables.top());
    tmpSymTables.pop();
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

  // declarations/initializations
  std::ofstream fout;
  std::stack< std::map<std::string,SymbolNode*> > tmpSymTables;
  std::map<std::string,SymbolNode*> currentSymTable;
  std::map<std::string,SymbolNode*>::iterator iter;
  Spec* spec;
  int level;

  if(this->symTables.empty()){
    return;
  }

  fout.open(filename.c_str(), std::ofstream::app);
  fout << "Symbol Tables\n"
       << "====================================================" << std::endl;
  level = 1;

  // dump symbol tables
  while(!this->symTables.empty()){
    currentSymTable = this->symTables.top();
    fout << "[Symbol table #" << level << "]"<< std::endl;

    for(iter = currentSymTable.begin(); iter != currentSymTable.end(); ++iter){
      spec = (*iter->second).getSpec();
      fout << "Symbol: " << iter->first << "; ";
      if(spec != NULL){
        fout << spec->getSpecStr();
      }
      fout << "Position: " << (*iter->second).getPos() << ";";
      fout << "\n";
    }
    fout << "--------------------------------------------------" << std::endl;

    tmpSymTables.push(currentSymTable);
    this->symTables.pop();
    level++;
  }
  fout << "====================================================\n\n" << std::endl;

  while(!tmpSymTables.empty()){
    this->symTables.push(tmpSymTables.top());
    tmpSymTables.pop();
  }
  fout.close();
}
Debugger* SymbolTable::getDebugger() const{
  return this->debugger;
}
void SymbolTable::setFileName(const std::string filename){
  this->filename = filename;
}