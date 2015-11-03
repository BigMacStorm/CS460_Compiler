#include "ast_node.h"
init_declarator_list_node::init_declarator_list_node(){
}

init_declarator_list_node::init_declarator_list_node(init_declarator_node* child){
    this->children.push_back(child);
}

void init_declarator_list_node::addDecl(init_declarator_node* child){
    this->children.push_back(child);
}

std::vector<init_declarator_node*> init_declarator_list_node::getChildren() const{
    return this->children;
}

void init_declarator_list_node::print(){
    visualizer.addNode(this->id,"init_declarator_list");
    visualizer.addEdge(this->pid,this->id);
    for(int child = 0; child < this->children.size(); child++){
    if(this->children[child]!=NULL){
        this->children[child]->setPID(this->id);
        this->children[child]->print();
    }

}

void declaration_list_node::generateCode(){
}
