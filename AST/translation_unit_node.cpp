#include "ast_node.h"

translation_unit_node::translation_unit_node(){
}

translation_unit_node::translation_unit_node(external_declaration_node* child){
    this -> children.push_back(child);
}

//add more external declaration nodes as children
translation_unit_node::void addExternDecl(external_declaration_node* child){
    this -> children.push_back(child);
}

//return all of the children of the node
translation_unit_node::std::vector<external_declaration_node*> getChildren() const{
    return this -> children;
}

//print the name of this node followed by children (graphviz readable?)
translation_unit_node::void print(){
    for(int child = 0; child < this->children.size(); child++){
    this -> children[child].print();
  }
}

//implemented later
translation_unit_node::void generateCode(){
}
