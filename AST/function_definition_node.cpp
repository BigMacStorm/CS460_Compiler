#include"ast_node.h"

function_definition_node::function_definition_node(){
}

function_definition_node::function_definition_node(declaration_specifiers_node* spec, declarator_node* dec, declaration_list_node* dlist, compound_statement_node* stmts){
    this->specifiers = spec;
    this->decl = dec;
    this->decList = dsist;
    this->compStmt = stmts;
}

void function_definition_node::print(){
    visualizer.addNode(this->id,"function_definition");
    visualizer.addEdge(this->pid,this->id);
       
    this->specifiers->setPID(this->id);
    this->specifiers.print();
    this->decl->setPID(this->id);
    this->decl.print();
    this->decList->setPID(this->id);
    this->decList.print();
    this->compStmt->setPID(this->id);
    this->compStmt.print();
}

void function_definition_node::generateCode(){

}
