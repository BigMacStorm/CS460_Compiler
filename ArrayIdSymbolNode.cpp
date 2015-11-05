#include "ArrayIdSymbolNode.h"

ArrayIdSymbolNode::
ArrayIdSymbolNode() : SymbolNode() {
    this->arraySizeAstNode = NULL;
}

ArrayIdSymbolNode::
ArrayIdSymbolNode(std::string name, Spec* specifier,
                  constant_expression_node* arraySizeAstNode,
                  int line, bool defined)
    : SymbolNode(name, specifier, line, defined) {

    // Just assign the AST node
    this->arraySizeAstNode = arraySizeAstNode;
}

constant_expression_node* ArrayIdSymbolNode::
getArrSizeAstNode() {
    return arraySizeAstNode;
}
