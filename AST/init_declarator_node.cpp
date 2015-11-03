#include "ast_node.h"

init_declarator_node::init_declarator_node(){
}

init_declarator_node::init_declarator_node(declarator_node* decl, initializer_node* init){
    this->decl = decl;
    this->initializer = init;
}

void init_declarator_node::print(){
    visualizer.addNode(this->id,"init_declarator");
    visualizer.addEdge(this->pid,this->id);
    this->decl->setPID(this->id);
    this->decl.print();
    this->initializer->setPID(this->id);
    this->initializer.print();

}

void declaration_node::generateCode(){

}
