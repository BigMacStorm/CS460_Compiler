/* definitions ****************************************************************/
%{
extern "C"{
  int yyparse();
  int yylex();
}
#include <stdio.h>
#include "SymbolTable.h"
#include "Debugger.h"

extern Debugger warningDebugger;
extern Debugger reductionDebugger;
extern SymbolTable symTable;
extern int yylineno;
extern char* yytext;

void yyerror(char* s);
%}

%union{
  char cval;
  int ival;
  double dval;
  long lval;
  unsigned long long ullval;
  char* sval;
  SymbolNode* symval;
 }

%token IDENTIFIERtok
%token INTEGER_CONSTANTtok FLOATING_CONSTANTtok CHARACTER_CONSTANTtok ENUMERATION_CONSTANTtok
%token STRING_LITERALtok
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
%token STRUCTtok UNIONtok ENUMtok ELIPSIStok RANGEtok

%token CASEtok DEFAULTtok IFtok ELSEtok SWITCHtok WHILEtok DOtok FORtok GOTOtok CONTINUEtok BREAKtok RETURNtok

%token ERRORtok

%start translation_unit

/* Grammar ruls and actions ***************************************************/
%%

translation_unit
  : external_declaration {
     reductionDebugger.debug("translation_unit -> external_declaration");
  }
  | translation_unit external_declaration {
    reductionDebugger.debug("translation_unit -> translation_unit external_declaration");
  }
  ;

external_declaration
  : function_definition {
    reductionDebugger.debug("external_declaration -> function_definition");
  }
  | declaration  {
    reductionDebugger.debug("external_declaration -> declaration");
  }
  ;

/*** scope productions *******************************************************
A start_scope is called before compound_statement and a end_scope is called
after compound_statement.
*****************************************************************************/
enter_scope
  : {symTable.pushTable();}
;
end_scope
  : {symTable.popTable();}
;

function_definition
  : declarator compound_statement {
      reductionDebugger.debug("function_definition -> declarator compound_statement");
      }
  | declarator declaration_list compound_statement {
      reductionDebugger.debug("function_definition -> declarator declaration_list compound_statement");
      }
  | declaration_specifiers declarator compound_statement {
      reductionDebugger.debug("function_definition -> declaration_specifiers declarator compound_statement");
    }
  | declaration_specifiers declarator declaration_list compound_statement {
       reductionDebugger.debug("function_definition -> declaration_specifiers declarator declaration_list compound_statement");
    }
  ;

declaration
  : declaration_specifiers SEMItok{
      reductionDebugger.debug("declaration -> declaration_specifiers SEMItok");
  }
  | declaration_specifiers init_declarator_list SEMItok{
      reductionDebugger.debug("declaration -> declaration_specifiers init_declarator_list SEMItok");
  }
  ;

declaration_list
  : declaration{
      reductionDebugger.debug("declaration_list -> declaration");
  }
  | declaration_list declaration{
      reductionDebugger.debug("declaration_list -> declaration_list declaration");
  }
  ;

declaration_specifiers
  : storage_class_specifier {
      reductionDebugger.debug("declaration_specifiers -> storage_class_specifier");
  }
  | storage_class_specifier declaration_specifiers  {
      reductionDebugger.debug("declaration_specifiers -> storage_class_specifier declaration_specifiers");
  }
  | type_specifier  {
      reductionDebugger.debug("declaration_specifiers -> type_specifier");
  }
  | type_specifier declaration_specifiers  {
      reductionDebugger.debug("declaration_specifiers -> type_specifier declaration_specifiers");
  }
  | type_qualifier  {
      reductionDebugger.debug("declaration_specifiers -> type_qualifier");
  }
  | type_qualifier declaration_specifiers  {
      reductionDebugger.debug("declaration_specifiers -> type_qualifier declaration_specifiers");
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
    reductionDebugger.debug("storage_class_specifier -> AUTOtok");
  }
  | REGISTERtok {
    reductionDebugger.debug("storage_class_specifier -> REGISTERtok");
  }
  | STATICtok {
    reductionDebugger.debug("storage_class_specifier -> STATICtok");
  }
  | EXTERNtok {
    reductionDebugger.debug("storage_class_specifier -> EXTERNtok");
  }
  | TYPEDEFtok {
    reductionDebugger.debug("storage_class_specifier -> TYPEDEFtok");
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
    reductionDebugger.debug("type_specifier -> VOIDtok");
  }
  | CHARtok {
    reductionDebugger.debug("type_specifier -> CHARtok");
  }
  | SHORTtok {
    reductionDebugger.debug("type_specifier -> SHORTtok");
  }
  | INTtok {
    reductionDebugger.debug("type_specifier -> INTtok");
  }
  | LONGtok  {
    reductionDebugger.debug("type_specifier -> LONGtok");
  }
  | FLOATtok  {
    reductionDebugger.debug("type_specifier -> FLOATtok");
  }
  | DOUBLEtok  {
    reductionDebugger.debug("type_specifier -> DOUBLEtok");
  }
  | SIGNEDtok  {
    reductionDebugger.debug("type_specifier -> SIGNEDtok");
  }
  | UNSIGNEDtok  {
    reductionDebugger.debug("type_specifier -> UNSIGNEDtok");
  }
  | struct_or_union_specifier  {
    reductionDebugger.debug("type_specifier -> struct_or_union_specifier");
  }
  | enum_specifier  {
    reductionDebugger.debug("type_specifier -> enum_specifier");
  }
  | TYPEDEF_NAMEtok  {
    reductionDebugger.debug("type_specifier -> TYPEDEF_NAMEtok");
  }
  ;

type_qualifier
  : CONSTtok {
    reductionDebugger.debug("type_qualifier -> CONSTtok");
  }
  | VOLATILEtok {
    reductionDebugger.debug("type_qualifier -> VOLATILEtok");
  }
  ;

struct_or_union_specifier
  : struct_or_union identifier OPEN_CURLYtok struct_declaration_list CLOSE_CURLYtok {
      reductionDebugger.debug("struct_or_union_specifier -> struct_or_union identifier OPEN_CURLYtok struct_declaration_list CLOSE_CURLYtok");
  }
  | struct_or_union OPEN_CURLYtok struct_declaration_list CLOSE_CURLYtok {
      reductionDebugger.debug("struct_or_union_specifier -> struct_or_union OPEN_CURLYtok struct_declaration_list CLOSE_CURLYtokk");
  }
  | struct_or_union identifier {
      // forward declaration
      reductionDebugger.debug("struct_or_union_specifier -> struct_or_union identifier");
  }
  ;

struct_or_union
  : STRUCTtok {
      reductionDebugger.debug("struct_or_union -> STRUCTtok");
  }
  | UNIONtok {
      reductionDebugger.debug("struct_or_union -> UNIONtok");
  }
  ;

struct_declaration_list
  : struct_declaration {
      reductionDebugger.debug("struct_declaration_list -> struct_declaration");
  }
  | struct_declaration_list struct_declaration {
      reductionDebugger.debug("struct_declaration_list -> struct_declaration_list struct_declaration");
  }
  ;

init_declarator_list
  : init_declarator {
      reductionDebugger.debug("init_declarator_list -> init_declarator");
  }
  | init_declarator_list COMMAtok init_declarator {
      // multiple single line declarations
      reductionDebugger.debug("init_declarator_list -> init_declarator_list COMMAtok init_declarator");
  }
  ;

init_declarator
  : declarator {
      reductionDebugger.debug("init_declarator -> declarator");
  }
  | declarator EQUALtok initializer {
      // initialize the variable
      reductionDebugger.debug("init_declarator -> declarator EQUALtok initializer");
  }
  ;

struct_declaration
  : specifier_qualifier_list struct_declarator_list SEMItok {
      reductionDebugger.debug("struct_declaration -> specifier_qualifier_list struct_declarator_list SEMItok");
  }
  ;

specifier_qualifier_list
  : type_specifier {
      reductionDebugger.debug("specifier_qualifier_list -> type_specifier");
  }
  | type_specifier specifier_qualifier_list {
      reductionDebugger.debug("specifier_qualifier_list -> type_specifier specifier_qualifier_list");
  }
  | type_qualifier {
      reductionDebugger.debug("specifier_qualifier_list -> type_qualifier");
  }
  | type_qualifier specifier_qualifier_list {
      reductionDebugger.debug("specifier_qualifier_list -> type_qualifier specifier_qualifier_list");
  }
  ;

struct_declarator_list
  : struct_declarator {
      reductionDebugger.debug("struct_declarator_list -> struct_declarator");
  }
  | struct_declarator_list COMMAtok struct_declarator {
      reductionDebugger.debug("struct_declarator_list -> struct_declarator_list COMMAtok struct_declarator");
  }
  ;

struct_declarator
  : declarator {
      reductionDebugger.debug("struct_declarator -> declarator");
  }
  | COLONtok constant_expression {
      reductionDebugger.debug("struct_declarator -> COLONtok constant_expression");
  }
  | declarator COLONtok constant_expression {
      reductionDebugger.debug("struct_declarator -> declarator COLONtok constant_expression");
  }
  ;

enum_specifier
  : ENUMtok OPEN_CURLYtok enumerator_list CLOSE_CURLYtok {
      reductionDebugger.debug("enum_specifier -> ENUMtok OPEN_CURLYtok enumerator_list CLOSE_CURLYtok");
  }
  | ENUMtok identifier OPEN_CURLYtok enumerator_list CLOSE_CURLYtok {
      reductionDebugger.debug("enum_specifier -> ENUMtok identifier OPEN_CURLYtok enumerator_list CLOSE_CURLYtok");
  }
  | ENUMtok identifier {
      reductionDebugger.debug("enum_specifier -> ENUMtok identifier");
  }
  ;

enumerator_list
  : enumerator {
      reductionDebugger.debug("enumerator_list -> enumerator");
  }
  | enumerator_list COMMAtok enumerator {
      reductionDebugger.debug("enumerator_list -> enumerator_list COMMAtok enumerator");
  }
  ;

enumerator
  : identifier {
      reductionDebugger.debug("struct_declaration -> identifier");
  }
  | identifier EQUALtok constant_expression {
      reductionDebugger.debug("struct_declaration -> identifier EQUALtok constant_expression");
  }
  ;

declarator
  : direct_declarator {
      reductionDebugger.debug("declarator -> direct_declarator");
  }
  | pointer direct_declarator {
      // pointer mode
      reductionDebugger.debug("declarator -> pointer direct_declarator");
  }
  ;

direct_declarator
  : identifier {
      reductionDebugger.debug("direct_declarator -> identifier");
  }
  | OPEN_PARENtok declarator CLOSE_PARENtok {
      // e.g., int (*a)[COLS]
      reductionDebugger.debug("direct_declarator -> OPEN_PARENtok declarator CLOSE_PARENtok");
  }
  | direct_declarator OPEN_SQUAREtok CLOSE_SQUAREtok {
      // array mode
      reductionDebugger.debug("direct_declarator -> direct_declarator OPEN_SQUAREtok CLOSE_SQUAREtok");
  }
  | direct_declarator OPEN_SQUAREtok constant_expression CLOSE_SQUAREtok {
      // array mode
      reductionDebugger.debug("direct_declarator -> direct_declarator OPEN_SQUAREtok constant_expression CLOSE_SQUAREtok");
  }
  | direct_declarator OPEN_PARENtok CLOSE_PARENtok {
      // function mode
      reductionDebugger.debug("direct_declarator -> direct_declarator OPEN_PARENtok CLOSE_PARENtok");
  }
  | direct_declarator OPEN_PARENtok parameter_type_list CLOSE_PARENtok {
      // function mode
      reductionDebugger.debug("direct_declarator -> direct_declarator OPEN_PARENtok parameter_type_list CLOSE_PARENtok");
  }
  | direct_declarator OPEN_PARENtok identifier_list CLOSE_PARENtok {
      //
      reductionDebugger.debug("direct_declarator -> direct_declarator OPEN_PARENtok identifier_list CLOSE_PARENtok");
  }
  ;

pointer
  : UNARY_ASTERISKtok {
      // *
      reductionDebugger.debug("pointer -> UNARY_ASTERISKtok");
  }
  | UNARY_ASTERISKtok type_qualifier_list {
      // * cost/volatile
      reductionDebugger.debug("pointer -> UNARY_ASTERISKtok type_qualifier_list");
  }
  | UNARY_ASTERISKtok pointer {
      // ** ...
      reductionDebugger.debug("pointer -> UNARY_ASTERISKtok pointer");
  }
  | UNARY_ASTERISKtok type_qualifier_list pointer {
      // * cost/volatile * ...
      reductionDebugger.debug("pointer -> UNARY_ASTERISKtok type_qualifier_list pointer");
  }
  ;

type_qualifier_list
  : type_qualifier {
      reductionDebugger.debug("struct_declaration -> type_qualifier");
  }
  | type_qualifier_list type_qualifier {
      reductionDebugger.debug("struct_declaration -> type_qualifier_list type_qualifier");
  }
  ;

parameter_type_list
  : parameter_list {
      reductionDebugger.debug("parameter_type_list -> parameter_list");
  }
  | parameter_list COMMAtok ELIPSIStok {
      reductionDebugger.debug("parameter_type_list ->  parameter_list COMMAtok ELIPSIStok");
  }
  ;

parameter_list
  : parameter_declaration {
      reductionDebugger.debug("parameter_list -> parameter_declaration");
  }
  | parameter_list COMMAtok parameter_declaration {
      reductionDebugger.debug("parameter_list -> parameter_list COMMAtok parameter_declaration");
  }
  ;

parameter_declaration
  : declaration_specifiers declarator {
      reductionDebugger.debug("parameter_declaration -> declaration_specifiers declarator");
  }
  | declaration_specifiers {
      reductionDebugger.debug("parameter_declaration -> declaration_specifiers");
  }
  | declaration_specifiers abstract_declarator {
      reductionDebugger.debug("parameter_declaration -> declaration_specifiers abstract_declarator");
  }
  ;

identifier_list
  : identifier {
      reductionDebugger.debug("identifier_list -> identifier");
  }
  | identifier_list COMMAtok identifier {
      reductionDebugger.debug("identifier_list -> ");
  }
  ;

initializer
  : assignment_expression {
      reductionDebugger.debug("initializer -> assignment_expression");
  }
  | OPEN_CURLYtok initializer_list CLOSE_CURLYtok {
      reductionDebugger.debug("initializer -> OPEN_CURLYtok initializer_list CLOSE_CURLYtok");
  }
  | OPEN_CURLYtok initializer_list COMMAtok CLOSE_CURLYtok {
      reductionDebugger.debug("initializer -> OPEN_CURLYtok initializer_list COMMAtok CLOSE_CURLYtok");
  }
  ;

initializer_list
  : initializer {
      reductionDebugger.debug("initializer_list -> initializer");
  }
  | initializer_list COMMAtok initializer {
      reductionDebugger.debug("initializer_list -> initializer_list COMMAtok initializer");
  }
  ;

type_name
  : specifier_qualifier_list {
      reductionDebugger.debug("type_name -> specifier_qualifier_list");
  }
  | specifier_qualifier_list abstract_declarator {
      reductionDebugger.debug("type_name -> specifier_qualifier_list abstract_declarator");
  }
  ;

abstract_declarator
  : pointer {
      reductionDebugger.debug("abstract_declarator -> pointer");
  }
  | direct_abstract_declarator {
      reductionDebugger.debug("abstract_declarator -> direct_abstract_declarator");
  }
  | pointer direct_abstract_declarator {
      reductionDebugger.debug("abstract_declarator -> pointer direct_abstract_declarator");
  }
  ;

direct_abstract_declarator
  : OPEN_PARENtok abstract_declarator CLOSE_PARENtok {
      reductionDebugger.debug("direct_abstract_declarator -> OPEN_PARENtok abstract_declarator CLOSE_PARENtok");
  }
  | OPEN_SQUAREtok CLOSE_SQUAREtok {
      reductionDebugger.debug("direct_abstract_declarator -> OPEN_SQUAREtok CLOSE_SQUAREtok");
  }
  | OPEN_SQUAREtok constant_expression CLOSE_SQUAREtok {
      reductionDebugger.debug("direct_abstract_declarator -> OPEN_SQUAREtok constant_expression CLOSE_SQUAREtok");
  }
  | direct_abstract_declarator OPEN_SQUAREtok CLOSE_SQUAREtok {
      reductionDebugger.debug("direct_abstract_declarator -> direct_abstract_declarator OPEN_SQUAREtok CLOSE_SQUAREtok");
  }
  | direct_abstract_declarator OPEN_SQUAREtok constant_expression CLOSE_SQUAREtok {
      reductionDebugger.debug("direct_abstract_declarator -> direct_abstract_declarator OPEN_SQUAREtok constant_expression CLOSE_SQUAREtok");
  }
  | OPEN_PARENtok CLOSE_PARENtok {
      reductionDebugger.debug("direct_abstract_declarator -> OPEN_PARENtok CLOSE_PARENtok");
  }
  | OPEN_PARENtok parameter_type_list CLOSE_PARENtok {
      reductionDebugger.debug("direct_abstract_declarator -> OPEN_PARENtok parameter_type_list CLOSE_PARENtok");
  }
  | direct_abstract_declarator OPEN_PARENtok CLOSE_PARENtok {
      reductionDebugger.debug("direct_abstract_declarator -> direct_abstract_declarator OPEN_PARENtok CLOSE_PARENtok");
  }
  | direct_abstract_declarator OPEN_PARENtok parameter_type_list CLOSE_PARENtok {
      reductionDebugger.debug("direct_abstract_declarator -> direct_abstract_declarator OPEN_PARENtok parameter_type_list CLOSE_PARENtok");
  }
  ;

statement
  : labeled_statement {
      reductionDebugger.debug("statement -> labeled_statement");
  }
  | compound_statement {
      reductionDebugger.debug("statement -> compound_statement");
  }
  | expression_statement {
      reductionDebugger.debug("statement -> expression_statement");
  }
  | selection_statement {
      reductionDebugger.debug("statement -> selection_statement");
  }
  | iteration_statement {
      reductionDebugger.debug("statement -> iteration_statement");
  }
  | jump_statement {
      reductionDebugger.debug("statement -> jump_statement");
  }
  ;

labeled_statement
  : identifier COLONtok statement {
      reductionDebugger.debug("labeled_statement -> identifier COLONtok statement");
  }
  | CASEtok constant_expression COLONtok statement {
      reductionDebugger.debug("labeled_statement -> CASEtok constant_expression COLONtok statement");
  }
  | DEFAULTtok COLONtok statement {
      reductionDebugger.debug("labeled_statement -> DEFAULTtok COLONtok statement");
  }
  ;

expression_statement
  : SEMItok {
      reductionDebugger.debug("expression_statement -> SEMItok");
  }
  | expression SEMItok {
      reductionDebugger.debug("expression_statement -> expression SEMItok");
  }
  ;

compound_statement
  : OPEN_CURLYtok enter_scope CLOSE_CURLYtok end_scope{
      reductionDebugger.debug("compound_statement -> OPEN_CURLYtok CLOSE_CURLYtok");
  }
  | OPEN_CURLYtok enter_scope statement_list CLOSE_CURLYtok end_scope{
      reductionDebugger.debug("compound_statement -> OPEN_CURLYtok statement_list CLOSE_CURLYtok");
  }
  | OPEN_CURLYtok enter_scope declaration_list CLOSE_CURLYtok end_scope{
      reductionDebugger.debug("compound_statement -> OPEN_CURLYtok declaration_list CLOSE_CURLYtok");
  }
  | OPEN_CURLYtok enter_scope declaration_list statement_list CLOSE_CURLYtok end_scope{
      reductionDebugger.debug("compound_statement -> OPEN_CURLYtok declaration_list statement_list CLOSE_CURLYtok");
  }
  ;

statement_list
  : statement {
      reductionDebugger.debug("statement_list -> statement");
  }
  | statement_list statement {
      reductionDebugger.debug("statement_list -> statement_list statement");
  }
  ;

selection_statement
  : IFtok OPEN_PARENtok expression CLOSE_PARENtok statement {
      reductionDebugger.debug("selection_statement -> IFtok OPEN_PARENtok expression CLOSE_PARENtok statement");
  }
  | IFtok OPEN_PARENtok expression CLOSE_PARENtok statement ELSEtok statement {
      reductionDebugger.debug("selection_statement -> IFtok OPEN_PARENtok expression CLOSE_PARENtok statement ELSEtok statement");
  }
  | SWITCHtok OPEN_PARENtok expression CLOSE_PARENtok statement {
      reductionDebugger.debug("selection_statement -> SWITCHtok OPEN_PARENtok expression CLOSE_PARENtok statement");
  }
  ;

iteration_statement
  : WHILEtok OPEN_PARENtok expression CLOSE_PARENtok statement {
      reductionDebugger.debug("iteration_statement -> WHILEtok OPEN_PARENtok expression CLOSE_PARENtok statement");
  }
  | DOtok statement WHILEtok OPEN_PARENtok expression CLOSE_PARENtok SEMItok {
      reductionDebugger.debug("iteration_statement -> DOtok statement WHILEtok OPEN_PARENtok expression CLOSE_PARENtok SEMItok");
  }
  | FORtok OPEN_PARENtok SEMItok SEMItok CLOSE_PARENtok statement {
      reductionDebugger.debug("iteration_statement -> FORtok OPEN_PARENtok SEMItok SEMItok CLOSE_PARENtok statement");
  }
  | FORtok OPEN_PARENtok SEMItok SEMItok expression CLOSE_PARENtok statement {
      reductionDebugger.debug("iteration_statement -> FORtok OPEN_PARENtok SEMItok SEMItok expression CLOSE_PARENtok statement");
  }
  | FORtok OPEN_PARENtok SEMItok expression SEMItok CLOSE_PARENtok statement {
      reductionDebugger.debug("iteration_statement -> FORtok OPEN_PARENtok SEMItok expression SEMItok CLOSE_PARENtok statement");
  }
  | FORtok OPEN_PARENtok SEMItok expression SEMItok expression CLOSE_PARENtok statement {
      reductionDebugger.debug("iteration_statement -> FORtok OPEN_PARENtok SEMItok expression SEMItok expression CLOSE_PARENtok statement");
  }
  | FORtok OPEN_PARENtok expression SEMItok SEMItok CLOSE_PARENtok statement {
      reductionDebugger.debug("iteration_statement -> FORtok OPEN_PARENtok expression SEMItok SEMItok CLOSE_PARENtok statement");
  }
  | FORtok OPEN_PARENtok expression SEMItok SEMItok expression CLOSE_PARENtok statement {
      reductionDebugger.debug("iteration_statement -> FORtok OPEN_PARENtok expression SEMItok SEMItok expression CLOSE_PARENtok statement");
  }
  | FORtok OPEN_PARENtok expression SEMItok expression SEMItok CLOSE_PARENtok statement {
      reductionDebugger.debug("iteration_statement -> FORtok OPEN_PARENtok expression SEMItok expression SEMItok CLOSE_PARENtok statement");
  }
  | FORtok OPEN_PARENtok expression SEMItok expression SEMItok expression CLOSE_PARENtok statement {
      reductionDebugger.debug("iteration_statement -> FORtok OPEN_PARENtok expression SEMItok expression SEMItok expression CLOSE_PARENtok statement");
  }
  ;

jump_statement
  : GOTOtok identifier SEMItok {
      reductionDebugger.debug("jump_statement -> GOTOtok identifier SEMItok");
  }
  | CONTINUEtok SEMItok {
      reductionDebugger.debug("jump_statement -> CONTINUEtok SEMItok");
  }
  | BREAKtok SEMItok {
      reductionDebugger.debug("jump_statement -> BREAKtok SEMItok");
  }
  | RETURNtok SEMItok {
      reductionDebugger.debug("jump_statement ->  RETURNtok SEMItok");
  }
  | RETURNtok expression SEMItok {
      reductionDebugger.debug("jump_statement -> RETURNtok expression SEMItok");
  }
  ;

expression
  : assignment_expression {
      reductionDebugger.debug("expression -> assignment_expression");
  }
  | expression COMMAtok assignment_expression {
      reductionDebugger.debug("expression -> expression COMMAtok assignment_expression");
  }
  ;

assignment_expression
  : conditional_expression {
      reductionDebugger.debug("assignment_expression -> conditional_expression");
  }
  | unary_expression assignment_operator assignment_expression {
      reductionDebugger.debug("assignment_expression -> unary_expression assignment_operator assignment_expression");
  }
  ;

assignment_operator
  : EQUALtok {
      reductionDebugger.debug("assignment_operator -> EQUALtok");
  }
  | MUL_ASSIGNtok {
      reductionDebugger.debug("assignment_operator -> MUL_ASSIGNtok");
  }
  | DIV_ASSIGNtok {
      reductionDebugger.debug("assignment_operator -> DIV_ASSIGNtok");
  }
  | MOD_ASSIGNtok {
      reductionDebugger.debug("assignment_operator -> MOD_ASSIGNtok");
  }
  | ADD_ASSIGNtok {
      reductionDebugger.debug("assignment_operator -> ADD_ASSIGNtok");
  }
  | SUB_ASSIGNtok {
      reductionDebugger.debug("assignment_operator -> SUB_ASSIGNtok");
  }
  | LEFT_ASSIGNtok {
      reductionDebugger.debug("assignment_operator -> LEFT_ASSIGNtok");
  }
  | RIGHT_ASSIGNtok {
      reductionDebugger.debug("assignment_operator -> RIGHT_ASSIGNtok");
  }
  | AND_ASSIGNtok {
      reductionDebugger.debug("assignment_operator -> AND_ASSIGNtok");
  }
  | XOR_ASSIGNtok {
      reductionDebugger.debug("assignment_operator -> XOR_ASSIGNtok");
  }
  | OR_ASSIGNtok {
      reductionDebugger.debug("assignment_operator -> OR_ASSIGNtok");
  }
  ;

conditional_expression
  : logical_or_expression {
      reductionDebugger.debug("conditional_expression -> logical_or_expression");
  }
  | logical_or_expression QUESTION_MARKtok expression COLONtok conditional_expression {
      reductionDebugger.debug("conditional_expression -> logical_or_expression QUESTION_MARKtok expression COLONtok conditional_expression");
  }
  ;

constant_expression
  : conditional_expression {
      reductionDebugger.debug("constant_expression -> conditional_expression");
  }
  ;

logical_or_expression
  : logical_and_expression {
      reductionDebugger.debug("logical_or_expression -> logical_and_expression");
  }
  | logical_or_expression OR_OPtok logical_and_expression {
      reductionDebugger.debug("logical_or_expression -> logical_or_expression OR_OPtok logical_and_expression");
  }
  ;

logical_and_expression
  : inclusive_or_expression {
      reductionDebugger.debug("logical_and_expression -> inclusive_or_expression");
  }
  | logical_and_expression AND_OPtok inclusive_or_expression {
      reductionDebugger.debug("logical_and_expression -> logical_and_expression AND_OPtok inclusive_or_expression");
  }
  ;

inclusive_or_expression
  : exclusive_or_expression {
      reductionDebugger.debug("inclusive_or_expression -> exclusive_or_expression");
  }
  | inclusive_or_expression PIPEtok exclusive_or_expression {
      reductionDebugger.debug("inclusive_or_expression -> inclusive_or_expression PIPEtok exclusive_or_expression");
  }
  ;

exclusive_or_expression
  : and_expression {
      reductionDebugger.debug("exclusive_or_expression -> and_expression");
  }
  | exclusive_or_expression UP_CARROTtok and_expression {
      reductionDebugger.debug("exclusive_or_expression -> exclusive_or_expression UP_CARROTtok and_expression");
  }
  ;

and_expression
  : equality_expression {
      reductionDebugger.debug("and_expression -> equality_expression");
  }
  | and_expression UNARY_ANDtok equality_expression {
      reductionDebugger.debug("and_expression -> and_expression UNARY_ANDtok equality_expression");
  }
  ;

equality_expression
  : relational_expression {
      reductionDebugger.debug("equality_expression -> relational_expression");
  }
  | equality_expression EQ_OPtok relational_expression {
      reductionDebugger.debug("equality_expression -> equality_expression EQ_OPtok relational_expression");
  }
  | equality_expression NE_OPtok relational_expression {
      reductionDebugger.debug("equality_expression -> equality_expression NE_OPtok relational_expression");
  }
  ;

relational_expression
  : shift_expression {
      reductionDebugger.debug("relational_expression -> shift_expression");
  }
  | relational_expression LEFT_ANGLEtok shift_expression {
      reductionDebugger.debug("relational_expression -> relational_expression LEFT_ANGLEtok shift_expression");
  }
  | relational_expression RIGHT_ANGLEtok shift_expression {
      reductionDebugger.debug("relational_expression -> relational_expression RIGHT_ANGLEtok shift_expression");
  }
  | relational_expression LE_OPtok shift_expression {
      reductionDebugger.debug("relational_expression -> relational_expression LE_OPtok shift_expression");
  }
  | relational_expression GE_OPtok shift_expression {
      reductionDebugger.debug("relational_expression -> relational_expression GE_OPtok shift_expression");
  }
  ;

shift_expression
  : additive_expression {
      reductionDebugger.debug("shift_expression -> additive_expression");
  }
  | shift_expression LEFT_OPtok additive_expression {
      reductionDebugger.debug("shift_expression -> shift_expression LEFT_OPtok additive_expression");
  }
  | shift_expression RIGHT_OPtok additive_expression {
      reductionDebugger.debug("shift_expression -> shift_expression RIGHT_OPtok additive_expression");
  }
  ;

additive_expression
  : multiplicative_expression {
      reductionDebugger.debug("additive_expression -> multiplicative_expression");
  }
  | additive_expression UNARY_PLUStok multiplicative_expression {
      reductionDebugger.debug("additive_expression -> additive_expression UNARY_PLUStok multiplicative_expression");
  }
  | additive_expression UNARY_MINUStok multiplicative_expression {
      reductionDebugger.debug("additive_expression -> additive_expression UNARY_MINUStok multiplicative_expression");
  }
  ;

multiplicative_expression
  : cast_expression {
      reductionDebugger.debug("multiplicative_expression -> cast_expression");
  }
  | multiplicative_expression UNARY_ASTERISKtok cast_expression {
      reductionDebugger.debug("multiplicative_expression -> multiplicative_expression UNARY_ASTERISKtok cast_expression");
  }
  | multiplicative_expression FORWARD_SLASHtok cast_expression {
      reductionDebugger.debug("multiplicative_expression -> multiplicative_expression FORWARD_SLASHtok cast_expression");
  }
  | multiplicative_expression PERCENTtok cast_expression {
      reductionDebugger.debug("multiplicative_expression -> multiplicative_expression PERCENTtok cast_expression");
  }
  ;

cast_expression
  : unary_expression {
      reductionDebugger.debug("cast_expression -> unary_expression");
  }
  | OPEN_PARENtok type_name CLOSE_PARENtok cast_expression {
      reductionDebugger.debug("cast_expression -> OPEN_PARENtok type_name CLOSE_PARENtok cast_expression");
  }
  ;

unary_expression
  : postfix_expression {
      reductionDebugger.debug("unary_expression -> postfix_expression");
  }
  | INC_OPtok unary_expression {
      reductionDebugger.debug("unary_expression -> INC_OPtok unary_expression");
  }
  | DEC_OPtok unary_expression {
      reductionDebugger.debug("unary_expression -> DEC_OPtok unary_expression");
  }
  | unary_operator cast_expression {
      reductionDebugger.debug("unary_expression -> unary_operator cast_expression");
  }
  | SIZEOFtok unary_expression {
      reductionDebugger.debug("unary_expression -> SIZEOFtok unary_expression");
  }
  | SIZEOFtok OPEN_PARENtok type_name CLOSE_PARENtok {
      reductionDebugger.debug("unary_expression -> SIZEOFtok OPEN_PARENtok type_name CLOSE_PARENtok");
  }
  ;

unary_operator
  : UNARY_ANDtok {
      reductionDebugger.debug("unary_operator -> UNARY_ANDtok");
  }
  | UNARY_ASTERISKtok {
      reductionDebugger.debug("unary_operator -> UNARY_ASTERISKtok");
  }
  | UNARY_PLUStok {
      reductionDebugger.debug("unary_operator -> UNARY_PLUStok");
  }
  | UNARY_MINUStok {
      reductionDebugger.debug("unary_operator -> UNARY_MINUStok");
  }
  | UNARY_TILDEtok {
      reductionDebugger.debug("unary_operator -> UNARY_TILDEtok");
  }
  | UNARY_BANGtok {
      reductionDebugger.debug("unary_operator -> UNARY_BANGtok");
  }
  ;

postfix_expression
  : primary_expression {
      reductionDebugger.debug("postfix_expression -> primary_expression");
  }
  | postfix_expression OPEN_SQUAREtok expression CLOSE_SQUAREtok {
      reductionDebugger.debug("postfix_expression -> postfix_expression OPEN_SQUAREtok expression CLOSE_SQUAREtok");
  }
  | postfix_expression OPEN_PARENtok CLOSE_PARENtok {
      reductionDebugger.debug("postfix_expression -> postfix_expression OPEN_PARENtok CLOSE_PARENtok");
  }
  | postfix_expression OPEN_PARENtok argument_expression_list CLOSE_PARENtok {
      reductionDebugger.debug("postfix_expression -> postfix_expression OPEN_PARENtok argument_expression_list CLOSE_PARENtok");
  }
  | postfix_expression PERIODtok identifier {
      reductionDebugger.debug("postfix_expression -> postfix_expression PERIODtok identifier");
  }
  | postfix_expression PTR_OPtok identifier {
      reductionDebugger.debug("postfix_expression -> postfix_expression PTR_OPtok identifier");
  }
  | postfix_expression INC_OPtok {
      reductionDebugger.debug("postfix_expression -> postfix_expression INC_OPtok");
  }
  | postfix_expression DEC_OPtok {
      reductionDebugger.debug("postfix_expression -> postfix_expression DEC_OPtok");
  }
  ;

primary_expression
  : identifier {
      reductionDebugger.debug("primary_expression -> identifier");
  }
  | constant {
      reductionDebugger.debug("primary_expression -> constant");
  }
  | string {
      reductionDebugger.debug("primary_expression -> string");
  }
  | OPEN_PARENtok expression CLOSE_PARENtok {
      reductionDebugger.debug("primary_expression -> OPEN_PARENtok expression CLOSE_PARENtok");
  }
  ;

argument_expression_list
  : assignment_expression {
      reductionDebugger.debug("argument_expression_list -> assignment_expression");
  }
  | argument_expression_list COMMAtok assignment_expression {
      reductionDebugger.debug("argument_expression_list -> argument_expression_list COMMAtok assignment_expression");
  }
  ;

constant
  : INTEGER_CONSTANTtok {
      reductionDebugger.debug("constant -> INTEGER_CONSTANTtok");
  }
  | CHARACTER_CONSTANTtok {
      reductionDebugger.debug("constant -> CHARACTER_CONSTANTtok");
  }
  | FLOATING_CONSTANTtok {
      reductionDebugger.debug("constant -> FLOATING_CONSTANTtok");
  }
  | ENUMERATION_CONSTANTtok {
      reductionDebugger.debug("constant -> ENUMERATION_CONSTANTtok");
  }
  ;

string
  : STRING_LITERALtok {
      reductionDebugger.debug("string -> STRING_LITERALtok");
  }
  ;

identifier
  : IDENTIFIERtok {
      reductionDebugger.debug("identifier -> IDENTIFIERtok");
  }
  ;

%%
/* user code ****************************************************************/
void yyerror (char* s) {
    fflush(stdout);
    printf("%s on line %d - %s\n", s, yylineno, yytext);
}
