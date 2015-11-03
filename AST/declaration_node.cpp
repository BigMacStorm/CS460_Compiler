#include "ast_node.h"

declaration_node::declaration_node(){
}

declaration_node::declaration_node(declaration_specifiers_node* spec, init_declarator_list_node* dlist){
    this->specifier = spec;
    this->decList = dlist;
}

void declaration_node::print(){
    visualizer.addNode(this->id,"declaration");
    visualizer.addEdge(this->pid,this->id);
    this->specifiers->setPID(this->id);
    this->specifiers.print();
    this->decList->setPID(this->id);
    this->decList.print();

}

void declaration_node::generateCode(){

}
