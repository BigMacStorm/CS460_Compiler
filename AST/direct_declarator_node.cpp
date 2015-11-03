#include "ast_node.h"
  direct_declarator_node::direct_declarator_node(std::string identifier): ast_node(){
    init();
    this->identifier = identifier;
  }

  direct_declarator_node::direct_declarator_node(DirectType::Type direct_type,
    direct_declarator_node* direct_declarator,
    constant_expression_node* constExpr): ast_node(){
    init();
    this->direct_type = direct_type;
    this->direct_declarator = direct_declarator;
    this->constExpr = constExpr;
  }

  direct_declarator_node::direct_declarator_node(DirectType::Type direct_type,
    direct_declarator_node* direct_declarator): ast_node(){
    init();
    this->direct_type = direct_type;
    this->direct_declarator = direct_declarator;
  }

  direct_declarator_node::direct_declarator_node(DirectType::Type direct_type,
    direct_declarator_node* direct_declarator, parameter_type_list_node* paramList): ast_node(){
    init();
    this->direct_type = direct_type;
    this->direct_declarator = direct_declarator;
    this->paramList = paramList;
  }

  direct_declarator_node::direct_declarator_node(DirectType::Type direct_type,
    direct_declarator_node* direct_declarator, identifier_list_node* idList): ast_node(){
    init();
    this->direct_type = direct_type;
    this->direct_declarator = direct_declarator;
    this->idList = idList;
  }

  void direct_declarator_node::init(){
    this->identifier = "";
    this->declarator = NULL;
    this->direct_declarator = NULL;
    this->constExpr = NULL;
    this->paramList = NULL;
    this->idList = NULL;
    this->direct_type = DirectType::NONE;
  }

  void direct_declarator_node::print(){
    switch(this->direct_type){
      case DirectType::NONE:
        visualizer.addNode(this->id,identifier);
        visualizer.addEdge(this->pid,this->id);
      break;
      case DirectType::ARRAY:
        visualizer.addNode(this->id,"[]");
        visualizer.addEdge(this->pid,this->id);

        if(this->direct_declarator!= NULL){
          this->direct_declarator->setPID(this->id);
          this->direct_declarator->print();
        }
        if(this->constExpr!= NULL){
          this->constExpr->setPID(this->id);
          this->constExpr->print();
        }
      break;
      case DirectType::FUNCTION:
        visualizer.addNode(this->id,"func");
        visualizer.addEdge(this->pid,this->id);

        if(this->direct_declarator!= NULL){
          this->direct_declarator->setPID(this->id);
          this->direct_declarator->print();
        }
        if(this->paramList!= NULL){
          this->paramList->setPID(this->id);
          this->paramList->print();
        }
      break;
      case DirectType::FUNCTION_CALL:
        visualizer.addNode(this->id,"func_call");
        visualizer.addEdge(this->pid,this->id);

        if(this->direct_declarator!= NULL){
          this->direct_declarator->setPID(this->id);
          this->direct_declarator->print();
        }
        if(this->idList!= NULL){
          this->idList->setPID(this->id);
          this->idList->print();
        }
      break;
    } // end switch
  }
  void direct_declarator_node::generateCode(){

  }
