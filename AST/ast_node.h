#ifndef __AST_NODE__H__
#define __AST_NODE__H__
#include <string>
#include <iostream>
#include "../SymbolNode.h"

// forward declaration
class ast_node;
class program_node;
class translation_unit_node;
class external_declaration_node;
class function_definition_node;
class declaration_node;
class declaration_list_node;
class init_declarator_node;
class declaration_specifiers_node;
class storage_class_specifier_node;
class type_specifier_node;
class type_qualifier_node;
class union_specifier_node;
class or_union_node;
class struct_declaration_node;
class qualifier_list_node;
class declarator_list_node;
class struct_declarator_node;
class enum_specifier_node;
class enumerator_list_node;
class enumerator_node;
class declarator_node;
class direct_declarator_node;
class pointer_node;
class type_list_node;
class parameter_list_node;
class parameter_declaration_node;
class identifier_list_node;
class initializer_node;
class initializer_list_node;
class type_name_node;
class abstract_declarator_node;
class statement_node;
class labeled_statement_node;
class expression_statement_node;
class compound_statement_node;
class statement_list_node;
class selection_statement_node;
class iteration_statement_node;
class jump_statement_node;
class expression_node;
class assignment_expression_node;
class assignment_operator_node;
class conditional_expression_node;
class constant_expression_node;
class logical_or_expression_node;
class logical_and_expression_node;
class inclusive_or_expression_node;
class exclusive_or_expression_node;
class equality_expression_node;
class relational_expression_node;
class shift_expression_node;
class additive_expression_node;
class multiplicative_expression_node;
class cast_expression_node;
class unary_expression_node;
class unary_operator_node;
class postfix_expression_node;
class primary_expression_node;
class expression_list_node;
class argument_expression_list_node;
class constant_node;
class string_node;
class identifier_node;

// Comment your name under nodes that you'll work on
// Assignments (roughly):
// 1-20 - Niki
// 21-40 - David
// 41-60 - Yuta
// 61-80 - Aaron

class ast_node {
  public:
    ast_node(){
      this->name = "";
      this->parent = NULL;
      this->source = "";
    };
    virtual ~ast_node(){};

    virtual void print()=0;
    virtual void generateCode()=0;

    // If we need polymorphism
    //virtual std::vector<ast_node*> getChildren();
    // Otherwise, have specialized children getters

  private:
    std::string name;
    ast_node* parent;
    std::string source;
};

class program_node : public ast_node {
  public:
  private:
};

class translation_unit_node : public ast_node {
  public:
  private:
};

class external_declaration_node : public ast_node {
  public:
  private:
};

class function_definition_node : public ast_node {
  public:
  private:
};

class declaration_node : public ast_node {
  public:
  private:
};

class declaration_list_node : public ast_node {
  public:
  private:
};

class init_declarator_node : public ast_node {
  public:
  private:
};

class declaration_specifiers_node : public ast_node {
  public:
  private:
};

class storage_class_specifier_node : public ast_node {
  public:
  private:
};

class type_specifier_node : public ast_node {
  public:
  private:
};

class type_qualifier_node : public ast_node {
  public:
  private:
};

class union_specifier_node : public ast_node {
  public:
  private:
};

class or_union_node : public ast_node {
  public:
  private:
};

class struct_declaration_node : public ast_node {
  public:
  private:
};

class qualifier_list_node : public ast_node {
  public:
  private:
};

class declarator_list_node : public ast_node {
  public:
  private:
};

class struct_declarator_node : public ast_node {
  public:
  private:
};

class enum_specifier_node : public ast_node {
  public:
  private:
};

class enumerator_list_node : public ast_node {
  public:
  private:
};

class enumerator_node : public ast_node {
  public:
  private:
};

class declarator_node : public ast_node {
  public:
  private:
};

class direct_declarator_node : public ast_node {
  public:
  private:
};

class pointer_node : public ast_node {
  public:
  private:
};

class type_list_node : public ast_node {
  public:
  private:
};

class parameter_list_node : public ast_node {
  public:
  private:
};

class parameter_declaration_node : public ast_node {
  public:
  private:
};

class identifier_list_node : public ast_node {
  public:
  private:
};

class initializer_node : public ast_node {
  public:
  private:
};

class initializer_list_node : public ast_node {
  public:
  private:
};

class type_name_node : public ast_node {
  public:
  private:
};

class abstract_declarator_node : public ast_node {
  public:
  private:
};

class statement_node : public ast_node {
  public:
  private:
};

class labeled_statement_node : public ast_node {
  public:
  private:
};

class expression_statement_node : public ast_node {
  public:
  private:
};

class compound_statement_node : public ast_node {
  public:
  private:
};

class statement_list_node : public ast_node {
  public:
  private:
};

class selection_statement_node : public ast_node {
  public:
  private:
};

class iteration_statement_node : public ast_node {
  public:
    /*
    iteration_statement_node();
    ~iteration_statement_node();

    void print() {
        // Print name
        // And more?
    }

    void generateCode() {
        // Don't worry about it for now
    }

    */
  private:
    //ast_node* a, b, c, d;
};

class jump_statement_node : public ast_node {
  public:
  private:
};

class expression_node: public ast_node {
public:
  expression_node();
  expression_node(assignment_expression_node* child);
  void addAssignmentExpr(assignment_expression_node* child);
  std::vector<assignment_expression_node*> getChildren() const;
  void print();
  void generateCode();
private:
  std::vector<assignment_expression_node*> children;
};

class assignment_expression_node : public ast_node {
  public:
    assignment_expression_node(conditional_expression_node* cond_expr);
    assignment_expression_node(unary_expression_node* unary_expr,
      assignment_operator_node* assign_op, assignment_expression_node* assign_expr);
    void init();
    void print();
    void generateCode();
  private:
    conditional_expression_node* cond_expr;
    unary_expression_node* unary_expr;
    assignment_operator_node* assign_op;
    assignment_expression_node* assign_expr;
    bool isConditionalExpr;
    int mode;
};

namespace AssignType{
  enum Type{EQUAL,MUL_ASSIGN,DIV_ASSIGN,MOD_ASSIGN,ADD_ASSIGN,SUB_ASSIGN,
    LEFT_ASSIGN,RIGHT_ASSIGN,AND_ASSIGN,XOR_ASSIGN,OR_ASSIGN};
}

class assignment_operator_node : public ast_node {
  public:
    assignment_operator_node();
    assignment_operator_node(AssignType::Type op);
    void print();
    void generateCode();
  private:
    int op;
};

class conditional_expression_node : public ast_node {
  public:
  private:
};

class constant_expression_node : public ast_node {
  public:
  private:
};

class logical_or_expression_node : public ast_node {
  public:
  private:
};

class logical_and_expression_node : public ast_node {
  public:
  private:
};

class inclusive_or_expression_node : public ast_node {
  public:
  private:
};

class exclusive_or_expression_node : public ast_node {
  public:
  private:
};

class equality_expression_node : public ast_node {
  public:
  private:
};

class relational_expression_node : public ast_node {
  public:
  private:
};

class shift_expression_node : public ast_node {
  public:
  private:
};

class additive_expression_node : public ast_node {
  public:
  private:
};

class multiplicative_expression_node : public ast_node {
  public:
  private:
};

class cast_expression_node : public ast_node {
  public:
  private:
};

namespace UnaryOpType{
  enum Type{ INC,DEC,SIZEOF };
}
class unary_expression_node : public ast_node {
  public:
    unary_expression_node(postfix_expression_node* postExpr);
    unary_expression_node(UnaryOpType::Type op, unary_expression_node* unaryExpr);
    void print();
    void generateCode();
  private:
    postfix_expression_node* postExpr;
    UnaryOpType::Type op;
    unary_expression_node* unaryExpr;
    int mode;
};

class unary_operator_node : public ast_node {
  public:
  private:
};
namespace PostOpType{
  enum Type{NONE,PERIOD,PTR_OP,INC,DEC};
}
class postfix_expression_node : public ast_node {
  public:
    postfix_expression_node(primary_expression_node* primayExpr);
    postfix_expression_node(postfix_expression_node* postExpr, expression_node* expr); // array
    postfix_expression_node(postfix_expression_node* postExpr); // array w/o expr
    postfix_expression_node(postfix_expression_node* postExpr, argument_expression_list_node* argExpr); // function call
    postfix_expression_node(postfix_expression_node* postExpr, PostOpType::Type op, std::string identifier); // ptr or dot
    postfix_expression_node(postfix_expression_node* postExpr, PostOpType::Type op); // inc or dec
    void init();
    void print();
    void generateCode();
  private:
    int mode;
    primary_expression_node* primayExpr;
    postfix_expression_node* postExpr;
    expression_node* expr;
    argument_expression_list_node* argExpr;
    PostOpType::Type op;
    std::string identifier;
};

class primary_expression_node: public ast_node {
  public:
    primary_expression_node(identifier_node* identifier);
    primary_expression_node(constant_node* constant);
    primary_expression_node(string_node* string);
    primary_expression_node(expression_node* expr);
    void init();
    void print();
    void generateCode();
  private:
    identifier_node* identifier;
    constant_node* constant;
    string_node* string;
    expression_node* expr;
    int mode;
};

class expression_list_node : public ast_node {
  public:
  private:
};

class argument_expression_list_node : public ast_node {
public:
  argument_expression_list_node();
  argument_expression_list_node(assignment_expression_node* child);
  void addAssignmentExpr(assignment_expression_node* child);
  std::vector<assignment_expression_node*> getChildren() const;
  void print();
  void generateCode();
private:
  std::vector<assignment_expression_node*> children;
};

namespace ConstType{
  enum Type {INT,CHAR,FLOAT,ENUM};
}

class constant_node : public ast_node {
public:
  constant_node(int ival);
  constant_node(char cval);
  constant_node(float fval);
  int getIval() const;
  char getCval() const;
  float getFval() const;
  void setIval(int ival);
  void setCval(char cval);
  void setFval(float fval);
  void print();
  void generateCode();

private:
  int ival;
  char cval;
  float fval;
  ConstType::Type type;
};

class string_node : public ast_node {
  public:
    string_node();
    string_node(std::string string_literal);
    std::string getStringLiteral();
    void setStringLiteral(std::string string_literal);
    void print();
    void generateCode();
  private:
    std::string string_literal;
};

class identifier_node: public ast_node {
  public:
    identifier_node(std::string name, SymbolNode* symnode);
    SymbolNode* getSymNode() const;
    void print();
    void generateCode();
  private:
    std::string id_name;
    SymbolNode *id_symnode;
};
#endif