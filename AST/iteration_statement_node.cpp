#include "ast_node.h"
iteration_statement_node::iteration_statement_node(IterType::Type iter_type, expression_node* expr1,
  statement_node* statement): ast_node(){
  init();
  this->iter_type = iter_type;
  this->expr1 = expr1;
  this->statement = statement;
  this->mode = 0;
}
iteration_statement_node::iteration_statement_node(IterType::Type iter_type, expression_node* expr1,
  expression_node* expr2,expression_node* expr3,statement_node* statement): ast_node(){
  init();
  this->iter_type = iter_type;
  this->expr1 = expr1;
  this->expr2 = expr2;
  this->expr3 = expr3;
  this->statement = statement;
  this->mode = 1;
}
void iteration_statement_node::init(){
  this->iter_type = IterType::NONE;
  this->expr1 = NULL;
  this->expr2 = NULL;
  this->expr3 = NULL;
  this->statement = NULL;
  this->mode = -1;
}
void iteration_statement_node::print(){
  visualizer.debug("iteration_statement");
  switch(this->mode){
    case 0:
      if(this->iter_type == IterType::WHILE){
        visualizer.addNode(this->id,"while");
        visualizer.addEdge(this->pid,this->id);
        if(this->expr1 != NULL){
          this->expr1->setPID(this->id);
          this->expr1->print();
        }
        if(this->statement != NULL){
          this->statement->setPID(this->id);
          this->statement->print();
        }
      }
      else if(this->iter_type == IterType::DO){
        visualizer.addNode(this->id,"do");
        visualizer.addEdge(this->pid,this->id);
        if(this->statement != NULL){
          this->statement->setPID(this->id);
          this->statement->print();
        }
        if(this->expr1 != NULL){
          this->expr1->setPID(this->id);
          this->expr1->print();
        }
      }
    break;
    case 1:
      if(this->expr1 != NULL){
        this->expr1->setPID(this->id);
        this->expr1->print();
      }
      if(this->expr2 != NULL){
        this->expr2->setPID(this->id);
        this->expr2->print();
      }
      if(this->expr3 != NULL){
        this->expr3->setPID(this->id);
        this->expr3->print();
      }
      if(this->statement != NULL){
        this->statement->setPID(this->id);
        this->statement->print();
      }
    break;
    default:
      std::cout << "ERROR: unknown iteration statement type" << std::endl;
    break;
  }
}
void iteration_statement_node::generateCode(){

}