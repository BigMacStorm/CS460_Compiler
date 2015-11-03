#include "ast_node.h"
initializer_node::initializer_node(assignment_expression_node* assignExpr): ast_node(){
  this->assignExpr = assignExpr;
}
initializer_node::initializer_node(initializer_list_node* initList){
  this->initList = initList;
}
void initializer_node::print(){
  if(this->assignExpr != NULL){
    this->assignExpr->setPID(this->pid);
    this->assignExpr->print();
  }
  if(this->initList != NULL){
    this->initList->setPID(this->pid);
    this->initList->print();
  }
}
void initializer_node::generateCode(){

}