#include "ast_node.h"
struct_declarator_node::struct_declarator_node(declarator_node* decl, constant_expression_node* constExpr): ast_node(){
  this->decl = decl;
  this->constExpr = constExpr;
}
void struct_declarator_node::print(){
  visualizer.debug("struct_declarator");
  visualizer.addNode(this->id,"struct_declarator");
  visualizer.addEdge(this->pid,this->id);
  if(this->decl!=NULL){
    this->decl->setPID(this->id);
    this->decl->print();
  }
  if(this->constExpr!=NULL){
    this->constExpr->setPID(this->id);
    this->constExpr->print();
  }
}
void struct_declarator_node::generateCode(){
}