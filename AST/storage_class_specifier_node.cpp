#include "ast_node.h"
storage_class_specifier_node::storage_class_specifier_node(): ast_node(){
}
storage_class_specifier_node::storage_class_specifier_node(StorageSpecifier::Store storeType): ast_node(){
  this->storeType = storeType;
}
void storage_class_specifier_node::print(){
  std::string type;
  switch(this->storeType){
    case StorageSpecifier::AUTO:
      type = "auto";
    break;
    case StorageSpecifier::REGISTER:
      type = "register";
    break;
    case StorageSpecifier::STATIC:
      type = "static";
    break;
    case StorageSpecifier::EXTERN:
      type = "extern";
    break;
    case StorageSpecifier::TYPEDEF:
      type = "typedef";
    break;
  }
  visualizer.addNode(this->id,type);
  visualizer.addEdge(this->pid,this->id);
}
void storage_class_specifier_node::generateCode(){
}