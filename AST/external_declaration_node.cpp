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

//print name and name of child
void external_declaration_node::print(){
    //print own info
    if (functionChild == NULL) {
        declChild->print();
    }
    else
        functionChild->print();
}

//later
void external_declaration_node::generateCode(){

}
