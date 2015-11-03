#include "ast_node.h"
postfix_expression_node::postfix_expression_node(primary_expression_node* primayExpr): ast_node(){
  init();
  this->primayExpr = primayExpr;
  this->mode = 0;
}
postfix_expression_node::postfix_expression_node(postfix_expression_node* postExpr, expression_node* expr): ast_node(){
  init();
  this->postExpr = postExpr;
  this->expr = expr;
  this->mode = 1;
}
postfix_expression_node::postfix_expression_node(postfix_expression_node* postExpr): ast_node(){
  init();
  this->postExpr = postExpr;
  this->mode = 2;
}
postfix_expression_node::postfix_expression_node(postfix_expression_node* postExpr, argument_expression_list_node* argExpr): ast_node(){
  init();
  this->postExpr = postExpr;
  this->argExpr = argExpr;
  this->mode = 3;
}
postfix_expression_node::postfix_expression_node(postfix_expression_node* postExpr, OpType::Type op, std::string identifier): ast_node(){
  init();
  this->postExpr = postExpr;
  this->op = op;
  this->identifier = identifier;
  this->mode = 4;
}
postfix_expression_node::postfix_expression_node(postfix_expression_node* postExpr, OpType::Type op): ast_node(){
  init();
  this->postExpr = postExpr;
  this->op = op;
  this->mode = 5;
}
void postfix_expression_node::init(){
  this->primayExpr = NULL;
  this->postExpr = NULL;
  this->expr = NULL;
  this->argExpr = NULL;
  this->op = OpType::NONE;
  this->identifier ="";
}
void postfix_expression_node::print(){
  switch(this->mode){
    case 0:
      if(primayExpr!=NULL){
        primayExpr->setPID(this->pid);
        primayExpr->print();
      }
    break;
    case 1:
      if(postExpr!=NULL){
        postExpr->setPID(this->pid);
        postExpr->print();
      }
      if(expr!=NULL){
        expr->setPID(this->pid);
        expr->print();
      }
    break;
    case 2:
      if(postExpr!=NULL){
        postExpr->setPID(this->pid);
        postExpr->print();
      }
    break;
    case 3:
      if(postExpr!=NULL){
        postExpr->setPID(this->pid);
        postExpr->print();
      }
      if(argExpr!=NULL){
        argExpr->setPID(this->pid);
        argExpr->print();
      }
    break;
    case 4:
      if(postExpr!=NULL){
        postExpr->setPID(this->pid);
        postExpr->print();
      }
    break;
    case 5:
      this->op_node_id = ast_node::getUID();
      if(this->op == OpType::INC){
        visualizer.addNode(this->op_node_id,"++");
      }
      else{
        visualizer.addNode(this->op_node_id,"--");
      }
      visualizer.addEdge(this->pid,this->op_node_id);

      if(postExpr!=NULL){
        postExpr->setPID(this->op_node_id);
        postExpr->print();
      }
    break;
    default:
      std::cout << "ERROR: unknown postfix expression type";
    break;
  }
}
void postfix_expression_node::generateCode(){

}