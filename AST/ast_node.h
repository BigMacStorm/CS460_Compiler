#ifndef __AST_NODE__H__
#define __AST_NODE__H__
#include <string>
#include <iostream>
#include <cstdlib>
#include "../SymbolTable.h"
#include "../SymbolNode.h"
#include "../graph.h"

extern Graph visualizer;

// forward declaration
class ast_node;
class translation_unit_node;
class external_declaration_node;
class function_definition_node;
class declaration_node;
class declaration_list_node;
class init_declarator_node;
class init_declarator_list_node;
class declaration_specifiers_node;
class storage_class_specifier_node;
class type_specifier_node;
class type_qualifier_node;
class type_qualifier_list_node;
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
class parameter_type_list_node;
class parameter_list_node;
class parameter_declaration_node;
class identifier_list_node;
class initializer_node;
class initializer_list_node;
class type_name_node;
class abstract_declarator_node;
class direct_abstract_declarator_node;
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

// Grouping this off to note that they are all binary operations,
// which we may want to collapse all into something like a binary_operation_node
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
class argument_expression_list_node;
class constant_node;
class string_node;
class identifier_node;

namespace DirectType{
  enum Type{NONE, ARRAY, FUNCTION, FUNCTION_CALL};
}
//could be enum for type_specifiers but should also includes struct and union (extra credit)
namespace TypeSpecifier{
  enum Type{VOID, CHAR, SHORT, INT, LONG, FLOAT, DOUBLE, SIGNED,
            UNSIGNED, TYPEDEF_NAME};
}
namespace ConstType{
  enum Type {INT,CHAR,FLOAT,ENUM};
}
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
namespace JumpType{
  enum Type{NONE, RETURN, BREAK, CONTINUE};
}
namespace IterType{
  enum Type{NONE, WHILE, DO, FOR};
}
namespace SelecType{
  enum Type{NONE, IF, SWITCH};
}
namespace LabelType{
  enum Type{NONE, CASE, DEFAULT};
}

class ast_node {
  public:
    ast_node(){
      this->name = "";
      this->parent = NULL;
      this->source = "";
      setID();
    };
    ~ast_node(){
      //delete children then itself, is this defined in each specific class?
    };
    virtual void print()=0;
    virtual void generateCode()=0;
    static int getTempNum(){ return tempNum++; }
    static int getLabelNum(){ return labelNum++; }
    static int getUID(){ return unique_id++; }

    void setID(){ this->id = getUID(); }
    int getID(){ return this->id; }
    int getPID(){ return this->pid; }
    void setPID(int pid){this->pid = pid; }

    Spec* getSpec();

    void error(const std::string& message) {
        std::cout << message << std::endl;
        exit(1);
    }
    void warning(const std::string& message) {
        std::cout << message << std::endl;
    }

  private:
    std::string name;
    ast_node* parent;
    std::string source;

    // for 3AC
    static int tempNum;   // 0
    static int labelNum;  // 0

    // for graphviz
    static int unique_id;  // 0

  protected:
    int id;
    int pid;
    Spec* spec;

    // If we need polymorphism
    //virtual std::vector<ast_node*> getChildren();
    // Otherwise, have specialized children getters
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
    function_definition_node(declaration_specifiers_node* specifiers,
                            declarator_node* decl,
                            declaration_list_node* decList,
                            compound_statement_node* compStmt);
    void print();
    void generateCode();
  private:
    int spec_id;
    declaration_specifiers_node* specifiers;
    declarator_node* decl;
    declaration_list_node* decList;
    compound_statement_node* compStmt;
};

class declaration_node : public ast_node {
  public:
    declaration_node();
    declaration_node(declaration_specifiers_node* specifier, init_declarator_list_node* decList);
    void print();
    void generateCode();
  private:
    declaration_specifiers_node* specifier;
    init_declarator_list_node* decList;
    int spec_id;
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
    init_declarator_node(declarator_node* declarator, initializer_node* initializer);
    Spec* getSpec();
    void init();
    void print();
    void generateCode();
  private:
    int equal_id;
    declarator_node* declarator;
    initializer_node* initializer;
};

class init_declarator_list_node : public ast_node {
public:
  init_declarator_list_node();
  init_declarator_list_node(init_declarator_node* child);
  void addInitDecl(init_declarator_node* child);
  std::vector<init_declarator_node*> getChildren() const;
  void print();
  void generateCode();
private:
  std::vector<init_declarator_node*> children;
};

class declaration_specifiers_node : public ast_node {
  public:
    declaration_specifiers_node(storage_class_specifier_node* storage, declaration_specifiers_node* declSpec);
    declaration_specifiers_node(type_specifier_node* typeSpec, declaration_specifiers_node* declSpec);
    declaration_specifiers_node(type_qualifier_node* qualifier, declaration_specifiers_node* declSpec);
    void init();
    void print();
    void generateCode();
  private:
    storage_class_specifier_node* storage;
    type_specifier_node* typeSpec;
    type_qualifier_node* qualifier;
    declaration_specifiers_node* declSpec;
};

class storage_class_specifier_node : public ast_node {
  public:
    storage_class_specifier_node();
    storage_class_specifier_node(SpecName::Storage storeType);
    void print();
    void generateCode();
  private:
    SpecName::Storage storeType;
};

class type_specifier_node : public ast_node {
  public:
    type_specifier_node();
    type_specifier_node(TypeSpecifier::Type type);
    void print();
    void generateCode();
  private:
    TypeSpecifier::Type type;
};

class type_qualifier_node : public ast_node {
  public:
    type_qualifier_node();
    type_qualifier_node(SpecName::Qualifier qual);
    void print();
    void generateCode();
  private:
    SpecName::Qualifier qual;
};
class type_qualifier_list_node : public ast_node {
public:
  type_qualifier_list_node();
  type_qualifier_list_node(type_qualifier_node* child);
  void addQual(type_qualifier_node* child);
  std::vector<type_qualifier_node*> getChildren() const;
  void print();
  void generateCode();
private:
  std::vector<type_qualifier_node*> children;
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
    specifier_qualifier_list_node(type_specifier_node* spec, specifier_qualifier_list_node* sqlist);
    specifier_qualifier_list_node(type_qualifier_node* qual, specifier_qualifier_list_node* sqlist);
    void init();
    Spec* getSpec();
    void print();
    void generateCode();
  private:
    specifier_qualifier_list_node* sqlist;
    type_specifier_node* spec;
    type_qualifier_node* qual;
};

class enum_specifier_node : public ast_node {
  public:
    enum_specifier_node();
    //init as null if not used
    enum_specifier_node(identifier_node* identifier, enumerator_list_node* enm);
    void print();
    void generateCode();
  private:
    enumerator_list_node* enumList;
    identifier_node* identifier;
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
    enumerator_node();
    enumerator_node(identifier_node* identifier, constant_expression_node* constExpr);
    void print();
    void generateCode();
  private:
    identifier_node* identifier;
    constant_expression_node* constExpr;
};

class declarator_node : public ast_node {
  public:
    declarator_node(pointer_node* pointer, direct_declarator_node* directDecl);

    Spec* getSpec();
    void print();
    void generateCode();
  private:
    direct_declarator_node* directDecl;
    pointer_node* pointer;
};

class direct_declarator_node : public ast_node {
  public:
    direct_declarator_node(identifier_node* identifier);
    direct_declarator_node(DirectType::Type direct_type, direct_declarator_node* direct_declarator, constant_expression_node* constExpr);
    direct_declarator_node(DirectType::Type direct_type, direct_declarator_node* direct_declarator);
    direct_declarator_node(DirectType::Type direct_type, direct_declarator_node* direct_declarator, parameter_type_list_node* paramList);
    direct_declarator_node(DirectType::Type direct_type, direct_declarator_node* direct_declarator, identifier_list_node* idList);
    void init();

    Spec* getSpec();
    void print();
    void generateCode();

  private:
    identifier_node* identifier;
    declarator_node* declarator;
    direct_declarator_node* direct_declarator;
    constant_expression_node* constExpr;
    parameter_type_list_node* paramList;
    identifier_list_node* idList;
    DirectType::Type direct_type;
    int mode;
};

class pointer_node : public ast_node {
  public:
    pointer_node(type_qualifier_list_node* typeQualList, pointer_node* pointer);
    void print();
    void generateCode();

  private:
    type_qualifier_list_node* typeQualList;
    pointer_node* pointer;
};

class parameter_type_list_node : public ast_node {
  public:
    parameter_type_list_node(parameter_list_node* paramList);
    void print();
    void generateCode();
  private:
    parameter_list_node* paramList;
};

class parameter_list_node : public ast_node {
public:
  parameter_list_node();
  parameter_list_node(parameter_declaration_node* child);
  void addParamDecl(parameter_declaration_node* child);
  std::vector<parameter_declaration_node*> getChildren() const;
  void print();
  void generateCode();
private:
  std::vector<parameter_declaration_node*> children;
};

class parameter_declaration_node : public ast_node {
  public:
    parameter_declaration_node(declaration_specifiers_node* declSpec);
    parameter_declaration_node(declaration_specifiers_node* declSpec, declarator_node* decl);
    parameter_declaration_node(declaration_specifiers_node* declSpec, abstract_declarator_node* absDecl);
    void print();
    void generateCode();
  private:
    declaration_specifiers_node* declSpec;
    declarator_node* decl;
    abstract_declarator_node* absDecl;
};

class identifier_list_node : public ast_node {
public:
  identifier_list_node();
  identifier_list_node(std::string child);
  void addIdentifier(std::string child);
  std::vector<std::string> getChildren() const;
  void print();
  void generateCode();
private:
  std::vector<std::string> children;
};

class initializer_node : public ast_node {
  public:
    initializer_node(assignment_expression_node* assignExpr);
    initializer_node(initializer_list_node* initList);

    Spec* getSpec();
    void print();
    void generateCode();

  private:
    assignment_expression_node* assignExpr;
    initializer_list_node* initList;
};

class initializer_list_node : public ast_node {
 public:
   initializer_list_node();
   initializer_list_node(initializer_node* child);
   void addInit(initializer_node* child);
   std::vector<initializer_node*> getChildren() const;

   Spec* getSpec();
   void print();
   void generateCode();
 private:
   std::vector<initializer_node*> children;
};

class type_name_node : public ast_node {
  public:
    type_name_node(specifier_qualifier_list_node* specQualList, abstract_declarator_node* absDecl);
    void print();
    void generateCode();
  private:
    specifier_qualifier_list_node* specQualList;
    abstract_declarator_node* absDecl;
};

class abstract_declarator_node : public ast_node {
  public:
    abstract_declarator_node(pointer_node* pointer,direct_abstract_declarator_node* directAbs);
    void print();
    void generateCode();
  private:
    pointer_node* pointer;
    direct_abstract_declarator_node* directAbs;
};

class direct_abstract_declarator_node: public ast_node{
public:
  direct_abstract_declarator_node();
  void print();
  void generateCode();
private:
};

class statement_node : public ast_node {
  public:
    statement_node(labeled_statement_node* labelStmt);
    statement_node(compound_statement_node* compStmt);
    statement_node(expression_statement_node* exprStmt);
    statement_node(selection_statement_node* selectStmt);
    statement_node(iteration_statement_node* iterStmt);
    statement_node(jump_statement_node* jumpStmt);
    void init();
    void print();
    void generateCode();
  private:
    labeled_statement_node* labelStmt;
    compound_statement_node* compStmt;
    expression_statement_node* exprStmt;
    selection_statement_node* selectStmt;
    iteration_statement_node* iterStmt;
    jump_statement_node* jumpStmt;
    int mode;
};


class labeled_statement_node : public ast_node {
  public:
    labeled_statement_node(std::string identifier, statement_node* statement);
    labeled_statement_node(LabelType::Type label_type, constant_expression_node* constExpr, statement_node* statement);
    void init();
    void print();
    void generateCode();
  private:
    LabelType::Type label_type;
    std::string identifier;
    constant_expression_node* constExpr;
    statement_node* statement;
};

class expression_statement_node : public ast_node {
  public:
    expression_statement_node();
    expression_statement_node(expression_node* expr);
    void init();
    void print();
    void generateCode();
  private:
    expression_node* expr;
};

class compound_statement_node : public ast_node {
  public:
    compound_statement_node(declaration_list_node* declList, statement_list_node* stateList);
    void init();
    void print();
    void generateCode();
  private:
    statement_list_node* stateList;
    declaration_list_node* declList;
};

class statement_list_node : public ast_node {
 public:
   statement_list_node();
   statement_list_node(statement_node* child);
   void addStmt(statement_node* child);
   std::vector<statement_node*> getChildren() const;
   void print();
   void generateCode();
 private:
   std::vector<statement_node*> children;
};

class selection_statement_node : public ast_node {
  public:
    selection_statement_node(SelecType::Type selec_type, expression_node* expr,
      statement_node* statement1,statement_node* statement2);
    void init();
    void print();
    void generateCode();

  private:
    SelecType::Type selec_type;
    expression_node* expr;
    statement_node *statement1, *statement2;
    int else_id;
};

class iteration_statement_node : public ast_node {
  public:
    iteration_statement_node(IterType::Type iter_type, expression_node* expr1,
      statement_node* statement);
    iteration_statement_node(IterType::Type iter_type, expression_node* expr1,
      expression_node* expr2,expression_node* expr3,statement_node* statement);
    void init();
    void print();
    void generateCode();

  private:
    IterType::Type iter_type;
    expression_node *expr1, *expr2, *expr3;
    statement_node* statement;
    int mode;
};

class jump_statement_node : public ast_node {
  public:
    jump_statement_node(std::string identifier);
    jump_statement_node(JumpType::Type jump_type);
    jump_statement_node(expression_node* expr);
    void init();
    void print();
    void generateCode();
  private:
    std::string identifier;
    expression_node* expr;
    JumpType::Type jump_type;
    int mode;
    int label_id;
};

class expression_node: public ast_node {
public:
  expression_node();
  expression_node(assignment_expression_node* child);
  void addAssignmentExpr(assignment_expression_node* child);
  std::vector<assignment_expression_node*> getChildren() const;

  Spec* getSpec();
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

    Spec* getSpec();
    void print();
    void generateCode();
  private:
    conditional_expression_node* cond_expr;
    unary_expression_node* unary_expr;
    assignment_operator_node* assign_op;
    assignment_expression_node* assign_expr;
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

    Spec* getSpec();
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

    Spec* getSpec();
    void print();
    void generateCode();
  private:
    conditional_expression_node* condExpr;
    expression_node* expr;
    logical_or_expression_node* logOrExpr;
    int mode;
};


//////////////////// Beginning of binary operations ////////////////////////////
class logical_or_expression_node : public ast_node {
  public:
    logical_or_expression_node(logical_and_expression_node* logAndExpr);
    logical_or_expression_node(logical_or_expression_node* logOrExpr,
            OpType::Type op, logical_and_expression_node* logAndExpr);
    void init();

    Spec* getSpec();
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

    Spec* getSpec();
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

    Spec* getSpec();
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

    Spec* getSpec();
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

    Spec* getSpec();
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

    Spec* getSpec();
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

    Spec* getSpec();
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

    Spec* getSpec();
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

    Spec* getSpec();
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

    Spec* getSpec();
    void print();
    void generateCode();
  private:
    cast_expression_node* castExpr;
    multiplicative_expression_node* multiExpr;
    OpType::Type op;
    int mode;
};
////////////////////////////////////////////////////////////////////////////////


class cast_expression_node : public ast_node {
  public:
    cast_expression_node(unary_expression_node* unaryExpr);
    cast_expression_node(type_name_node* typeName, cast_expression_node* castExpr);

    Spec* getSpec();
    void print();
    void generateCode();
  private:
    unary_expression_node* unaryExpr;
    cast_expression_node* castExpr;
    type_name_node* typeName;
};

class unary_expression_node : public ast_node {
  public:
    unary_expression_node(postfix_expression_node* postExpr);
    unary_expression_node(OpType::Type op, unary_expression_node* unaryExpr);
    unary_expression_node(unary_operator_node* unaryOp, cast_expression_node* castExpr);
    std::string getOpStr() const;
    void init();

    Spec* getSpec();
    void print();
    void generateCode();
  private:
    postfix_expression_node* postExpr;
    OpType::Type op;
    unary_operator_node* unaryOp;
    unary_expression_node* unaryExpr;
    cast_expression_node* castExpr;
    int mode;
};

class unary_operator_node : public ast_node {
  public:
    unary_operator_node(OpType::Type op);

    Spec* getSpec();
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
    Spec* getSpecForIdentifier();
    Spec* getSpec();
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
    int op_node_id;
};

class primary_expression_node: public ast_node {
  public:
    primary_expression_node(identifier_node* identifier);
    primary_expression_node(constant_node* constant);
    primary_expression_node(string_node* string);
    primary_expression_node(expression_node* expr);
    void init();
    bool isIdentifier() const;
    identifier_node* getIdentifier() const;
    Spec* getSpec();
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

  Spec* getSpec();
  void print();
  void generateCode();
private:
  std::vector<assignment_expression_node*> children;
};

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

  Spec* getSpec();
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

    Spec* getSpec();
    void print();
    void generateCode();

  private:
    std::string string_literal;
};

class identifier_node: public ast_node {
  public:
    identifier_node(std::string name, SymbolNode* symnode);
    void setSymNode(SymbolNode* sym);
    SymbolNode* getSymNode() const;
    std::string getName() const;
    Spec* getSpec();
    void print();
    void generateCode();
  private:
    std::string id_name;
    SymbolNode *id_symnode;
};
#endif
