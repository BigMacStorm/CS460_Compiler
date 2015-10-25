#include <string>

// Comment your name under nodes that you'll work on
// Assignments (roughly):
// 1-20 - Niki
// 21-40 - David
// 41-60 - Yuta
// 61-80 - Aaron

class ast_node {
  public:
    virtual ast_node()=0;
    virtual ~ast_node()=0;

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

class enter_scope_node : public ast_node {
  public:
  private:
};

class end_scope_node : public ast_node {
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

class declarator_list_node : public ast_node {
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

class class_specifier_node : public ast_node {
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

class declaration_list_node : public ast_node {
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

class qualifier_list_node : public ast_node {
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

class expression_node : public ast_node {
  public:
  private:
};

class assignment_expression_node : public ast_node {
  public:
  private:
};

class assignment_operator_node : public ast_node {
  public:
  private:
};

class conditional_expression_node : public ast_node {
  public:
  private:
};

class constant_expression_node : public ast_node {
  public:
  private:
};

class or_expression_node : public ast_node {
  public:
  private:
};

class and_expression_node : public ast_node {
  public:
  private:
};

class or_expression_node : public ast_node {
  public:
  private:
};

class or_expression_node : public ast_node {
  public:
  private:
};

class and_expression_node : public ast_node {
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

class unary_expression_node : public ast_node {
  public:
  private:
};

class unary_operator_node : public ast_node {
  public:
  private:
};

class postfix_expression_node : public ast_node {
  public:
  private:
};

class primary_expression_node : public ast_node {
  public:
  private:
};

class expression_list_node : public ast_node {
  public:
  private:
};

class constant_node : public ast_node {
  public:
  private:
};

class string_node : public ast_node {
  public:
  private:
};

class identifier_node : public ast_node {
  public:
  private:
};
