#include "ast_node.h"
statement_node::statement_node(labeled_statement_node* labelStmt): ast_node(){
  init();
  this->labelStmt = labelStmt;
  this->mode = 0;
 }
statement_node::statement_node(compound_statement_node* compStmt): ast_node(){
  init();
  this->compStmt = compStmt;
  this->mode = 1;
 }
statement_node::statement_node(expression_statement_node* exprStmt): ast_node(){
  init();
  this->exprStmt = exprStmt;
  this->mode = 2;
 }
statement_node::statement_node(selection_statement_node* selectStmt): ast_node(){
  init();
  this->selectStmt = selectStmt;
  this->mode = 3;
 }
statement_node::statement_node(iteration_statement_node* iterStmt): ast_node(){
  init();
  this->iterStmt = iterStmt;
  this->mode = 4;
 }
statement_node::statement_node(jump_statement_node* jumpStmt): ast_node(){
  init();
  this->jumpStmt = jumpStmt;
  this->mode = 5;
}
statement_node::~statement_node(){
  if(this->labelStmt!=NULL){
    delete this->labelStmt;
  }
  if(this->compStmt!=NULL){
    delete this->compStmt;
  }
  if(this->exprStmt!=NULL){
    delete this->exprStmt;
  }
  if(this->selectStmt!=NULL){
    delete this->selectStmt;
  }
  if(this->iterStmt!=NULL){
    delete this->iterStmt;
  }
  if(this->jumpStmt!=NULL){
    delete this->jumpStmt;
  }
}
void statement_node::init(){
  labelStmt = NULL;
  compStmt = NULL;
  exprStmt = NULL;
  selectStmt = NULL;
  iterStmt = NULL;
  jumpStmt = NULL;
  mode = -1;
}
void statement_node::print(){
  visualizer.debug("statement");
  visualizer.addNode(this->id,"statement");
  visualizer.addEdge(this->pid,this->id);
  switch(this->mode){
    case 0:
      if(this->labelStmt != NULL){
        this->labelStmt->setPID(this->id);
        this->labelStmt->print();
      }
    break;
    case 1:
      if(this->compStmt != NULL){
        this->compStmt->setPID(this->id);
        this->compStmt->print();
      }
    break;
    case 2:
      if(this->exprStmt != NULL){
        this->exprStmt->setPID(this->id);
        this->exprStmt->print();
      }
    break;
    case 3:
      if(this->selectStmt != NULL){
        this->selectStmt->setPID(this->id);
        this->selectStmt->print();
      }
    break;
    case 4:
      if(this->iterStmt != NULL){
        this->iterStmt->setPID(this->id);
        this->iterStmt->print();
      }
    break;
    case 5:
      if(this->jumpStmt != NULL){
        this->jumpStmt->setPID(this->id);
        this->jumpStmt->print();
      }
    break;
  }
}
std::string statement_node::generateCode(){
  switch(this->mode){
    case 0:
      this->labelStmt->generateCode();
    break;
    case 1:
      this->compStmt->generateCode();
    break;
    case 2:
      return this->exprStmt->generateCode();
    break;
    case 3:
      this->selectStmt->generateCode();
    break;
    case 4:
      this->iterStmt->generateCode();
    break;
    case 5:
      this->jumpStmt->generateCode();
    break;
  }
  return "";
}