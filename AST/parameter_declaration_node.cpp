#include "ast_node.h"
parameter_declaration_node::parameter_declaration_node(declaration_specifiers_node* declSpec): ast_node(){
  this->declSpec = declSpec;
}
parameter_declaration_node::parameter_declaration_node(declaration_specifiers_node* declSpec, declarator_node* decl): ast_node(){
  this->declSpec = declSpec;
  this->decl = decl;
}
parameter_declaration_node::parameter_declaration_node(declaration_specifiers_node* declSpec, abstract_declarator_node* absDecl): ast_node(){
  this->declSpec = declSpec;
  this->absDecl = absDecl;
}
parameter_declaration_node::~parameter_declaration_node(){
  if(this->declSpec!=NULL){
    delete this->declSpec;
  }
  if(this->decl!=NULL){
    delete this->decl;
  }
  if(this->absDecl!=NULL){
    delete this->absDecl;
  }
}
void parameter_declaration_node::print(){
  visualizer.debug("parameter_declaration");
  visualizer.addNode(this->id,"param");
  visualizer.addEdge(this->pid,this->id);

  if(this->decl != NULL){
    if(this->declSpec != NULL){
      this->declSpec->setPID(this->id);
      this->declSpec->print();
    }
    this->decl->setPID(this->id);
    this->decl->print();
  }
  else if(this->absDecl != NULL){
    if(this->declSpec != NULL){
      this->declSpec->setPID(this->id);
      this->declSpec->print();
    }
    this->absDecl->setPID(this->id);
    this->absDecl->print();
  }
}
void parameter_declaration_node::generateCode(){

}