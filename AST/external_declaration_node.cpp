#include "ast_node.h"

external_declaration_node::external_declaration_node(){
}

external_declaration_node::external_declaration_node(function_definition_node* child){
    this -> functionChild = child;
    this -> declChild = NULL;
}

//add a declaration node child
external_declaration_node::external_declaration_node(declaration_node* child){
    this -> functionChild = NULL;
    this -> declChild = child;
}

//print name and name of child
external_declaration_node::void print(){
    //print own info
    if (functionChild == NULL) {
        declChild.print();
    }
    else
        functionChild.print();
}

//later
external_declaration_node::void generateCode(){

}
