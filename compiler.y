/* definitions ****************************************************************/
%{
extern "C"{
  int yyparse();
  int yylex();
}
#include <stdio.h>
#include <fstream>
#include <string.h>
#include "AST/ast_node.h"
#include "SymbolTable.h"
#include "Debugger.h"
#include "Declaration.h"
#include "Spec.h"

extern Debugger warningDebugger;
extern Debugger reductionDebugger;
extern SymbolTable symTable;
extern int linenum;
extern int colnum;
extern char* yytext;

// File for writing source lines and reductions to
//const char* listFileName = "list_file";
extern std::string listFileName;

void yyerror(const char* message);
void error(const std::string& message);
void warning(const std::string& message);
void reductionOut(const char* reductionCStr);

Declaration decl; // holds info about a current declaration
bool insert_mode = true;

%}

%union{
  char cval;
  int ival;
  double dval;
  char sval[100];
  SymbolNode* symnode;
  ast_node* astnode;
  SpecName::TypeKind tkval;
 }


// Tokens
%token <sval> IDENTIFIERtok
%token <ival> INTEGER_CONSTANTtok
%token <dval> FLOATING_CONSTANTtok
%token <cval> CHARACTER_CONSTANTtok
%token <sym> ENUMERATION_CONSTANTtok
%token <sval> STRING_LITERALtok

%token SIZEOFtok
%token PTR_OPtok
%token INC_OPtok DEC_OPtok
%token LEFT_OPtok RIGHT_OPtok
%token LE_OPtok GE_OPtok EQ_OPtok NE_OPtok
%token AND_OPtok OR_OPtok
%token MUL_ASSIGNtok DIV_ASSIGNtok MOD_ASSIGNtok ADD_ASSIGNtok SUB_ASSIGNtok
%token LEFT_ASSIGNtok RIGHT_ASSIGNtok AND_ASSIGNtok XOR_ASSIGNtok OR_ASSIGNtok
%token TYPEDEF_NAMEtok

%token SEMItok PERIODtok UNARY_BANGtok UNARY_TILDEtok UNARY_ANDtok
%token PERCENTtok FORWARD_SLASHtok UNARY_MINUStok UNARY_PLUStok
%token RIGHT_ANGLEtok LEFT_ANGLEtok UP_CARROTtok PIPEtok QUESTION_MARKtok
%token UNARY_ASTERISKtok CLOSE_SQUAREtok OPEN_SQUAREtok CLOSE_PARENtok
%token OPEN_PARENtok COLONtok EQUALtok COMMAtok CLOSE_CURLYtok OPEN_CURLYtok

%token TYPEDEFtok EXTERNtok STATICtok AUTOtok REGISTERtok
%token CHARtok SHORTtok INTtok LONGtok SIGNEDtok UNSIGNEDtok FLOATtok DOUBLEtok CONSTtok VOLATILEtok VOIDtok

/*%token STRUCTtok UNIONtok ENUMtok ELIPSIStok RANGEtok*/

%token <tkval> STRUCTtok
%token <tkval> UNIONtok
%token ENUMtok ELIPSIStok RANGEtok

%type <sval> identifier
%type <tkval> struct_or_union

%token CASEtok DEFAULTtok IFtok ELSEtok SWITCHtok WHILEtok DOtok FORtok GOTOtok CONTINUEtok BREAKtok RETURNtok

%token ERRORtok

%type <astnode> constant string primary_expression postfix_expression argument_expression_list unary_expression unary_operator cast_expression multiplicative_expression additive_expression shift_expression relational_expression equality_expression and_expression exclusive_or_expression inclusive_or_expression logical_and_expression logical_or_expression conditional_expression assignment_expression assignment_operator expression constant_expression

%start program

/* Grammar ruls and actions ***************************************************/
%%

program
  : translation_unit{
    std::cout << "Success!" << std::endl;
  }
translation_unit
  : external_declaration {
     reductionOut("[p]: translation_unit -> external_declaration");
  }
  | translation_unit external_declaration {
    reductionOut("[p]: translation_unit -> translation_unit external_declaration");
  }
  ;

external_declaration
  : function_definition{
    reductionOut("[p]: external_declaration -> function_definition");
  }
  | declaration  {
    reductionOut("[p]: external_declaration -> declaration");
  }
  ;

/*** scope productions *******************************************************
A start_scope is called before compound_statement and a end_scope is called
after compound_statement.
*****************************************************************************/
enter_scope
  : {
      if(insert_mode && decl.isMode(DeclMode::Function)){
        decl.complete(); // complete function definition
        symTable.pushTable();

        // push argments if possible
        std::vector<SymbolNode*> args = decl.getArgSymbolNodes();
        if(args.size() > 0){
          for(int arg = 0; arg < args.size(); arg++){
            symTable.insertSymbol(args[arg]->getName(),args[arg]);
            }
        }
        // function is complete
        std::string func_name = decl.getID(0);
        symTable.lookupSymbol(func_name)->setDefined(true);

        decl.clear();
        insert_mode = false;
        decl.setMode(DeclMode::NoMode);
      }
      else{
        symTable.pushTable();
      }
    }
;
end_scope
  : {symTable.popTable();}
;

function_definition
  : declarator compound_statement {
      reductionOut("[p]: function_definition -> declarator compound_statement");
      }
  | declarator declaration_list compound_statement {
      reductionOut("[p]: function_definition -> declarator declaration_list compound_statement");
      }
  | declaration_specifiers declarator compound_statement {
      reductionOut("[p]: function_definition -> declaration_specifiers declarator compound_statement");
    }
  | declaration_specifiers declarator declaration_list compound_statement {
       reductionOut("[p]: function_definition -> declaration_specifiers declarator declaration_list compound_statement");
    }
  ;

declaration
  : declaration_specifiers SEMItok{
      reductionOut("[p]: declaration -> declaration_specifiers SEMItok");
      insert_mode = true;
      decl.clear();
  }
  | declaration_specifiers init_declarator_list SEMItok{
      reductionOut("[p]: declaration -> declaration_specifiers init_declarator_list SEMItok");
      insert_mode = true;
      decl.clear();
  }
  ;

declaration_list
  : declaration{
      reductionOut("[p]: declaration_list -> declaration");
  }
  | declaration_list declaration{
      reductionOut("[p]: declaration_list -> declaration_list declaration");
  }
  ;

init_declarator_list
  : init_declarator {
      // a single variable declaration
      reductionOut("[p]: init_declarator_list -> init_declarator");
  }
  | init_declarator_list COMMAtok init_declarator {
      // multiple single line declarations
      reductionOut("[p]: init_declarator_list -> init_declarator_list COMMAtok init_declarator");
  }
  ;

init_declarator
  : declarator{
      // declaration
      reductionOut("[p]: init_declarator -> declarator");
      decl.complete();
  }
  | declarator EQUALtok initializer {
      // initialization
      reductionOut("[p]: init_declarator -> declarator EQUALtok initializer");
      decl.complete();
  }
  ;

/*** Declaration Spec *********************************************************
*****************************************************************************/
declaration_specifiers
  : storage_class_specifier {
      reductionOut("[p]: declaration_specifiers -> storage_class_specifier");
  }
  | storage_class_specifier declaration_specifiers  {
      reductionOut("[p]: declaration_specifiers -> storage_class_specifier declaration_specifiers");
  }
  | type_specifier  {
      reductionOut("[p]: declaration_specifiers -> type_specifier");
  }
  | type_specifier declaration_specifiers  {
      reductionOut("[p]: declaration_specifiers -> type_specifier declaration_specifiers");
  }
  | type_qualifier  {
      reductionOut("[p]: declaration_specifiers -> type_qualifier");
  }
  | type_qualifier declaration_specifiers  {
      reductionOut("[p]: declaration_specifiers -> type_qualifier declaration_specifiers");
  }
  ;

/* Storage Class **************************************************************
A variable or function has one of these storage classes
Storage class     Lifetime             Visibility
extern            program execution   external (whole program)
static            program execution   internal (translation unit only)
auto, register    function execution  (none)

Declaration without the storage class:
1. extern for all top-level declarations in a source file
2. auto for variables declared in function bodies.

register variable:
- A special case of automatic variable
- It suggests to the compiler that particular auto variables should be allocated
  to CPU registers instead of RAM, if possible.
- For most computers, accessing data in memory is considerably slower
  than processing in the CPU. Variables which are used repeatedly or
  whose access times are critical, may be declared to be of register

static variable
- it is only initialized at the beginning of program execution

typedef specifier
- it does not reserve storage and is called a storage class specifier
  only for syntactic convenience
 ****************************************************************************/

storage_class_specifier
  : AUTOtok {
    reductionOut("[p]: storage_class_specifier -> AUTOtok");
    decl.pushStorage(SpecName::Auto);
  }
  | REGISTERtok {
    reductionOut("[p]: storage_class_specifier -> REGISTERtok");
    decl.pushStorage(SpecName::Register);
  }
  | STATICtok {
    reductionOut("[p]: storage_class_specifier -> STATICtok");
    decl.pushStorage(SpecName::Static);
  }
  | EXTERNtok {
    reductionOut("[p]: storage_class_specifier -> EXTERNtok");
    decl.pushStorage(SpecName::Extern);
  }
  | TYPEDEFtok {
    reductionOut("[p]: storage_class_specifier -> TYPEDEFtok");
    decl.pushStorage(SpecName::Typedef);
  }
  ;

/* type_specifier ************************************************************
A type-specifier defines the type of a variable or function declaration.
A type-specifier is to be int by default when it is not provided.

The keyword void has three uses:
1. to specify a function return type (return no value)
2. to specify an argument-type list for a function that takes no arguments
3. to specify a pointer to an unspecified type.
*******************************************************************************/
type_specifier
  :
    VOIDtok {
    reductionOut("[p]: type_specifier -> VOIDtok");
    decl.setMode(DeclMode::Basic);
    decl.pushKind(SpecName::Basic);
    decl.pushBase(SpecName::Void);
  }
  | CHARtok {
    reductionOut("[p]: type_specifier -> CHARtok");
    decl.setMode(DeclMode::Basic);
    decl.pushKind(SpecName::Basic);
    decl.pushBase(SpecName::Char);
  }
  | SHORTtok {
    reductionOut("[p]: type_specifier -> SHORTtok");
    decl.setMode(DeclMode::Basic);
    decl.pushKind(SpecName::Basic);
    decl.pushBase(SpecName::Short);
  }
  | INTtok {
    reductionOut("[p]: type_specifier -> INTtok");
    decl.setMode(DeclMode::Basic);
    decl.pushKind(SpecName::Basic);
    decl.pushBase(SpecName::Int);
  }
  | LONGtok  {
    reductionOut("[p]: type_specifier -> LONGtok");
    decl.setMode(DeclMode::Basic);
    decl.pushKind(SpecName::Basic);
    decl.pushBase(SpecName::Long);
  }
  | FLOATtok  {
    reductionOut("[p]: type_specifier -> FLOATtok");
    decl.setMode(DeclMode::Basic);
    decl.pushKind(SpecName::Basic);
    decl.pushBase(SpecName::Float);
  }
  | DOUBLEtok  {
    reductionOut("[p]: type_specifier -> DOUBLEtok");
    decl.setMode(DeclMode::Basic);
    decl.pushKind(SpecName::Basic);
    decl.pushBase(SpecName::Double);
  }
  | SIGNEDtok  {
    reductionOut("[p]: type_specifier -> SIGNEDtok");
    decl.pushSign(SpecName::Signed);
  }
  | UNSIGNEDtok  {
    reductionOut("[p]: type_specifier -> UNSIGNEDtok");
    decl.pushSign(SpecName::Unsigned);
  }
  | struct_or_union_specifier  {
    reductionOut("[p]: type_specifier -> struct_or_union_specifier");
  }
  | enum_specifier  {
    reductionOut("[p]: type_specifier -> enum_specifier");
    decl.pushKind(SpecName::Enum);
    decl.setMode(DeclMode::Enum);
  }
  | TYPEDEF_NAMEtok  {
    decl.pushKind(SpecName::TypeName);
    reductionOut("[p]: type_specifier -> TYPEDEF_NAMEtok");
  }
  ;

type_qualifier
  : CONSTtok {
    reductionOut("[p]: type_qualifier -> CONSTtok");
    decl.pushQualifier(SpecName::Const);
  }
  | VOLATILEtok {
    reductionOut("[p]: type_qualifier -> VOLATILEtok");
    decl.pushQualifier(SpecName::Volatile);
  }
  ;

struct_or_union_specifier
  : struct_or_union identifier OPEN_CURLYtok struct_declaration_list CLOSE_CURLYtok {
      reductionOut("[p]: struct_or_union_specifier -> struct_or_union identifier OPEN_CURLYtok struct_declaration_list CLOSE_CURLYtok");

      if(symTable.lookupTopTable($2))
        error("error: redefinition"); // Redefinition; fatal error
      else
        symTable.insertSymbol($2, new SymbolNode($2, new Spec($1)));
  }
  | struct_or_union OPEN_CURLYtok struct_declaration_list CLOSE_CURLYtok {
      // struct {...}
      reductionOut("[p]: struct_or_union_specifier -> struct_or_union OPEN_CURLYtok struct_declaration_list CLOSE_CURLYtokk");
  }
  | struct_or_union identifier {
      // forward declaration  struct id;
      reductionOut("[p]: struct_or_union_specifier -> struct_or_union identifier");

      if(symTable.lookupTopTable($2))
        error("error: redefinition"); // Redefinition; fatal error
      else
        symTable.insertSymbol($2, new SymbolNode($2, new Spec($1)));
  }
  ;

struct_or_union
  : STRUCTtok {
      reductionOut("[p]: struct_or_union -> STRUCTtok");
      decl.pushKind(SpecName::Struct);
      decl.setMode(DeclMode::Struct);
      $$ = SpecName::Struct;
  }
  | UNIONtok {
      reductionOut("[p]: struct_or_union -> UNIONtok");
      decl.pushKind(SpecName::Union);
      decl.setMode(DeclMode::Union);
      $$ = SpecName::Union;
  }
  ;

struct_declaration_list
  : struct_declaration {
      reductionOut("[p]: struct_declaration_list -> struct_declaration");
  }
  | struct_declaration_list struct_declaration {
      reductionOut("[p]: struct_declaration_list -> struct_declaration_list struct_declaration");
  }
  ;

struct_declaration
  : specifier_qualifier_list struct_declarator_list SEMItok {
      reductionOut("[p]: struct_declaration -> specifier_qualifier_list struct_declarator_list SEMItok");
  }
  ;

specifier_qualifier_list
  : type_specifier {
      reductionOut("[p]: specifier_qualifier_list -> type_specifier");
  }
  | type_specifier specifier_qualifier_list {
      reductionOut("[p]: specifier_qualifier_list -> type_specifier specifier_qualifier_list");
  }
  | type_qualifier {
      reductionOut("[p]: specifier_qualifier_list -> type_qualifier");
  }
  | type_qualifier specifier_qualifier_list {
      reductionOut("[p]: specifier_qualifier_list -> type_qualifier specifier_qualifier_list");
  }
  ;

struct_declarator_list
  : struct_declarator {
      reductionOut("[p]: struct_declarator_list -> struct_declarator");
  }
  | struct_declarator_list COMMAtok struct_declarator {
      reductionOut("[p]: struct_declarator_list -> struct_declarator_list COMMAtok struct_declarator");
  }
  ;

struct_declarator
  : declarator {
      reductionOut("[p]: struct_declarator -> declarator");
  }
  | COLONtok constant_expression {
      reductionOut("[p]: struct_declarator -> COLONtok constant_expression");
  }
  | declarator COLONtok constant_expression {
      reductionOut("[p]: struct_declarator -> declarator COLONtok constant_expression");
  }
  ;

enum_specifier
  : ENUMtok OPEN_CURLYtok enumerator_list CLOSE_CURLYtok {
      reductionOut("[p]: enum_specifier -> ENUMtok OPEN_CURLYtok enumerator_list CLOSE_CURLYtok");
  }
  | ENUMtok identifier OPEN_CURLYtok enumerator_list CLOSE_CURLYtok {
      reductionOut("[p]: enum_specifier -> ENUMtok identifier OPEN_CURLYtok enumerator_list CLOSE_CURLYtok");
  }
  | ENUMtok identifier {
      reductionOut("[p]: enum_specifier -> ENUMtok identifier");
  }
  ;

enumerator_list
  : enumerator {
      reductionOut("[p]: enumerator_list -> enumerator");
  }
  | enumerator_list COMMAtok enumerator {
      reductionOut("[p]: enumerator_list -> enumerator_list COMMAtok enumerator");
  }
  ;

enumerator
  : identifier {
      reductionOut("[p]: enumerator -> identifier");
  }
  | identifier EQUALtok constant_expression {
      reductionOut("[p]: enumerator -> identifier EQUALtok constant_expression");
  }
  ;

declarator
  : direct_declarator {
      reductionOut("[p]: declarator -> direct_declarator");
      insert_mode = true;

      decl.pushKind(SpecName::NoKind);
      decl.pushBase(SpecName::NoType);
      decl.pushSign(SpecName::NoSign);
      decl.pushQualifier(SpecName::NoQualifier);
      decl.pushStorage(SpecName::NoStorage);

      if(decl.isMode(DeclMode::Array)){
         decl.setNextArray();
      }
  }
  | pointer direct_declarator {
      // pointer mode
      reductionOut("[p]: declarator -> pointer direct_declarator");
      decl.setNextPtr();

      decl.pushKind(SpecName::NoKind);
      decl.pushBase(SpecName::NoType);
      decl.pushSign(SpecName::NoSign);
      decl.pushQualifier(SpecName::NoQualifier);
      decl.pushStorage(SpecName::NoStorage);

      if(decl.isMode(DeclMode::Array)){
         decl.setNextArray();
      }
  }
  ;

direct_declarator
  : identifier {
      reductionOut("[p]: direct_declarator -> identifier");
      // for no return type
      if(decl.getBasesNum() > 0){
        decl.setHasType();
      }
  }
  | OPEN_PARENtok declarator CLOSE_PARENtok {
      // e.g., (*a)[COLS]
      reductionOut("[p]: direct_declarator -> OPEN_PARENtok declarator CLOSE_PARENtok");
  }
  | direct_declarator OPEN_SQUAREtok CLOSE_SQUAREtok {
      // array mode - e.g., foo[]
      reductionOut("[p]: direct_declarator -> direct_declarator OPEN_SQUAREtok CLOSE_SQUAREtok");
      decl.setMode(DeclMode::Array);
      decl.pushArraySize(1); // if there is initialization, warning: tentative array definition assumed to have one element
      decl.pushKind(SpecName::Array);
  }
  | direct_declarator OPEN_SQUAREtok constant_expression CLOSE_SQUAREtok {
      // array mode - e.g., type foo[size], foo[s1][s2]
      reductionOut("[p]: direct_declarator -> direct_declarator OPEN_SQUAREtok constant_expression CLOSE_SQUAREtok");
      decl.setMode(DeclMode::Array);
      decl.pushArraySize(yylval.ival);
      decl.pushKind(SpecName::Array);
  }
  | direct_declarator OPEN_PARENtok {

    decl.pushKind(SpecName::NoKind);
    decl.pushBase(SpecName::NoType);
    decl.pushSign(SpecName::NoSign);
    decl.pushQualifier(SpecName::NoQualifier);
    decl.pushStorage(SpecName::NoStorage);

  } CLOSE_PARENtok{
      // function mode - e.g., foo()
      reductionOut("[p]: direct_declarator -> direct_declarator OPEN_PARENtok CLOSE_PARENtok");
      decl.setMode(DeclMode::Function);
      decl.pushKind(SpecName::Function);
  }
  | direct_declarator OPEN_PARENtok {

    decl.pushKind(SpecName::NoKind);
    decl.pushBase(SpecName::NoType);
    decl.pushSign(SpecName::NoSign);
    decl.pushQualifier(SpecName::NoQualifier);
    decl.pushStorage(SpecName::NoStorage);

  } parameter_type_list CLOSE_PARENtok{
      // function mode - e.g., foo(type a, type b)
      reductionOut("[p]: direct_declarator -> direct_declarator OPEN_PARENtok parameter_type_list CLOSE_PARENtok");
      decl.setMode(DeclMode::Function);
      decl.pushKind(SpecName::Function);
  }
  | direct_declarator OPEN_PARENtok identifier_list CLOSE_PARENtok{
      // function call - e.g., foo(x,y)
      reductionOut("[p]: direct_declarator -> direct_declarator OPEN_PARENtok identifier_list CLOSE_PARENtok");
      decl.setMode(DeclMode::FunctionCall);
  }
  ;

pointer
  : UNARY_ASTERISKtok {
      // *
      reductionOut("[p]: pointer -> UNARY_ASTERISKtok");
      decl.setMode(DeclMode::Pointer);
      decl.pushKind(SpecName::Pointer);
      decl.incPtrLevel();
  }
  | UNARY_ASTERISKtok type_qualifier_list {
      // * const/volatile
      reductionOut("[p]: pointer -> UNARY_ASTERISKtok type_qualifier_list");
      decl.setMode(DeclMode::Pointer);
      decl.pushKind(SpecName::Pointer);
      decl.incPtrLevel();
  }
  | UNARY_ASTERISKtok pointer {
      // ** ...
      reductionOut("[p]: pointer -> UNARY_ASTERISKtok pointer");
      decl.setMode(DeclMode::Pointer);
      decl.pushKind(SpecName::Pointer);
      decl.incPtrLevel();
  }
  | UNARY_ASTERISKtok type_qualifier_list pointer {
      // * const/volatile * ...
      reductionOut("[p]: pointer -> UNARY_ASTERISKtok type_qualifier_list pointer");
      decl.setMode(DeclMode::Pointer);
      decl.pushKind(SpecName::Pointer);
      decl.incPtrLevel();
  }
  ;

type_qualifier_list
  : type_qualifier {
      reductionOut("[p]: type_qualifier_list -> type_qualifier");
  }
  | type_qualifier_list type_qualifier {
      reductionOut("[p]: type_qualifier_list -> type_qualifier_list type_qualifier");
  }
  ;

parameter_type_list
  : parameter_list {
      reductionOut("[p]: parameter_type_list -> parameter_list");
  }
  | parameter_list COMMAtok ELIPSIStok {
      reductionOut("[p]: parameter_type_list ->  parameter_list COMMAtok ELIPSIStok");
  }
  ;

parameter_list
  : parameter_declaration {
      reductionOut("[p]: parameter_list -> parameter_declaration");
      decl.incArgSize();
  }
  | parameter_list COMMAtok parameter_declaration {
      reductionOut("[p]: parameter_list -> parameter_list COMMAtok parameter_declaration");
      decl.incArgSize();
  }
  ;

parameter_declaration
  : declaration_specifiers declarator {
      // e.g., int x, int *x
      reductionOut("[p]: parameter_declaration -> declaration_specifiers declarator");
  }
  | declaration_specifiers {
      // e.g., int
      reductionOut("[p]: parameter_declaration -> declaration_specifiers");
      decl.pushKind(SpecName::NoKind);
      decl.pushBase(SpecName::NoType);
      decl.pushSign(SpecName::NoSign);
      decl.pushQualifier(SpecName::NoQualifier);
      decl.pushStorage(SpecName::NoStorage);
  }
  | declaration_specifiers abstract_declarator {
      // e.g., ?
      reductionOut("[p]: parameter_declaration -> declaration_specifiers abstract_declarator");
  }
  ;

identifier_list
  : identifier {
      reductionOut("[p]: identifier_list -> identifier");
  }
  | identifier_list COMMAtok identifier {
      reductionOut("[p]: identifier_list -> ");
  }
  ;

initializer
  : assignment_expression {
      reductionOut("[p]: initializer -> assignment_expression");
  }
  | OPEN_CURLYtok initializer_list CLOSE_CURLYtok {
      reductionOut("[p]: initializer -> OPEN_CURLYtok initializer_list CLOSE_CURLYtok");
  }
  | OPEN_CURLYtok initializer_list COMMAtok CLOSE_CURLYtok {
      reductionOut("[p]: initializer -> OPEN_CURLYtok initializer_list COMMAtok CLOSE_CURLYtok");
  }
  ;

initializer_list
  : initializer {
      reductionOut("[p]: initializer_list -> initializer");
  }
  | initializer_list COMMAtok initializer {
      reductionOut("[p]: initializer_list -> initializer_list COMMAtok initializer");
  }
  ;

type_name
  : specifier_qualifier_list {
      reductionOut("[p]: type_name -> specifier_qualifier_list");
  }
  | specifier_qualifier_list abstract_declarator {
      reductionOut("[p]: type_name -> specifier_qualifier_list abstract_declarator");
  }
  ;

abstract_declarator
  : pointer {
      reductionOut("[p]: abstract_declarator -> pointer");
  }
  | direct_abstract_declarator {
      reductionOut("[p]: abstract_declarator -> direct_abstract_declarator");
  }
  | pointer direct_abstract_declarator {
      reductionOut("[p]: abstract_declarator -> pointer direct_abstract_declarator");
  }
  ;

direct_abstract_declarator
  : OPEN_PARENtok abstract_declarator CLOSE_PARENtok {
      reductionOut("[p]: direct_abstract_declarator -> OPEN_PARENtok abstract_declarator CLOSE_PARENtok");
  }
  | OPEN_SQUAREtok CLOSE_SQUAREtok {
      reductionOut("[p]: direct_abstract_declarator -> OPEN_SQUAREtok CLOSE_SQUAREtok");
  }
  | OPEN_SQUAREtok constant_expression CLOSE_SQUAREtok {
      reductionOut("[p]: direct_abstract_declarator -> OPEN_SQUAREtok constant_expression CLOSE_SQUAREtok");
  }
  | direct_abstract_declarator OPEN_SQUAREtok CLOSE_SQUAREtok {
      reductionOut("[p]: direct_abstract_declarator -> direct_abstract_declarator OPEN_SQUAREtok CLOSE_SQUAREtok");
  }
  | direct_abstract_declarator OPEN_SQUAREtok constant_expression CLOSE_SQUAREtok {
      reductionOut("[p]: direct_abstract_declarator -> direct_abstract_declarator OPEN_SQUAREtok constant_expression CLOSE_SQUAREtok");
  }
  | OPEN_PARENtok CLOSE_PARENtok {
      reductionOut("[p]: direct_abstract_declarator -> OPEN_PARENtok CLOSE_PARENtok");
  }
  | OPEN_PARENtok parameter_type_list CLOSE_PARENtok {
      reductionOut("[p]: direct_abstract_declarator -> OPEN_PARENtok parameter_type_list CLOSE_PARENtok");
  }
  | direct_abstract_declarator OPEN_PARENtok CLOSE_PARENtok {
      reductionOut("[p]: direct_abstract_declarator -> direct_abstract_declarator OPEN_PARENtok CLOSE_PARENtok");
  }
  | direct_abstract_declarator OPEN_PARENtok parameter_type_list CLOSE_PARENtok {
      reductionOut("[p]: direct_abstract_declarator -> direct_abstract_declarator OPEN_PARENtok parameter_type_list CLOSE_PARENtok");
  }
  ;

statement
  : labeled_statement {
      reductionOut("[p]: statement -> labeled_statement");
  }
  | compound_statement {
      reductionOut("[p]: statement -> compound_statement");
  }
  | expression_statement {
      reductionOut("[p]: statement -> expression_statement");
  }
  | selection_statement {
      reductionOut("[p]: statement -> selection_statement");
  }
  | iteration_statement {
      reductionOut("[p]: statement -> iteration_statement");
  }
  | jump_statement {
      reductionOut("[p]: statement -> jump_statement");
  }
  ;

labeled_statement
  : identifier COLONtok statement {
      reductionOut("[p]: labeled_statement -> identifier COLONtok statement");
  }
  | CASEtok constant_expression COLONtok statement {
      reductionOut("[p]: labeled_statement -> CASEtok constant_expression COLONtok statement");
  }
  | DEFAULTtok COLONtok statement {
      reductionOut("[p]: labeled_statement -> DEFAULTtok COLONtok statement");
  }
  ;

expression_statement
  : SEMItok {
      reductionOut("[p]: expression_statement -> SEMItok");
  }
  | expression SEMItok {
      reductionOut("[p]: expression_statement -> expression SEMItok");
  }
  ;

compound_statement
  : OPEN_CURLYtok enter_scope CLOSE_CURLYtok end_scope{
      reductionOut("[p]: compound_statement -> OPEN_CURLYtok CLOSE_CURLYtok");
  }
  | OPEN_CURLYtok enter_scope statement_list CLOSE_CURLYtok end_scope{
      reductionOut("[p]: compound_statement -> OPEN_CURLYtok statement_list CLOSE_CURLYtok");
  }
  | OPEN_CURLYtok enter_scope declaration_list CLOSE_CURLYtok end_scope{
      reductionOut("[p]: compound_statement -> OPEN_CURLYtok declaration_list CLOSE_CURLYtok");
  }
  | OPEN_CURLYtok enter_scope declaration_list statement_list CLOSE_CURLYtok end_scope{
      reductionOut("[p]: compound_statement -> OPEN_CURLYtok declaration_list statement_list CLOSE_CURLYtok");
  }
  ;

statement_list
  : statement {
      reductionOut("[p]: statement_list -> statement");
  }
  | statement_list statement {
      reductionOut("[p]: statement_list -> statement_list statement");
  }
  ;

selection_statement
  : IFtok OPEN_PARENtok expression CLOSE_PARENtok statement {
      reductionOut("[p]: selection_statement -> IFtok OPEN_PARENtok expression CLOSE_PARENtok statement");
  }
  | IFtok OPEN_PARENtok expression CLOSE_PARENtok statement ELSEtok statement {
      reductionOut("[p]: selection_statement -> IFtok OPEN_PARENtok expression CLOSE_PARENtok statement ELSEtok statement");
  }
  | SWITCHtok OPEN_PARENtok expression CLOSE_PARENtok statement {
      reductionOut("[p]: selection_statement -> SWITCHtok OPEN_PARENtok expression CLOSE_PARENtok statement");
  }
  ;

iteration_statement
  : WHILEtok OPEN_PARENtok expression CLOSE_PARENtok statement {
      reductionOut("[p]: iteration_statement -> WHILEtok OPEN_PARENtok expression CLOSE_PARENtok statement");
  }
  | DOtok statement WHILEtok OPEN_PARENtok expression CLOSE_PARENtok SEMItok {
      reductionOut("[p]: iteration_statement -> DOtok statement WHILEtok OPEN_PARENtok expression CLOSE_PARENtok SEMItok");
  }
  | FORtok OPEN_PARENtok SEMItok SEMItok CLOSE_PARENtok statement {
      reductionOut("[p]: iteration_statement -> FORtok OPEN_PARENtok SEMItok SEMItok CLOSE_PARENtok statement");
  }
  | FORtok OPEN_PARENtok SEMItok SEMItok expression CLOSE_PARENtok statement {
      reductionOut("[p]: iteration_statement -> FORtok OPEN_PARENtok SEMItok SEMItok expression CLOSE_PARENtok statement");
  }
  | FORtok OPEN_PARENtok SEMItok expression SEMItok CLOSE_PARENtok statement {
      reductionOut("[p]: iteration_statement -> FORtok OPEN_PARENtok SEMItok expression SEMItok CLOSE_PARENtok statement");
  }
  | FORtok OPEN_PARENtok SEMItok expression SEMItok expression CLOSE_PARENtok statement {
      reductionOut("[p]: iteration_statement -> FORtok OPEN_PARENtok SEMItok expression SEMItok expression CLOSE_PARENtok statement");
  }
  | FORtok OPEN_PARENtok expression SEMItok SEMItok CLOSE_PARENtok statement {
      reductionOut("[p]: iteration_statement -> FORtok OPEN_PARENtok expression SEMItok SEMItok CLOSE_PARENtok statement");
  }
  | FORtok OPEN_PARENtok expression SEMItok SEMItok expression CLOSE_PARENtok statement {
      reductionOut("[p]: iteration_statement -> FORtok OPEN_PARENtok expression SEMItok SEMItok expression CLOSE_PARENtok statement");
  }
  | FORtok OPEN_PARENtok expression SEMItok expression SEMItok CLOSE_PARENtok statement {
      reductionOut("[p]: iteration_statement -> FORtok OPEN_PARENtok expression SEMItok expression SEMItok CLOSE_PARENtok statement");
  }
  | FORtok OPEN_PARENtok expression SEMItok expression SEMItok expression CLOSE_PARENtok statement {
      reductionOut("[p]: iteration_statement -> FORtok OPEN_PARENtok expression SEMItok expression SEMItok expression CLOSE_PARENtok statement");
  }
  ;

jump_statement
  : GOTOtok identifier SEMItok {
      reductionOut("[p]: jump_statement -> GOTOtok identifier SEMItok");
  }
  | CONTINUEtok SEMItok {
      reductionOut("[p]: jump_statement -> CONTINUEtok SEMItok");
  }
  | BREAKtok SEMItok {
      reductionOut("[p]: jump_statement -> BREAKtok SEMItok");
  }
  | RETURNtok SEMItok {
      reductionOut("[p]: jump_statement ->  RETURNtok SEMItok");
  }
  | RETURNtok expression SEMItok {
      reductionOut("[p]: jump_statement -> RETURNtok expression SEMItok");
  }
  ;

expression
  : assignment_expression {
      reductionOut("[p]: expression -> assignment_expression");
  }
  | expression COMMAtok assignment_expression {
      reductionOut("[p]: expression -> expression COMMAtok assignment_expression");
  }
  ;

assignment_expression
  : conditional_expression {
      //$$ = new assignment_expression_node(dynamic_cast<conditional_expression_node*>($1));
      reductionOut("[p]: assignment_expression -> conditional_expression");
  }
  | unary_expression assignment_operator assignment_expression {
      $$ = new assignment_expression_node(dynamic_cast<unary_expression_node*>($1),dynamic_cast<assignment_operator_node*>($2),dynamic_cast<assignment_expression_node*>($3));
      reductionOut("[p]: assignment_expression -> unary_expression assignment_operator assignment_expression");
  }
  ;

assignment_operator
  : EQUALtok {
      $$ = new assignment_operator_node(AssignType::EQUAL);
      reductionOut("[p]: assignment_operator -> EQUALtok");
  }
  | MUL_ASSIGNtok {
      $$ = new assignment_operator_node(AssignType::MUL_ASSIGN);
      reductionOut("[p]: assignment_operator -> MUL_ASSIGNtok");
  }
  | DIV_ASSIGNtok {
      $$ = new assignment_operator_node(AssignType::DIV_ASSIGN);
      reductionOut("[p]: assignment_operator -> DIV_ASSIGNtok");
  }
  | MOD_ASSIGNtok {
      $$ = new assignment_operator_node(AssignType::MOD_ASSIGN);
      reductionOut("[p]: assignment_operator -> MOD_ASSIGNtok");
  }
  | ADD_ASSIGNtok {
      $$ = new assignment_operator_node(AssignType::ADD_ASSIGN);
      reductionOut("[p]: assignment_operator -> ADD_ASSIGNtok");
  }
  | SUB_ASSIGNtok {
      $$ = new assignment_operator_node(AssignType::SUB_ASSIGN);
      reductionOut("[p]: assignment_operator -> SUB_ASSIGNtok");
  }
  | LEFT_ASSIGNtok {
      $$ = new assignment_operator_node(AssignType::LEFT_ASSIGN);
      reductionOut("[p]: assignment_operator -> LEFT_ASSIGNtok");
  }
  | RIGHT_ASSIGNtok {
      $$ = new assignment_operator_node(AssignType::RIGHT_ASSIGN);
      reductionOut("[p]: assignment_operator -> RIGHT_ASSIGNtok");
  }
  | AND_ASSIGNtok {
      $$ = new assignment_operator_node(AssignType::AND_ASSIGN);
      reductionOut("[p]: assignment_operator -> AND_ASSIGNtok");
  }
  | XOR_ASSIGNtok {
      $$ = new assignment_operator_node(AssignType::XOR_ASSIGN);
      reductionOut("[p]: assignment_operator -> XOR_ASSIGNtok");
  }
  | OR_ASSIGNtok {
      $$ = new assignment_operator_node(AssignType::OR_ASSIGN);
      reductionOut("[p]: assignment_operator -> OR_ASSIGNtok");
  }
  ;

conditional_expression
  : logical_or_expression {
      reductionOut("[p]: conditional_expression -> logical_or_expression");
  }
  | logical_or_expression QUESTION_MARKtok expression COLONtok conditional_expression {
      reductionOut("[p]: conditional_expression -> logical_or_expression QUESTION_MARKtok expression COLONtok conditional_expression");
  }
  ;

constant_expression
  : conditional_expression {
      reductionOut("[p]: constant_expression -> conditional_expression");
  }
  ;

logical_or_expression
  : logical_and_expression {
      reductionOut("[p]: logical_or_expression -> logical_and_expression");
  }
  | logical_or_expression OR_OPtok logical_and_expression {
      reductionOut("[p]: logical_or_expression -> logical_or_expression OR_OPtok logical_and_expression");
  }
  ;

logical_and_expression
  : inclusive_or_expression {
      reductionOut("[p]: logical_and_expression -> inclusive_or_expression");
  }
  | logical_and_expression AND_OPtok inclusive_or_expression {
      reductionOut("[p]: logical_and_expression -> logical_and_expression AND_OPtok inclusive_or_expression");
  }
  ;

inclusive_or_expression
  : exclusive_or_expression {
      reductionOut("[p]: inclusive_or_expression -> exclusive_or_expression");
  }
  | inclusive_or_expression PIPEtok exclusive_or_expression {
      reductionOut("[p]: inclusive_or_expression -> inclusive_or_expression PIPEtok exclusive_or_expression");
  }
  ;

exclusive_or_expression
  : and_expression {
      reductionOut("[p]: exclusive_or_expression -> and_expression");
  }
  | exclusive_or_expression UP_CARROTtok and_expression {
      reductionOut("[p]: exclusive_or_expression -> exclusive_or_expression UP_CARROTtok and_expression");
  }
  ;

and_expression
  : equality_expression {
      reductionOut("[p]: and_expression -> equality_expression");
  }
  | and_expression UNARY_ANDtok equality_expression {
      reductionOut("[p]: and_expression -> and_expression UNARY_ANDtok equality_expression");
  }
  ;

equality_expression
  : relational_expression {
      $$ = new equality_expression_node(dynamic_cast<relational_expression_node*>($1));
      reductionOut("[p]: equality_expression -> relational_expression");
  }
  | equality_expression EQ_OPtok relational_expression {
      $$ = new equality_expression_node(dynamic_cast<equality_expression_node*>($1),OpType::EQ,dynamic_cast<relational_expression_node*>($3));
      reductionOut("[p]: equality_expression -> equality_expression EQ_OPtok relational_expression");
  }
  | equality_expression NE_OPtok relational_expression {
      reductionOut("[p]: equality_expression -> equality_expression NE_OPtok relational_expression");
  }
  ;

relational_expression
  : shift_expression {
      $$ = new relational_expression_node(dynamic_cast<shift_expression_node*>($1));
      reductionOut("[p]: relational_expression -> shift_expression");
  }
  | relational_expression LEFT_ANGLEtok shift_expression {
      $$ = new relational_expression_node(dynamic_cast<relational_expression_node*>($1),OpType::L,dynamic_cast<shift_expression_node*>($3));
      reductionOut("[p]: relational_expression -> relational_expression LEFT_ANGLEtok shift_expression");
  }
  | relational_expression RIGHT_ANGLEtok shift_expression {
      $$ = new relational_expression_node(dynamic_cast<relational_expression_node*>($1),OpType::G,dynamic_cast<shift_expression_node*>($3));
      reductionOut("[p]: relational_expression -> relational_expression RIGHT_ANGLEtok shift_expression");
  }
  | relational_expression LE_OPtok shift_expression {
      $$ = new relational_expression_node(dynamic_cast<relational_expression_node*>($1),OpType::LE,dynamic_cast<shift_expression_node*>($3));
      reductionOut("[p]: relational_expression -> relational_expression LE_OPtok shift_expression");
  }
  | relational_expression GE_OPtok shift_expression {
      $$ = new relational_expression_node(dynamic_cast<relational_expression_node*>($1),OpType::GE,dynamic_cast<shift_expression_node*>($3));
      reductionOut("[p]: relational_expression -> relational_expression GE_OPtok shift_expression");
  }
  ;

shift_expression
  : additive_expression {
      $$ = new shift_expression_node(dynamic_cast<additive_expression_node*>($1));
      reductionOut("[p]: shift_expression -> additive_expression");
  }
  | shift_expression LEFT_OPtok additive_expression {
      $$ = new shift_expression_node(dynamic_cast<shift_expression_node*>($1),OpType::LEFT_OP, dynamic_cast<additive_expression_node*>($3));
      reductionOut("[p]: shift_expression -> shift_expression LEFT_OPtok additive_expression");
  }
  | shift_expression RIGHT_OPtok additive_expression {
      $$ = new shift_expression_node(dynamic_cast<shift_expression_node*>($1),OpType::RIGHT_OP, dynamic_cast<additive_expression_node*>($3));
      reductionOut("[p]: shift_expression -> shift_expression RIGHT_OPtok additive_expression");
  }
  ;

additive_expression
  : multiplicative_expression {
      $$ = new additive_expression_node(dynamic_cast<multiplicative_expression_node*>($1));
      reductionOut("[p]: additive_expression -> multiplicative_expression");
  }
  | additive_expression UNARY_PLUStok multiplicative_expression {
      $$ = new additive_expression_node(dynamic_cast<additive_expression_node*>($1),OpType::PLUS,dynamic_cast<multiplicative_expression_node*>($3));
      reductionOut("[p]: additive_expression -> additive_expression UNARY_PLUStok multiplicative_expression");
  }
  | additive_expression UNARY_MINUStok multiplicative_expression {
      $$ = new additive_expression_node(dynamic_cast<additive_expression_node*>($1),OpType::MINUS,dynamic_cast<multiplicative_expression_node*>($3));
      reductionOut("[p]: additive_expression -> additive_expression UNARY_MINUStok multiplicative_expression");
  }
  ;

multiplicative_expression
  : cast_expression {
      $$ = new multiplicative_expression_node(dynamic_cast<cast_expression_node*>($1));
      reductionOut("[p]: multiplicative_expression -> cast_expression");
  }
  | multiplicative_expression UNARY_ASTERISKtok cast_expression {
      $$ = new multiplicative_expression_node(dynamic_cast<multiplicative_expression_node*>($1),OpType::ASTERISK,dynamic_cast<cast_expression_node*>($3));
      reductionOut("[p]: multiplicative_expression -> multiplicative_expression UNARY_ASTERISKtok cast_expression");
  }
  | multiplicative_expression FORWARD_SLASHtok cast_expression {
      $$ = new multiplicative_expression_node(dynamic_cast<multiplicative_expression_node*>($1),OpType::DIV,dynamic_cast<cast_expression_node*>($3));
      reductionOut("[p]: multiplicative_expression -> multiplicative_expression FORWARD_SLASHtok cast_expression");
  }
  | multiplicative_expression PERCENTtok cast_expression {
      $$ = new multiplicative_expression_node(dynamic_cast<multiplicative_expression_node*>($1),OpType::MOD,dynamic_cast<cast_expression_node*>($3));
      reductionOut("[p]: multiplicative_expression -> multiplicative_expression PERCENTtok cast_expression");
  }
  ;

cast_expression
  : unary_expression {
      $$ = new cast_expression_node(dynamic_cast<unary_expression_node*>($1));
      reductionOut("[p]: cast_expression -> unary_expression");
  }
  | OPEN_PARENtok type_name CLOSE_PARENtok cast_expression {
      reductionOut("[p]: cast_expression -> OPEN_PARENtok type_name CLOSE_PARENtok cast_expression");
  }
  ;

unary_expression
  : postfix_expression {
      $$ = new unary_expression_node(dynamic_cast<postfix_expression_node*>($1));
      reductionOut("[p]: unary_expression -> postfix_expression");
  }
  | INC_OPtok unary_expression {
      $$ = new unary_expression_node(OpType::INC,dynamic_cast<unary_expression_node*>($2));
      reductionOut("[p]: unary_expression -> INC_OPtok unary_expression");
  }
  | DEC_OPtok unary_expression {
      $$ = new unary_expression_node(OpType::DEC,dynamic_cast<unary_expression_node*>($2));
      reductionOut("[p]: unary_expression -> DEC_OPtok unary_expression");
  }
  | unary_operator cast_expression {
      reductionOut("[p]: unary_expression -> unary_operator cast_expression");
  }
  | SIZEOFtok unary_expression {
      $$ = new unary_expression_node(OpType::SIZEOF,dynamic_cast<unary_expression_node*>($2));
      reductionOut("[p]: unary_expression -> SIZEOFtok unary_expression");
  }
  | SIZEOFtok OPEN_PARENtok type_name CLOSE_PARENtok {
      reductionOut("[p]: unary_expression -> SIZEOFtok OPEN_PARENtok type_name CLOSE_PARENtok");
  }
  ;

unary_operator
  : UNARY_ANDtok {
      $$ = new unary_operator_node(OpType::AND);
      reductionOut("[p]: unary_operator -> UNARY_ANDtok");
  }
  | UNARY_ASTERISKtok {
      $$ = new unary_operator_node(OpType::ASTERISK);
      reductionOut("[p]: unary_operator -> UNARY_ASTERISKtok");
  }
  | UNARY_PLUStok {
      $$ = new unary_operator_node(OpType::PLUS);
      reductionOut("[p]: unary_operator -> UNARY_PLUStok");
  }
  | UNARY_MINUStok {
      $$ = new unary_operator_node(OpType::MINUS);
      reductionOut("[p]: unary_operator -> UNARY_MINUStok");
  }
  | UNARY_TILDEtok {
      $$ = new unary_operator_node(OpType::TILDE);
      reductionOut("[p]: unary_operator -> UNARY_TILDEtok");
  }
  | UNARY_BANGtok {
      $$ = new unary_operator_node(OpType::BANG);
      reductionOut("[p]: unary_operator -> UNARY_BANGtok");
  }
  ;

postfix_expression
  : primary_expression {
      $$ = new postfix_expression_node(dynamic_cast<primary_expression_node*>($1));
      reductionOut("[p]: postfix_expression -> primary_expression");
  }
  | postfix_expression OPEN_SQUAREtok expression CLOSE_SQUAREtok {
      $$ = new postfix_expression_node(dynamic_cast<postfix_expression_node*>($1),dynamic_cast<expression_node*>($3));
      reductionOut("[p]: postfix_expression -> postfix_expression OPEN_SQUAREtok expression CLOSE_SQUAREtok");
  }
  | postfix_expression OPEN_PARENtok CLOSE_PARENtok {
      $$ = new postfix_expression_node(dynamic_cast<postfix_expression_node*>($1));
      reductionOut("[p]: postfix_expression -> postfix_expression OPEN_PARENtok CLOSE_PARENtok");
  }
  | postfix_expression OPEN_PARENtok argument_expression_list CLOSE_PARENtok {
      $$ = new postfix_expression_node(dynamic_cast<postfix_expression_node*>($1),dynamic_cast<argument_expression_list_node*>($3));
      reductionOut("[p]: postfix_expression -> postfix_expression OPEN_PARENtok argument_expression_list CLOSE_PARENtok");
  }
  | postfix_expression PERIODtok identifier {
      $$ = new postfix_expression_node(dynamic_cast<postfix_expression_node*>($1),PostOpType::PERIOD,$3);
      reductionOut("[p]: postfix_expression -> postfix_expression PERIODtok identifier");
  }
  | postfix_expression PTR_OPtok identifier {
      $$ = new postfix_expression_node(dynamic_cast<postfix_expression_node*>($1),PostOpType::PTR_OP,$3);
      reductionOut("[p]: postfix_expression -> postfix_expression PTR_OPtok identifier");
  }
  | postfix_expression INC_OPtok {
      $$ = new postfix_expression_node(dynamic_cast<postfix_expression_node*>($1),PostOpType::INC);
      reductionOut("[p]: postfix_expression -> postfix_expression INC_OPtok");
  }
  | postfix_expression DEC_OPtok {
      $$ = new postfix_expression_node(dynamic_cast<postfix_expression_node*>($1),PostOpType::DEC);
      reductionOut("[p]: postfix_expression -> postfix_expression DEC_OPtok");
  }
  ;

primary_expression
  : identifier {
      // use before declaration check
      if(!symTable.lookupSymbol($1)) {
        std::stringstream ss;
        ss << "[p]: ERROR: identifier \'" << $1 << "\' not found" << ", line " << linenum << " col " << colnum;
        error(ss.str());
      }

      decl.lightClear();   // erace symbols not in declaration
      insert_mode = false; // turn lookup mode on

      // ast node creation
      SymbolNode *sym = symTable.lookupSymbol($1);
      if(sym != NULL){
        $$ = new primary_expression_node(new identifier_node($1, sym));
      }
      // reduction complete
      reductionOut("[p]: primary_expression -> identifier");
  }
  | constant {
      $$ = new primary_expression_node(dynamic_cast<constant_node*>($1));
      reductionOut("[p]: primary_expression -> constant");
  }
  | string {
      $$ = new primary_expression_node(dynamic_cast<string_node*>($1));
      reductionOut("[p]: primary_expression -> string");
  }
  | OPEN_PARENtok expression CLOSE_PARENtok {
      $$ = new primary_expression_node(dynamic_cast<expression_node*>($2));
      reductionOut("[p]: primary_expression -> OPEN_PARENtok expression CLOSE_PARENtok");
  }
  ;

argument_expression_list
  : assignment_expression {
      $$ = new argument_expression_list_node(dynamic_cast<assignment_expression_node*>($1));
      reductionOut("[p]: argument_expression_list -> assignment_expression");
  }
  | argument_expression_list COMMAtok assignment_expression {
      dynamic_cast<argument_expression_list_node*>($1)->addAssignmentExpr(dynamic_cast<assignment_expression_node*>($3));
      $$ = $1;
      reductionOut("[p]: argument_expression_list -> argument_expression_list COMMAtok assignment_expression");
  }
  ;

constant
  : INTEGER_CONSTANTtok {
      $$ = new constant_node((int)$1);
      reductionOut("[p]: constant -> INTEGER_CONSTANTtok");
  }
  | CHARACTER_CONSTANTtok {
      $$ = new constant_node((char)$1);
      reductionOut("[p]: constant -> CHARACTER_CONSTANTtok");
  }
  | FLOATING_CONSTANTtok {
      $$ = new constant_node((float)$1);
      reductionOut("[p]: constant -> FLOATING_CONSTANTtok");
  }
  | ENUMERATION_CONSTANTtok {
      reductionOut("[p]: constant -> ENUMERATION_CONSTANTtok");
  }
  ;

string
  : STRING_LITERALtok {
      $$ = new string_node ($1);
      reductionOut("[p]: string -> STRING_LITERALtok");
  }
  ;

identifier
  : IDENTIFIERtok {
      // save to use later in declaration.cpp
      decl.pushID(std::string(yylval.sval));
      decl.pushLine(linenum);
      decl.pushCol(colnum);

      strcpy($$, $1);
      reductionOut("[p]: identifier -> IDENTIFIERtok");
  }
  ;

%%
/* user code ****************************************************************/
void error(const std::string& message) {
    yyerror(message.c_str());
    exit(1); // stop parsing
}
void yyerror(const char* message) {
    printf("%s\n", message);
}
void warning(const std::string& message){
  std::cout << message << std::endl;
}
// Simultaneous output to debugging and list_file
void reductionOut(const char* reductionCStr) {
    // Append the reduction to listFileName
    std::ofstream fout;
    fout.open(listFileName, std::ofstream::out | std::ofstream::app);
    fout << reductionCStr << std::endl;
    fout.close();

    // Optional debugging output
     reductionDebugger.debug(reductionCStr);
}
