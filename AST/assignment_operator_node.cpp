#include "ast_node.h"
assignment_operator_node::assignment_operator_node(){}
assignment_operator_node::assignment_operator_node(AssignType::Type op){
  this->op = op;
}
void assignment_operator_node::print(){
  switch(this->op){
    case AssignType::EQUAL:
      std::cout << "=";
    break;
    case AssignType::MUL_ASSIGN:
      std::cout << "*=";
    break;
    case AssignType::DIV_ASSIGN:
      std::cout << "/=";
    break;
    case AssignType::MOD_ASSIGN:
      std::cout << "%%=";
    break;
    case AssignType::ADD_ASSIGN:
      std::cout << "+=";
    break;
    case AssignType::SUB_ASSIGN:
      std::cout << "-=";
    break;
    case AssignType::LEFT_ASSIGN:
      std::cout << "<<=";
    break;
    case AssignType::RIGHT_ASSIGN:
      std::cout << ">>=";
    break;
    case AssignType::AND_ASSIGN:
      std::cout << "&=";
    break;
    case AssignType::XOR_ASSIGN:
      std::cout << "^=";
    break;
    case AssignType::OR_ASSIGN:
      std::cout << "|=";
    break;
    default:
      std::cout << "ERROR Unknown assignment operator type";
    break;
  } // end switch
}
void assignment_operator_node::generateCode(){

}

