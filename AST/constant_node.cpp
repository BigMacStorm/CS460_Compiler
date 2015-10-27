#include "ast_node.h"
constant_node::constant_node(int ival){
  this->type = ConstType::INT;
  this->ival = ival;
}
constant_node::constant_node(char cval){
  this->type = ConstType::CHAR;
  this->cval = cval;
}
constant_node::constant_node(float fval){
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
  switch(this->type){
    case ConstType::INT:
      std::cout << this->ival;
    break;
    case ConstType::CHAR:
      std::cout << this->cval;
    break;
    case ConstType::FLOAT:
      std::cout << this->fval;
    break;
    default:
      std::cout <<"ERROR: Unknown constant type";
    break;
  }
}
void constant_node::generateCode(){

}