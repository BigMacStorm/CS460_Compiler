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
Spec* postfix_expression_node::getSpec(){
  switch(this->mode){
    case 0:
      return this->primayExpr->getSpec();
    break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
      if(this->postExpr!=NULL){
        return this->postExpr->getSpec();
      }
      return NULL;

    default:
      return NULL;
  }
}
Spec * postfix_expression_node::getSpecForIdentifier(){
  Spec* spec = this->postExpr->getSpec();
  SpecName::TypeKind kind = spec->getTypeKind();

  // constant numerical value (not identifier)
  if(spec->isValue()){
    return spec;
  }

  // basic
  if(kind == SpecName::Basic){
   return spec;
  }

  // array
  if(kind == SpecName::Array){
    // check if the size is int
    if(this->expr!=NULL){
      if(this->expr->getSpec()->getBaseType() != SpecName::Int){
        error("[a] ERROR: array size must be integer");
      }
    }
     // bounds checking
     return new TypeBasic(spec->getBaseType());
   }
  // pointer
  if(kind == SpecName::Pointer){
   return new TypeBasic(spec->getBaseType());
  }
  // function
  if(kind == SpecName::Function){
    // function argument type checking
   return new TypeBasic(spec->getBaseType());
  }
  return NULL;
}
void postfix_expression_node::generateCode(){

}