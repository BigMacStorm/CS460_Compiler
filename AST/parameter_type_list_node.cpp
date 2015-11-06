#include "ast_node.h"
parameter_type_list_node::parameter_type_list_node(parameter_list_node* paramList){
  this->paramList = paramList;
}
void parameter_type_list_node::print(){
  visualizer.debug("parameter_type_list");
  if(this->paramList!=NULL){
    this->paramList->setPID(this->pid);
    this->paramList->print();
  }
}
void parameter_type_list_node::generateCode(){

}