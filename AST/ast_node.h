#ifndef __AST_NODE__H__
#define __AST_NODE__H__
#include <string>
#include <iostream>
#include "../SymbolNode.h"

// Comment your name under nodes that you'll work on
// Assignments (roughly):
// 1-20 - Niki
// 21-40 - David
// 41-60 - Yuta
// 61-80 - Aaron

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
class and_expression_node;
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

namespace OpType{
  enum Type{NONE, PERIOD,PTR_OP,
            INC, DEC, SIZEOF,
            MUL, DIV, PLUS, MINUS,
            ASTERISK, MOD, PIPE,
            AND, UP_CARROT, TILDE, BANG,
            LEFT_OP, RIGHT_OP, QUESTION,
            L, G, GE, LE, EQ, NE, AND_OP, OR_OP
          };
}

class ast_node {
  public:
    ast_node(){
      this->name = "";
      this->parent = NULL;
      this->source = "";
    };
    virtual ~ast_node(){
      //delete children then itself, is this defined in each specific class?
    };

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

//may not need this node as its a unit production program -> translation_unit
class program_node : public ast_node {
  public:
    program_node();
    program_node(translation_unit_node* child);
    //should only be on translation unit node so this add function could be removed ??
    void addTranslationUnit(translation_unit_node* child);
    translation_unit_node* getChild() const;
  void print();
  void generateCode();
  private:
    translation_unit_node* translationUnit;
};

class translation_unit_node : public ast_node {
  public:
    translation_unit_node();
    translation_unit_node(external_declaration_node* child);
    void addExternDecl(external_declaration_node* child);
    std::vector<external_declaration_node*> getChildren() const;
    void print();
    void generateCode();
  private:
    std::vector<external_declaration_node*> children;
};

class external_declaration_node : public ast_node {
  public:
    external_declaration_node();
    external_declaration_node(function_definition_node* child);
    external_declaration_node(declaration_node* child);
    void print();
    void generateCode();
  private:
    function_definition_node* functionChild;
    declaration_node* declChild;
};

class function_definition_node : public ast_node {
  public:
    function_definition_node();
    function_definition_node(declaration_specifiers_node* spec,
                             declarator_node* dec,
                             declaration_list_node* dlist,
                             compound_statement_node* stmts);
    void print();
    void generateCode();
  private:
    declaration_specifiers_node* specifiers;
    declarator_node* decl;
    declaration_list_node* decList;
    compound_statement_node* compStmt;
};

class declaration_node : public ast_node {
  public:
    declaration_node();
    declaration_node(declaration_specifiers_node* spec, init_declarator_list_node* dlist);
    void print();
    void generateCode();
  private:
    declaration_specifiers_node* specifier;
    init_declarator_list_node* decList;
};

class declaration_list_node : public ast_node {
  public:
    declaration_list_node();
    declaration_list_node(declaration_node* child);
    void addDecl(declaration_node* child);
    std::vector<declaration_node*> getChildren() const;
    void print();
    void generateCode();
  private:
    std::vector<declaration_node*> children;
};

class init_declarator_node : public ast_node {
  public:
  private:
};

class init_declarator_list_node : public ast_node {
  public:
  private:
};

class declaration_specifiers_node : public ast_node {
  public:
  private:
};

namespace StorageSpecifier{
  enum Store{AUTO, REGISTER, STATIC, EXTERN, TYPEDEF};
}
class storage_class_specifier_node : public ast_node {
  public:
    type_specifier_node();
    type_specifier_node(StorageSpecifier::Store storeType);
    void print();
    void generateCode();
  private:
    int storeType;
};

//could be enum for type_specifiers but should also includes struct and union (extra credit)
namespace TypeSpecifier{
  enum Type{VOID, CHAR, SHORT, INT, LONG, FLOAT, DOUBLE, SIGNED
            UNSIGNED, TYPEDEF_NAME};
}
class type_specifier_node : public ast_node {
  public:
    type_specifier_node();
    type_specifier_node(TypeSpecifier::Type type);
    void print();
    void generateCode();
  private:
    int type;
};

namespace TypeQualifier{
  enum Qual{CONST, VOLATILE};
}
class type_qualifier_node : public ast_node {
  public:
    type_specifier_node();
    type_specifier_node(TypeQualifier::Qual qual);
    void print();
    void generateCode();
  private:
    int qual;
};

/* 
leaving struct related classes commented out unless we decide to implement them

class struct_or_union_specifier_node : public ast_node {
  public:
  private:
};

class struct_or_union_node : public ast_node {
  public:
  private:
};

class struct_declaration_list_node : public ast_node {
  public:
  private:
};

class struct_declaration_node : public ast_node {
  public:
  private:
};

class struct_declarator_list_node : public ast_node {
  public:
  private:
};

class struct_declarator_node : public ast_node {
  public:
  private:
};
*/

class specifier_qualifier_list_node : public ast_node {
  public:
    qualifier_list_node();
    qualifier_list_node(type_specifier_node* child);
    //type is ast_node as it should accept both type specifiers and quantifiers
    void addTypeSpecifier(ast_node* child);
    //only one vector as order of type specifiers and quantifiers should be preserved??
    std::vector<ast_node*> getChildren() const;
    void print();
    void generateCode();
  private:
    std::vector<ast_node*> children;
};

class declarator_list_node : public ast_node {
  public:
  private:
};

class enum_specifier_node : public ast_node {
  public:
    enum_specifier_node();
    //init as null if not used
    enum_specifier_node(identifier_node* id, enumerator_list_node* enm);
  private:
    enumerator_list_node* enumList
    identifier_node* id
};

class enumerator_list_node : public ast_node {
  public:
    enumerator_list_node();
    enumerator_list_node(enum_specifier_node* child);
    void addEnumSpec(enum_specifier_node* child);
    std::vector<enum_specifier_node*> getChildren() const;
    void print();
    void generateCode();
  private:
    std::vector<enum_specifier_node*> children;
};//

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

class constant_expression_node : public ast_node {
  public:
    constant_expression_node(conditional_expression_node* condExpr);
    void init();
    void print();
    void generateCode();
  private:
    conditional_expression_node* condExpr;
};

class conditional_expression_node : public ast_node {
  public:
    conditional_expression_node(logical_or_expression_node* logOrExpr);
    conditional_expression_node(logical_or_expression_node* logOrExpr, expression_node* expr, conditional_expression_node* condExpr);
    void init();
    void print();
    void generateCode();
  private:
    conditional_expression_node* condExpr;
    expression_node* expr;
    logical_or_expression_node* logOrExpr;
    int mode;
};

class logical_or_expression_node : public ast_node {
  public:
    logical_or_expression_node(logical_and_expression_node* logAndExpr);
    logical_or_expression_node(logical_or_expression_node* logOrExpr, OpType::Type op, logical_and_expression_node* logAndExpr);
    void init();
    void print();
    void generateCode();
  private:
    logical_and_expression_node* logAndExpr;
    logical_or_expression_node* logOrExpr;
    OpType::Type op;
    int mode;
};

class logical_and_expression_node : public ast_node {
  public:
    logical_and_expression_node(inclusive_or_expression_node* iorExpr);
    logical_and_expression_node(logical_and_expression_node* logAndExpr, OpType::Type op, inclusive_or_expression_node* iorExpr);
    void init();
    void print();
    void generateCode();
  private:
    inclusive_or_expression_node* iorExpr;
    logical_and_expression_node* logAndExpr;
    OpType::Type op;
    int mode;
};

class inclusive_or_expression_node : public ast_node {
  public:
    inclusive_or_expression_node(exclusive_or_expression_node* exorExpr);
    inclusive_or_expression_node(inclusive_or_expression_node* iorExpr, OpType::Type op, exclusive_or_expression_node* exorExpr);
    void init();
    void print();
    void generateCode();
  private:
    exclusive_or_expression_node* exorExpr;
    inclusive_or_expression_node* iorExpr;
    OpType::Type op;
    int mode;
};

class exclusive_or_expression_node : public ast_node {
  public:
    exclusive_or_expression_node(and_expression_node* andExpr);
    exclusive_or_expression_node(exclusive_or_expression_node* exorExpr, OpType::Type op, and_expression_node* andExpr);
    void init();
    void print();
    void generateCode();
  private:
    and_expression_node* andExpr;
    exclusive_or_expression_node* exorExpr;
    OpType::Type op;
    int mode;
};
class and_expression_node : public ast_node {
  public:
    and_expression_node(equality_expression_node* equalExpr);
    and_expression_node(and_expression_node* andExpr, OpType::Type op, equality_expression_node* equalExpr);
    void init();
    void print();
    void generateCode();
  private:
    and_expression_node* andExpr;
    equality_expression_node* equalExpr;
    OpType::Type op;
    int mode;
};

class equality_expression_node : public ast_node {
  public:
    equality_expression_node(relational_expression_node* relExpr);
    equality_expression_node(equality_expression_node* equalExpr, OpType::Type op, relational_expression_node* relExpr);
    void init();
    void print();
    void generateCode();
  private:
    equality_expression_node* equalExpr;
    relational_expression_node* relExpr;
    OpType::Type op;
    int mode;
};

class relational_expression_node : public ast_node {
  public:
    relational_expression_node(shift_expression_node* shiftExpr);
    relational_expression_node(relational_expression_node* relExpr, OpType::Type op, shift_expression_node* shiftExpr);
    void init();
    void print();
    void generateCode();
  private:
    relational_expression_node* relExpr;
    shift_expression_node* shiftExpr;
    OpType::Type op;
    int mode;
};

class shift_expression_node : public ast_node {
  public:
    shift_expression_node(additive_expression_node* addExpr);
    shift_expression_node(shift_expression_node* shiftExpr, OpType::Type op, additive_expression_node* addExpr);
    void init();
    void print();
    void generateCode();
  private:
    shift_expression_node* shiftExpr;
    additive_expression_node* addExpr;
    OpType::Type op;
    int mode;
};

class additive_expression_node : public ast_node {
  public:
    additive_expression_node(multiplicative_expression_node* multiExpr);
    additive_expression_node(additive_expression_node* addExpr, OpType::Type op, multiplicative_expression_node* multiExpr);
    void init();
    void print();
    void generateCode();
  private:
    multiplicative_expression_node* multiExpr;
    additive_expression_node* addExpr;
    OpType::Type op;
    int mode;
};

class multiplicative_expression_node : public ast_node {
  public:
    multiplicative_expression_node(cast_expression_node* castExpr);
    multiplicative_expression_node(multiplicative_expression_node* multiExpr, OpType::Type op, cast_expression_node* castExpr);
    void init();
    void print();
    void generateCode();
  private:
    cast_expression_node* castExpr;
    multiplicative_expression_node* multiExpr;
    OpType::Type op;
    int mode;
};

class cast_expression_node : public ast_node {
  public:
    cast_expression_node(unary_expression_node* unaryExpr);
    void print();
    void generateCode();
  private:
    unary_expression_node* unaryExpr;
};

class unary_expression_node : public ast_node {
  public:
    unary_expression_node(postfix_expression_node* postExpr);
    unary_expression_node(OpType::Type op, unary_expression_node* unaryExpr);
    void print();
    void generateCode();
  private:
    postfix_expression_node* postExpr;
    OpType::Type op;
    unary_expression_node* unaryExpr;
    int mode;
};

class unary_operator_node : public ast_node {
  public:
    unary_operator_node(OpType::Type op);
    void print();
    void generateCode();
  private:
    OpType::Type op;
};

class postfix_expression_node : public ast_node {
  public:
    postfix_expression_node(primary_expression_node* primayExpr);
    postfix_expression_node(postfix_expression_node* postExpr, expression_node* expr); // array
    postfix_expression_node(postfix_expression_node* postExpr); // array w/o expr
    postfix_expression_node(postfix_expression_node* postExpr, argument_expression_list_node* argExpr); // function call
    postfix_expression_node(postfix_expression_node* postExpr, OpType::Type op, std::string identifier); // ptr or dot
    postfix_expression_node(postfix_expression_node* postExpr, OpType::Type op); // inc or dec
    void init();
    void print();
    void generateCode();
  private:
    int mode;
    primary_expression_node* primayExpr;
    postfix_expression_node* postExpr;
    expression_node* expr;
    argument_expression_list_node* argExpr;
    OpType::Type op;
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
