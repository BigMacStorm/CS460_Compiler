#include "ast_node.h"

external_declaration_node::external_declaration_node(): ast_node(){
}

external_declaration_node::external_declaration_node(
  function_definition_node* child): ast_node(){
    this -> functionChild = child;
    this -> declChild = NULL;
}

//add a declaration node child
external_declaration_node::external_declaration_node(
  declaration_node* child): ast_node(){
    this -> functionChild = NULL;
    this -> declChild = child;
}

external_declaration_node::~external_declaration_node(){
  if(this->declChild!=NULL){
    delete this->declChild;
  }
  if(this->functionChild!=NULL){
    delete this->functionChild;
  }
}

//print name and name of child
void external_declaration_node::print(){
    visualizer.debug("external_declaration");
    //print own info
    if (this->functionChild == NULL) {
        this->declChild->setPID(this->pid);
        this->declChild->print();
    }
    else{
      this->functionChild->setPID(this->pid);
      this->functionChild->print();
    }
}

//later
void external_declaration_node::generateCode(){

}
