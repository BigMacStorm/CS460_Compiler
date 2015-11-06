#include "ast_node.h"
additive_expression_node::additive_expression_node(multiplicative_expression_node* multiExpr): ast_node(){
  init();
  this->multiExpr = multiExpr;
  this->mode = 0;
}
additive_expression_node::additive_expression_node(additive_expression_node* addExpr, OpType::Type op, multiplicative_expression_node* multiExpr): ast_node(){
  init();
  this->addExpr = addExpr;
  this->op = op;
  this->multiExpr = multiExpr;
  this->mode = 1;
}
void additive_expression_node::init(){
  this->addExpr = NULL;
  this->multiExpr = NULL;
  this->op = OpType::NONE;
  this->mode = -1;
}
void additive_expression_node::print(){
    visualizer.debug("additive_expression");
    switch(this->mode){
      case 0:
        if(this->multiExpr!=NULL){
          this->multiExpr->setPID(this->pid);
          this->multiExpr->print();
        }
      break;
      case 1:
        if(this->op == OpType::PLUS){
          visualizer.addNode(this->id,"+");
        }else{
          visualizer.addNode(this->id,"-");
        }
        visualizer.addEdge(this->pid,this->id);

        if(this->addExpr!=NULL){
          this->addExpr->setPID(this->id);
          this->addExpr->print();
        }
        if(this->multiExpr!=NULL){
          this->multiExpr->setPID(this->id);
          this->multiExpr->print();
        }
      break;
      default:
        std::cout << "ERROR: unknown additive expression type" << std::endl;
      break;
    }
  }
Spec* additive_expression_node::getSpec(){
  SpecName::BaseType left, right;
  switch(this->mode){
    case 0:
      if(this->multiExpr!=NULL){
        return this->multiExpr->getSpec();
      }
      return NULL;

    case 1:
      if(this->addExpr!=NULL){
        left = this->multiExpr->getSpec()->getBaseType();
      }
      if(this->multiExpr!=NULL){
        right = this->multiExpr->getSpec()->getBaseType();
      }
      if(this->op == OpType::PLUS){
        if(left != right){
          // implicit conversion to float
          if(left == SpecName::Float || right == SpecName::Float){
            warning("[A] WARNING: implicit conversion to 'float'");
            return new TypeBasic(SpecName::Float);
          }
        }
        return this->addExpr->getSpec();
      } // end *

      else{ // -
        if(left != right){
          // implicit conversion to float
          if(left == SpecName::Float || right == SpecName::Float){
            warning("[A] WARNING: implicit conversion to 'float'");
            return new TypeBasic(SpecName::Float);
          }
        }
        return this->addExpr->getSpec();
      } // end /

      return NULL;

    default:
      return NULL;
  }
}
void additive_expression_node::generateCode(){

}
