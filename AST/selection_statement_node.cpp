#include "ast_node.h"
selection_statement_node::selection_statement_node(SelecType::Type selec_type, expression_node* expr,
  statement_node* statement1,statement_node* statement2): ast_node(){
  this->selec_type = selec_type;
  this->expr = expr;
  this->statement1 = statement1;
  this->statement2 = statement2;
}
selection_statement_node::~selection_statement_node(){
  if(this->expr!=NULL){
    delete this->expr;
  }
  if(this->statement1!=NULL){
    delete this->statement1;
  }
  if(this->statement2!=NULL){
    delete this->statement2;
  }
}
void selection_statement_node::init(){
  this->selec_type = SelecType::NONE;
  this->expr = NULL;
  this->statement1 = NULL;
  this->statement2 = NULL;
}
void selection_statement_node::print(){
  visualizer.debug("selection_statement");
  if(this->selec_type == SelecType::IF){
    visualizer.addNode(this->id,"if");
    visualizer.addEdge(this->pid,this->id);
    if(this->expr != NULL){
      this->expr->setPID(this->id);
      this->expr->print();
    }
    if(this->statement1 != NULL){
      this->statement1->setPID(this->id);
      this->statement1->print();
    }
    if(this->statement2 != NULL){
      this->else_id = ast_node::getUID();
      visualizer.addNode(this->else_id,"else");
      visualizer.addEdge(this->id,this->else_id);
      this->statement2->setPID(this->else_id);
      this->statement2->print();
    }
  }
  else if(this->selec_type == SelecType::SWITCH){
    visualizer.addNode(this->id,"switch");
    visualizer.addEdge(this->pid,this->id);
    if(this->expr != NULL){
      this->expr->setPID(this->id);
      this->expr->print();
    }
    if(this->statement1 != NULL){
      this->statement1->setPID(this->id);
      this->statement1->print();
    }
  }
}
void selection_statement_node::generateCode(){
}