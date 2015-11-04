#include "ast_node.h"
constant_node::constant_node(int ival): ast_node(){
  this->type = ConstType::INT;
  this->ival = ival;
}
constant_node::constant_node(char cval): ast_node(){
  this->type = ConstType::CHAR;
  this->cval = cval;
}
constant_node::constant_node(float fval): ast_node(){
  this->type = ConstType::FLOAT;
  this->fval = fval;
}
int constant_node::getIval() const{
  return this->ival;
}
char constant_node::getCval() const{
  return this->cval;
}
float constant_node::getFval() const{
  return this->fval;
}
void constant_node::setIval(int ival){
  this->ival = ival;
}
void constant_node::setCval(char cval){
  this->cval = cval;
}
void constant_node::setFval(float fval){
  this->fval = fval;
}
void constant_node::print(){
  std::stringstream ss;
  switch(this->type){
    case ConstType::INT:
      ss << this->ival;
      visualizer.addNode(this->id,ss.str());
      visualizer.addEdge(this->pid,this->id);
    break;
    case ConstType::CHAR:
      ss << this->cval;
      visualizer.addNode(this->id,ss.str());
      visualizer.addEdge(this->pid,this->id);
    break;
    case ConstType::FLOAT:
      ss << this->fval;
      visualizer.addNode(this->id,ss.str());
      visualizer.addEdge(this->pid,this->id);
    break;
    default:
      std::cout <<"ERROR: Unknown constant type while print";
    break;
  }
}
Spec* constant_node::getSpec(){
  TypeBasic* typebasic = NULL;
  switch(this->type){
    case ConstType::INT:
      typebasic = new TypeBasic(SpecName::Int);
      typebasic->setValue(true);
    case ConstType::CHAR:
      typebasic = new TypeBasic(SpecName::Char);
      typebasic->setValue(true);
    case ConstType::FLOAT:
      typebasic = new TypeBasic(SpecName::Float);
      typebasic->setValue(true);
  }
  return typebasic;
}
void constant_node::generateCode(){

}