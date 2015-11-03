#include "ast_node.h"
function_definition_node::function_definition_node(): ast_node(){
}
function_definition_node::function_definition_node(declaration_specifiers_node* specifiers,
                         declarator_node* decl,
                         declaration_list_node* decList,
                         compound_statement_node* compStmt): ast_node(){
  this->specifiers = specifiers;
  this->decl = decl;
  this->decList = decList;
  this->compStmt = compStmt;
}
void function_definition_node::print(){
  visualizer.addNode(this->id, "function_definition");
  visualizer.addEdge(this->pid, this->id);
  if(this->specifiers!=NULL){
    this->specifiers->setPID(this->id);
    this->specifiers->print();
  }
  if(this->decl!=NULL){
    this->decl->setPID(this->id);
    this->decl->print();
  }
  if(this->decList!=NULL){
    this->decList->setPID(this->id);
    this->decList->print();
  }
  if(this->compStmt!=NULL){
    this->compStmt->setPID(this->id);
    this->compStmt->print();
  }
}
void function_definition_node::generateCode(){
}