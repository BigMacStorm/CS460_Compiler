#ifndef __DECLNODE__H__
#define __DECLNODE__H__
class Declarator{
 public:
  Declarator();
  Declarator* getParentDeclarator() const;
  SymbolNode* getSymNode() const;
 private:
  Declarator* parentDecl;
  SymbolNode* symnode;
};
#endif