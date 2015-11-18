#include "ast_node.h"

jump_statement_node::jump_statement_node(std::string identifier): ast_node(){
  init();
  this->identifier = identifier;
  this->mode = 0;
}
jump_statement_node::jump_statement_node(JumpType::Type jump_type): ast_node(){
  init();
  this->jump_type = jump_type;
  this->mode = 1;
}
jump_statement_node::jump_statement_node(expression_node* expr): ast_node(){
  init();
  this->expr = expr;
  this->mode = 2;
}
jump_statement_node::~jump_statement_node(){
  if(this->expr!=NULL){
    delete this->expr;
  }
}
void jump_statement_node::init(){
  this->identifier = "";
  this->expr = NULL;
  this->jump_type = JumpType::NONE;
  this->mode = -1;
}
void jump_statement_node::print(){
  visualizer.debug("jump_statement");
  switch(this->mode){
    case 0:
      visualizer.addNode(this->id,"goto");
      visualizer.addEdge(this->pid,this->id);
      this->label_id = ast_node::getUID();
      visualizer.addNode(this->label_id,this->identifier);
      visualizer.addEdge(this->id,this->label_id);
    break;
    case 1:
      if(this->jump_type==JumpType::RETURN){
        visualizer.addNode(this->id,"return");
        visualizer.addEdge(this->pid,this->id);
      }
      else if(this->jump_type==JumpType::CONTINUE){
        visualizer.addNode(this->id,"continue");
        visualizer.addEdge(this->pid,this->id);
      }
      else if(this->jump_type==JumpType::BREAK){
        visualizer.addNode(this->id,"break");
        visualizer.addEdge(this->pid,this->id);
      }
    break;
    case 2:
      visualizer.addNode(this->id,"return");
      visualizer.addEdge(this->pid,this->id);
      if(this->expr!=NULL){
        this->expr->setPID(this->id);
        this->expr->print();
      }
    break;
    default:
      std::cout << "ERROR: unknown jump statement type" << std::endl;
    break;
  }
}
std::string jump_statement_node::generateCode(){
<<<<<<< HEAD
=======
  std::string temp;
>>>>>>> be7319b8b25d0e06628e992a04129cf8143d6907
  switch(this->mode){
    case 0:
      codeGenerator.debug(" goto "+this->identifier);
    break;
    case 1:
      if(this->jump_type==JumpType::RETURN){
        codeGenerator.debug("return");
      }
      else if(this->jump_type==JumpType::CONTINUE){
        codeGenerator.debug("continue");
      }
      else if(this->jump_type==JumpType::BREAK){
        codeGenerator.debug("break");
      }
    break;
    case 2:
      if(this->expr!=NULL){
<<<<<<< HEAD
        return this->expr->generateCode();
      }
    break;
  }
}
=======
        temp = this->expr->generateCode();
        codeGenerator.debug("return " +temp+";\n");
      }
      else{
        codeGenerator.debug("return;\n");
      }
    break;
  }
  return "";
}
>>>>>>> be7319b8b25d0e06628e992a04129cf8143d6907
