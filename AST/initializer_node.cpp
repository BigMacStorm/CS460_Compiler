#include "ast_node.h"
initializer_node::initializer_node(assignment_expression_node* assignExpr): ast_node(){
  this->assignExpr = assignExpr;
}
initializer_node::initializer_node(initializer_list_node* initList){
  this->initList = initList;
}
void initializer_node::print(){
  visualizer.debug("initializer");
  if(this->assignExpr != NULL){
    this->assignExpr->setPID(this->pid);
    this->assignExpr->print();
  }
  if(this->initList != NULL){
    this->initList->setPID(this->pid);
    this->initList->print();
  }
}
Spec* initializer_node::getSpec(){
  if(this->assignExpr != NULL){
    return this->assignExpr->getSpec();
  }
  return new TypeBasic(SpecName::Int); // for now integer element only
}
/*
std::vector<Spec*> initializer_node::getSpecs(){
  std::vector<Spec*> specs;
  if(this->assignExpr != NULL){
    specs[0] = this->assignExpr->getSpec();
    return specs;
  }
  else if(this->initList!=NULL){
    return this->initList->getSpecs();
  }
  return specs;
}
*/
void initializer_node::generateCode(){

}