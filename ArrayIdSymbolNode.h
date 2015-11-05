#ifndef __ARRAY_ID_SYMBOL_NODE__H__
#define __ARRAY_ID_SYMBOL_NODE__H__

#include "SymbolNode.h"
#include "AST/ast_node.h"

// Derived from SymbolNode
// The only difference will be a pointer to a constant_expression AST node
class ArrayIdSymbolNode : public SymbolNode {
  public:
    ArrayIdSymbolNode();
    ArrayIdSymbolNode(std::string, Spec* specifier, constant_expression_node*,
                      int = -1, bool = false);

    constant_expression_node* getArrSizeAstNode();

  private:
    // This is so that AST nodes for array accesses can have access to the size
    // of the array.
    constant_expression_node* arraySizeAstNode;
};

#endif //ifndef __ARRAY_ID_SYMBOL_NODE__H__

