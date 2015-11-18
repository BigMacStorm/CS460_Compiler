#include "ast_node.h"
parameter_type_list_node::parameter_type_list_node(parameter_list_node* paramList){
  this->paramList = paramList;
}
parameter_type_list_node::~parameter_type_list_node(){
  if(this->paramList!=NULL){
    delete this->paramList;
  }
}
void parameter_type_list_node::print(){
  visualizer.debug("parameter_type_list");
  if(this->paramList!=NULL){
    this->paramList->setPID(this->pid);
    this->paramList->print();
  }
}
std::string parameter_type_list_node::generateCode(){
<<<<<<< HEAD
  if(this->paramList!=NULL){
    return this->paramList->generateCode();
  }
}
=======
  return this->paramList->generateCode();
}
>>>>>>> be7319b8b25d0e06628e992a04129cf8143d6907
