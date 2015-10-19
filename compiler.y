/* definitions ****************************************************************/
%{
extern "C"{
  int yyparse();
  int yylex();
}
#include <stdio.h>
#include <fstream>
#include <string.h>
#include "SymbolTable.h"
#include "Debugger.h"
#include "Spec.h"

extern Debugger warningDebugger;
extern Debugger reductionDebugger;
extern SymbolTable symTable;
extern int yylineno;
extern char* yytext;

// File for writing source lines and reductions to
const char* LIST_FILE = "list_file";

// Simultaneous output to debugging and list_file
void reductionOut(const char* reductionCStr) {
    // Append the reduction to LIST_FILE
    std::ofstream fout;
    fout.open(LIST_FILE, std::ofstream::out | std::ofstream::app);
    fout << reductionCStr << std::endl;
    fout.close();

    // Optional debugging output
    reductionDebugger.debug(reductionCStr);
}

void yyerror(char* s);
%}

%union{
  char cval;
  int ival;
  double dval;
  long lval;
  unsigned long long ullval;
  //char* sval;
  char sval[100]; // Changing this to an array fixed a strcpy segfault
  SymbolNode* symval;

  SpecName::TypeKind tkval;
 }

// Tokens
%token <sval> IDENTIFIERtok
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
%token <tkval> STRUCTtok
%token <tkval> UNIONtok
%token ENUMtok ELIPSIStok RANGEtok

%token CASEtok DEFAULTtok IFtok ELSEtok SWITCHtok WHILEtok DOtok FORtok GOTOtok CONTINUEtok BREAKtok RETURNtok

%token ERRORtok

// Nonterminals
%type <sval> identifier
%type <tkval> struct_or_union

%start translation_unit

/* Grammar ruls and actions ***************************************************/
%%

translation_unit
  : external_declaration {
     reductionOut("translation_unit -> external_declaration");
  }
  | translation_unit external_declaration {
    reductionOut("translation_unit -> translation_unit external_declaration");
  }
  ;

external_declaration
  : function_definition {
    reductionOut("external_declaration -> function_definition");
  }
  | declaration  {
    reductionOut("external_declaration -> declaration");
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
      reductionOut("function_definition -> declarator compound_statement");
      }
  | declarator declaration_list compound_statement {
      reductionOut("function_definition -> declarator declaration_list compound_statement");
      }
  | declaration_specifiers declarator compound_statement {
      reductionOut("function_definition -> declaration_specifiers declarator compound_statement");
    }
  | declaration_specifiers declarator declaration_list compound_statement {
       reductionOut("function_definition -> declaration_specifiers declarator declaration_list compound_statement");
    }
  ;

declaration
  : declaration_specifiers SEMItok{
      reductionOut("declaration -> declaration_specifiers SEMItok");
  }
  | declaration_specifiers init_declarator_list SEMItok{
      reductionOut("declaration -> declaration_specifiers init_declarator_list SEMItok");
  }
  ;

declaration_list
  : declaration{
      reductionOut("declaration_list -> declaration");
  }
  | declaration_list declaration{
      reductionOut("declaration_list -> declaration_list declaration");
  }
  ;

declaration_specifiers
  : storage_class_specifier {
      reductionOut("declaration_specifiers -> storage_class_specifier");
  }
  | storage_class_specifier declaration_specifiers  {
      reductionOut("declaration_specifiers -> storage_class_specifier declaration_specifiers");
  }
  | type_specifier  {
      reductionOut("declaration_specifiers -> type_specifier");
  }
  | type_specifier declaration_specifiers  {
      reductionOut("declaration_specifiers -> type_specifier declaration_specifiers");
  }
  | type_qualifier  {
      reductionOut("declaration_specifiers -> type_qualifier");
  }
  | type_qualifier declaration_specifiers  {
      reductionOut("declaration_specifiers -> type_qualifier declaration_specifiers");
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
    reductionOut("storage_class_specifier -> AUTOtok");
  }
  | REGISTERtok {
    reductionOut("storage_class_specifier -> REGISTERtok");
  }
  | STATICtok {
    reductionOut("storage_class_specifier -> STATICtok");
  }
  | EXTERNtok {
    reductionOut("storage_class_specifier -> EXTERNtok");
  }
  | TYPEDEFtok {
    reductionOut("storage_class_specifier -> TYPEDEFtok");
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
    reductionOut("type_specifier -> VOIDtok");
  }
  | CHARtok {
    reductionOut("type_specifier -> CHARtok");
  }
  | SHORTtok {
    reductionOut("type_specifier -> SHORTtok");
  }
  | INTtok {
    reductionOut("type_specifier -> INTtok");
  }
  | LONGtok  {
    reductionOut("type_specifier -> LONGtok");
  }
  | FLOATtok  {
    reductionOut("type_specifier -> FLOATtok");
  }
  | DOUBLEtok  {
    reductionOut("type_specifier -> DOUBLEtok");
  }
  | SIGNEDtok  {
    reductionOut("type_specifier -> SIGNEDtok");
  }
  | UNSIGNEDtok  {
    reductionOut("type_specifier -> UNSIGNEDtok");
  }
  | struct_or_union_specifier  {
    reductionOut("type_specifier -> struct_or_union_specifier");
  }
  | enum_specifier  {
    reductionOut("type_specifier -> enum_specifier");
  }
  | TYPEDEF_NAMEtok  {
    reductionOut("type_specifier -> TYPEDEF_NAMEtok");
  }
  ;

type_qualifier
  : CONSTtok {
    reductionOut("type_qualifier -> CONSTtok");
  }
  | VOLATILEtok {
    reductionOut("type_qualifier -> VOLATILEtok");
  }
  ;

struct_or_union_specifier
  : struct_or_union identifier OPEN_CURLYtok struct_declaration_list CLOSE_CURLYtok {
      reductionOut("struct_or_union_specifier -> struct_or_union identifier OPEN_CURLYtok struct_declaration_list CLOSE_CURLYtok");

      bool redefinition = false;
      bool shadowing = false;

      if(symTable.lookupTopTable($2)) {
        redefinition = true;
        printf("Here\n");
        // Redefinition; fatal error
        yyerror("error: redefinition");  // Note: Make this message better
      }

      // Can't shadow struct / union types
      /*
      else if(symTable.lookUpShadowedSymbol($2)) {
        shadowing = true;
        // Shadowing; warning
        printf("warning: shadowing\n");  // Note: Make this message better
      }
      */

      // Put the new declaration in the symbol table
      symTable.insertSymbol($2, new SymbolNode($2, new Spec($1)));
  }
  | struct_or_union OPEN_CURLYtok struct_declaration_list CLOSE_CURLYtok {
      reductionOut("struct_or_union_specifier -> struct_or_union OPEN_CURLYtok struct_declaration_list CLOSE_CURLYtokk");
  }
  | struct_or_union identifier {
      // forward declaration
      reductionOut("struct_or_union_specifier -> struct_or_union identifier");
  }
  ;

struct_or_union
  : STRUCTtok {
      reductionOut("struct_or_union -> STRUCTtok");
      $$ = SpecName::TypeKind::Struct;
  }
  | UNIONtok {
      reductionOut("struct_or_union -> UNIONtok");
      $$ = SpecName::TypeKind::Union;
  }
  ;

struct_declaration_list
  : struct_declaration {
      reductionOut("struct_declaration_list -> struct_declaration");
  }
  | struct_declaration_list struct_declaration {
      reductionOut("struct_declaration_list -> struct_declaration_list struct_declaration");
  }
  ;

init_declarator_list
  : init_declarator {
      reductionOut("init_declarator_list -> init_declarator");
  }
  | init_declarator_list COMMAtok init_declarator {
      // multiple single line declarations
      reductionOut("init_declarator_list -> init_declarator_list COMMAtok init_declarator");
  }
  ;

init_declarator
  : declarator {
      reductionOut("init_declarator -> declarator");
  }
  | declarator EQUALtok initializer {
      // initialize the variable
      reductionOut("init_declarator -> declarator EQUALtok initializer");
  }
  ;

struct_declaration
  : specifier_qualifier_list struct_declarator_list SEMItok {
      reductionOut("struct_declaration -> specifier_qualifier_list struct_declarator_list SEMItok");
  }
  ;

specifier_qualifier_list
  : type_specifier {
      reductionOut("specifier_qualifier_list -> type_specifier");
  }
  | type_specifier specifier_qualifier_list {
      reductionOut("specifier_qualifier_list -> type_specifier specifier_qualifier_list");
  }
  | type_qualifier {
      reductionOut("specifier_qualifier_list -> type_qualifier");
  }
  | type_qualifier specifier_qualifier_list {
      reductionOut("specifier_qualifier_list -> type_qualifier specifier_qualifier_list");
  }
  ;

struct_declarator_list
  : struct_declarator {
      reductionOut("struct_declarator_list -> struct_declarator");
  }
  | struct_declarator_list COMMAtok struct_declarator {
      reductionOut("struct_declarator_list -> struct_declarator_list COMMAtok struct_declarator");
  }
  ;

struct_declarator
  : declarator {
      reductionOut("struct_declarator -> declarator");
  }
  | COLONtok constant_expression {
      reductionOut("struct_declarator -> COLONtok constant_expression");
  }
  | declarator COLONtok constant_expression {
      reductionOut("struct_declarator -> declarator COLONtok constant_expression");
  }
  ;

enum_specifier
  : ENUMtok OPEN_CURLYtok enumerator_list CLOSE_CURLYtok {
      reductionOut("enum_specifier -> ENUMtok OPEN_CURLYtok enumerator_list CLOSE_CURLYtok");
  }
  | ENUMtok identifier OPEN_CURLYtok enumerator_list CLOSE_CURLYtok {
      reductionOut("enum_specifier -> ENUMtok identifier OPEN_CURLYtok enumerator_list CLOSE_CURLYtok");
  }
  | ENUMtok identifier {
      reductionOut("enum_specifier -> ENUMtok identifier");
  }
  ;

enumerator_list
  : enumerator {
      reductionOut("enumerator_list -> enumerator");
  }
  | enumerator_list COMMAtok enumerator {
      reductionOut("enumerator_list -> enumerator_list COMMAtok enumerator");
  }
  ;

enumerator
  : identifier {
      reductionOut("struct_declaration -> identifier");
  }
  | identifier EQUALtok constant_expression {
      reductionOut("struct_declaration -> identifier EQUALtok constant_expression");
  }
  ;

declarator
  : direct_declarator {
      reductionOut("declarator -> direct_declarator");
  }
  | pointer direct_declarator {
      // pointer mode
      reductionOut("declarator -> pointer direct_declarator");
  }
  ;

direct_declarator
  : identifier {
      reductionOut("direct_declarator -> identifier");
  }
  | OPEN_PARENtok declarator CLOSE_PARENtok {
      // e.g., int (*a)[COLS]
      reductionOut("direct_declarator -> OPEN_PARENtok declarator CLOSE_PARENtok");
  }
  | direct_declarator OPEN_SQUAREtok CLOSE_SQUAREtok {
      // array mode
      reductionOut("direct_declarator -> direct_declarator OPEN_SQUAREtok CLOSE_SQUAREtok");
  }
  | direct_declarator OPEN_SQUAREtok constant_expression CLOSE_SQUAREtok {
      // array mode
      reductionOut("direct_declarator -> direct_declarator OPEN_SQUAREtok constant_expression CLOSE_SQUAREtok");
  }
  | direct_declarator OPEN_PARENtok CLOSE_PARENtok {
      // function mode
      reductionOut("direct_declarator -> direct_declarator OPEN_PARENtok CLOSE_PARENtok");
  }
  | direct_declarator OPEN_PARENtok parameter_type_list CLOSE_PARENtok {
      // function mode
      reductionOut("direct_declarator -> direct_declarator OPEN_PARENtok parameter_type_list CLOSE_PARENtok");
  }
  | direct_declarator OPEN_PARENtok identifier_list CLOSE_PARENtok {
      //
      reductionOut("direct_declarator -> direct_declarator OPEN_PARENtok identifier_list CLOSE_PARENtok");
  }
  ;

pointer
  : UNARY_ASTERISKtok {
      // *
      reductionOut("pointer -> UNARY_ASTERISKtok");
  }
  | UNARY_ASTERISKtok type_qualifier_list {
      // * cost/volatile
      reductionOut("pointer -> UNARY_ASTERISKtok type_qualifier_list");
  }
  | UNARY_ASTERISKtok pointer {
      // ** ...
      reductionOut("pointer -> UNARY_ASTERISKtok pointer");
  }
  | UNARY_ASTERISKtok type_qualifier_list pointer {
      // * cost/volatile * ...
      reductionOut("pointer -> UNARY_ASTERISKtok type_qualifier_list pointer");
  }
  ;

type_qualifier_list
  : type_qualifier {
      reductionOut("struct_declaration -> type_qualifier");
  }
  | type_qualifier_list type_qualifier {
      reductionOut("struct_declaration -> type_qualifier_list type_qualifier");
  }
  ;

parameter_type_list
  : parameter_list {
      reductionOut("parameter_type_list -> parameter_list");
  }
  | parameter_list COMMAtok ELIPSIStok {
      reductionOut("parameter_type_list ->  parameter_list COMMAtok ELIPSIStok");
  }
  ;

parameter_list
  : parameter_declaration {
      reductionOut("parameter_list -> parameter_declaration");
  }
  | parameter_list COMMAtok parameter_declaration {
      reductionOut("parameter_list -> parameter_list COMMAtok parameter_declaration");
  }
  ;

parameter_declaration
  : declaration_specifiers declarator {
      reductionOut("parameter_declaration -> declaration_specifiers declarator");
  }
  | declaration_specifiers {
      reductionOut("parameter_declaration -> declaration_specifiers");
  }
  | declaration_specifiers abstract_declarator {
      reductionOut("parameter_declaration -> declaration_specifiers abstract_declarator");
  }
  ;

identifier_list
  : identifier {
      reductionOut("identifier_list -> identifier");
  }
  | identifier_list COMMAtok identifier {
      reductionOut("identifier_list -> ");
  }
  ;

initializer
  : assignment_expression {
      reductionOut("initializer -> assignment_expression");
  }
  | OPEN_CURLYtok initializer_list CLOSE_CURLYtok {
      reductionOut("initializer -> OPEN_CURLYtok initializer_list CLOSE_CURLYtok");
  }
  | OPEN_CURLYtok initializer_list COMMAtok CLOSE_CURLYtok {
      reductionOut("initializer -> OPEN_CURLYtok initializer_list COMMAtok CLOSE_CURLYtok");
  }
  ;

initializer_list
  : initializer {
      reductionOut("initializer_list -> initializer");
  }
  | initializer_list COMMAtok initializer {
      reductionOut("initializer_list -> initializer_list COMMAtok initializer");
  }
  ;

type_name
  : specifier_qualifier_list {
      reductionOut("type_name -> specifier_qualifier_list");
  }
  | specifier_qualifier_list abstract_declarator {
      reductionOut("type_name -> specifier_qualifier_list abstract_declarator");
  }
  ;

abstract_declarator
  : pointer {
      reductionOut("abstract_declarator -> pointer");
  }
  | direct_abstract_declarator {
      reductionOut("abstract_declarator -> direct_abstract_declarator");
  }
  | pointer direct_abstract_declarator {
      reductionOut("abstract_declarator -> pointer direct_abstract_declarator");
  }
  ;

direct_abstract_declarator
  : OPEN_PARENtok abstract_declarator CLOSE_PARENtok {
      reductionOut("direct_abstract_declarator -> OPEN_PARENtok abstract_declarator CLOSE_PARENtok");
  }
  | OPEN_SQUAREtok CLOSE_SQUAREtok {
      reductionOut("direct_abstract_declarator -> OPEN_SQUAREtok CLOSE_SQUAREtok");
  }
  | OPEN_SQUAREtok constant_expression CLOSE_SQUAREtok {
      reductionOut("direct_abstract_declarator -> OPEN_SQUAREtok constant_expression CLOSE_SQUAREtok");
  }
  | direct_abstract_declarator OPEN_SQUAREtok CLOSE_SQUAREtok {
      reductionOut("direct_abstract_declarator -> direct_abstract_declarator OPEN_SQUAREtok CLOSE_SQUAREtok");
  }
  | direct_abstract_declarator OPEN_SQUAREtok constant_expression CLOSE_SQUAREtok {
      reductionOut("direct_abstract_declarator -> direct_abstract_declarator OPEN_SQUAREtok constant_expression CLOSE_SQUAREtok");
  }
  | OPEN_PARENtok CLOSE_PARENtok {
      reductionOut("direct_abstract_declarator -> OPEN_PARENtok CLOSE_PARENtok");
  }
  | OPEN_PARENtok parameter_type_list CLOSE_PARENtok {
      reductionOut("direct_abstract_declarator -> OPEN_PARENtok parameter_type_list CLOSE_PARENtok");
  }
  | direct_abstract_declarator OPEN_PARENtok CLOSE_PARENtok {
      reductionOut("direct_abstract_declarator -> direct_abstract_declarator OPEN_PARENtok CLOSE_PARENtok");
  }
  | direct_abstract_declarator OPEN_PARENtok parameter_type_list CLOSE_PARENtok {
      reductionOut("direct_abstract_declarator -> direct_abstract_declarator OPEN_PARENtok parameter_type_list CLOSE_PARENtok");
  }
  ;

statement
  : labeled_statement {
      reductionOut("statement -> labeled_statement");
  }
  | compound_statement {
      reductionOut("statement -> compound_statement");
  }
  | expression_statement {
      reductionOut("statement -> expression_statement");
  }
  | selection_statement {
      reductionOut("statement -> selection_statement");
  }
  | iteration_statement {
      reductionOut("statement -> iteration_statement");
  }
  | jump_statement {
      reductionOut("statement -> jump_statement");
  }
  ;

labeled_statement
  : identifier COLONtok statement {
      reductionOut("labeled_statement -> identifier COLONtok statement");
  }
  | CASEtok constant_expression COLONtok statement {
      reductionOut("labeled_statement -> CASEtok constant_expression COLONtok statement");
  }
  | DEFAULTtok COLONtok statement {
      reductionOut("labeled_statement -> DEFAULTtok COLONtok statement");
  }
  ;

expression_statement
  : SEMItok {
      reductionOut("expression_statement -> SEMItok");
  }
  | expression SEMItok {
      reductionOut("expression_statement -> expression SEMItok");
  }
  ;

compound_statement
  : OPEN_CURLYtok enter_scope CLOSE_CURLYtok end_scope{
      reductionOut("compound_statement -> OPEN_CURLYtok CLOSE_CURLYtok");
  }
  | OPEN_CURLYtok enter_scope statement_list CLOSE_CURLYtok end_scope{
      reductionOut("compound_statement -> OPEN_CURLYtok statement_list CLOSE_CURLYtok");
  }
  | OPEN_CURLYtok enter_scope declaration_list CLOSE_CURLYtok end_scope{
      reductionOut("compound_statement -> OPEN_CURLYtok declaration_list CLOSE_CURLYtok");
  }
  | OPEN_CURLYtok enter_scope declaration_list statement_list CLOSE_CURLYtok end_scope{
      reductionOut("compound_statement -> OPEN_CURLYtok declaration_list statement_list CLOSE_CURLYtok");
  }
  ;

statement_list
  : statement {
      reductionOut("statement_list -> statement");
  }
  | statement_list statement {
      reductionOut("statement_list -> statement_list statement");
  }
  ;

selection_statement
  : IFtok OPEN_PARENtok expression CLOSE_PARENtok statement {
      reductionOut("selection_statement -> IFtok OPEN_PARENtok expression CLOSE_PARENtok statement");
  }
  | IFtok OPEN_PARENtok expression CLOSE_PARENtok statement ELSEtok statement {
      reductionOut("selection_statement -> IFtok OPEN_PARENtok expression CLOSE_PARENtok statement ELSEtok statement");
  }
  | SWITCHtok OPEN_PARENtok expression CLOSE_PARENtok statement {
      reductionOut("selection_statement -> SWITCHtok OPEN_PARENtok expression CLOSE_PARENtok statement");
  }
  ;

iteration_statement
  : WHILEtok OPEN_PARENtok expression CLOSE_PARENtok statement {
      reductionOut("iteration_statement -> WHILEtok OPEN_PARENtok expression CLOSE_PARENtok statement");
  }
  | DOtok statement WHILEtok OPEN_PARENtok expression CLOSE_PARENtok SEMItok {
      reductionOut("iteration_statement -> DOtok statement WHILEtok OPEN_PARENtok expression CLOSE_PARENtok SEMItok");
  }
  | FORtok OPEN_PARENtok SEMItok SEMItok CLOSE_PARENtok statement {
      reductionOut("iteration_statement -> FORtok OPEN_PARENtok SEMItok SEMItok CLOSE_PARENtok statement");
  }
  | FORtok OPEN_PARENtok SEMItok SEMItok expression CLOSE_PARENtok statement {
      reductionOut("iteration_statement -> FORtok OPEN_PARENtok SEMItok SEMItok expression CLOSE_PARENtok statement");
  }
  | FORtok OPEN_PARENtok SEMItok expression SEMItok CLOSE_PARENtok statement {
      reductionOut("iteration_statement -> FORtok OPEN_PARENtok SEMItok expression SEMItok CLOSE_PARENtok statement");
  }
  | FORtok OPEN_PARENtok SEMItok expression SEMItok expression CLOSE_PARENtok statement {
      reductionOut("iteration_statement -> FORtok OPEN_PARENtok SEMItok expression SEMItok expression CLOSE_PARENtok statement");
  }
  | FORtok OPEN_PARENtok expression SEMItok SEMItok CLOSE_PARENtok statement {
      reductionOut("iteration_statement -> FORtok OPEN_PARENtok expression SEMItok SEMItok CLOSE_PARENtok statement");
  }
  | FORtok OPEN_PARENtok expression SEMItok SEMItok expression CLOSE_PARENtok statement {
      reductionOut("iteration_statement -> FORtok OPEN_PARENtok expression SEMItok SEMItok expression CLOSE_PARENtok statement");
  }
  | FORtok OPEN_PARENtok expression SEMItok expression SEMItok CLOSE_PARENtok statement {
      reductionOut("iteration_statement -> FORtok OPEN_PARENtok expression SEMItok expression SEMItok CLOSE_PARENtok statement");
  }
  | FORtok OPEN_PARENtok expression SEMItok expression SEMItok expression CLOSE_PARENtok statement {
      reductionOut("iteration_statement -> FORtok OPEN_PARENtok expression SEMItok expression SEMItok expression CLOSE_PARENtok statement");
  }
  ;

jump_statement
  : GOTOtok identifier SEMItok {
      reductionOut("jump_statement -> GOTOtok identifier SEMItok");
  }
  | CONTINUEtok SEMItok {
      reductionOut("jump_statement -> CONTINUEtok SEMItok");
  }
  | BREAKtok SEMItok {
      reductionOut("jump_statement -> BREAKtok SEMItok");
  }
  | RETURNtok SEMItok {
      reductionOut("jump_statement ->  RETURNtok SEMItok");
  }
  | RETURNtok expression SEMItok {
      reductionOut("jump_statement -> RETURNtok expression SEMItok");
  }
  ;

expression
  : assignment_expression {
      reductionOut("expression -> assignment_expression");
  }
  | expression COMMAtok assignment_expression {
      reductionOut("expression -> expression COMMAtok assignment_expression");
  }
  ;

assignment_expression
  : conditional_expression {
      reductionOut("assignment_expression -> conditional_expression");
  }
  | unary_expression assignment_operator assignment_expression {
      reductionOut("assignment_expression -> unary_expression assignment_operator assignment_expression");
  }
  ;

assignment_operator
  : EQUALtok {
      reductionOut("assignment_operator -> EQUALtok");
  }
  | MUL_ASSIGNtok {
      reductionOut("assignment_operator -> MUL_ASSIGNtok");
  }
  | DIV_ASSIGNtok {
      reductionOut("assignment_operator -> DIV_ASSIGNtok");
  }
  | MOD_ASSIGNtok {
      reductionOut("assignment_operator -> MOD_ASSIGNtok");
  }
  | ADD_ASSIGNtok {
      reductionOut("assignment_operator -> ADD_ASSIGNtok");
  }
  | SUB_ASSIGNtok {
      reductionOut("assignment_operator -> SUB_ASSIGNtok");
  }
  | LEFT_ASSIGNtok {
      reductionOut("assignment_operator -> LEFT_ASSIGNtok");
  }
  | RIGHT_ASSIGNtok {
      reductionOut("assignment_operator -> RIGHT_ASSIGNtok");
  }
  | AND_ASSIGNtok {
      reductionOut("assignment_operator -> AND_ASSIGNtok");
  }
  | XOR_ASSIGNtok {
      reductionOut("assignment_operator -> XOR_ASSIGNtok");
  }
  | OR_ASSIGNtok {
      reductionOut("assignment_operator -> OR_ASSIGNtok");
  }
  ;

conditional_expression
  : logical_or_expression {
      reductionOut("conditional_expression -> logical_or_expression");
  }
  | logical_or_expression QUESTION_MARKtok expression COLONtok conditional_expression {
      reductionOut("conditional_expression -> logical_or_expression QUESTION_MARKtok expression COLONtok conditional_expression");
  }
  ;

constant_expression
  : conditional_expression {
      reductionOut("constant_expression -> conditional_expression");
  }
  ;

logical_or_expression
  : logical_and_expression {
      reductionOut("logical_or_expression -> logical_and_expression");
  }
  | logical_or_expression OR_OPtok logical_and_expression {
      reductionOut("logical_or_expression -> logical_or_expression OR_OPtok logical_and_expression");
  }
  ;

logical_and_expression
  : inclusive_or_expression {
      reductionOut("logical_and_expression -> inclusive_or_expression");
  }
  | logical_and_expression AND_OPtok inclusive_or_expression {
      reductionOut("logical_and_expression -> logical_and_expression AND_OPtok inclusive_or_expression");
  }
  ;

inclusive_or_expression
  : exclusive_or_expression {
      reductionOut("inclusive_or_expression -> exclusive_or_expression");
  }
  | inclusive_or_expression PIPEtok exclusive_or_expression {
      reductionOut("inclusive_or_expression -> inclusive_or_expression PIPEtok exclusive_or_expression");
  }
  ;

exclusive_or_expression
  : and_expression {
      reductionOut("exclusive_or_expression -> and_expression");
  }
  | exclusive_or_expression UP_CARROTtok and_expression {
      reductionOut("exclusive_or_expression -> exclusive_or_expression UP_CARROTtok and_expression");
  }
  ;

and_expression
  : equality_expression {
      reductionOut("and_expression -> equality_expression");
  }
  | and_expression UNARY_ANDtok equality_expression {
      reductionOut("and_expression -> and_expression UNARY_ANDtok equality_expression");
  }
  ;

equality_expression
  : relational_expression {
      reductionOut("equality_expression -> relational_expression");
  }
  | equality_expression EQ_OPtok relational_expression {
      reductionOut("equality_expression -> equality_expression EQ_OPtok relational_expression");
  }
  | equality_expression NE_OPtok relational_expression {
      reductionOut("equality_expression -> equality_expression NE_OPtok relational_expression");
  }
  ;

relational_expression
  : shift_expression {
      reductionOut("relational_expression -> shift_expression");
  }
  | relational_expression LEFT_ANGLEtok shift_expression {
      reductionOut("relational_expression -> relational_expression LEFT_ANGLEtok shift_expression");
  }
  | relational_expression RIGHT_ANGLEtok shift_expression {
      reductionOut("relational_expression -> relational_expression RIGHT_ANGLEtok shift_expression");
  }
  | relational_expression LE_OPtok shift_expression {
      reductionOut("relational_expression -> relational_expression LE_OPtok shift_expression");
  }
  | relational_expression GE_OPtok shift_expression {
      reductionOut("relational_expression -> relational_expression GE_OPtok shift_expression");
  }
  ;

shift_expression
  : additive_expression {
      reductionOut("shift_expression -> additive_expression");
  }
  | shift_expression LEFT_OPtok additive_expression {
      reductionOut("shift_expression -> shift_expression LEFT_OPtok additive_expression");
  }
  | shift_expression RIGHT_OPtok additive_expression {
      reductionOut("shift_expression -> shift_expression RIGHT_OPtok additive_expression");
  }
  ;

additive_expression
  : multiplicative_expression {
      reductionOut("additive_expression -> multiplicative_expression");
  }
  | additive_expression UNARY_PLUStok multiplicative_expression {
      reductionOut("additive_expression -> additive_expression UNARY_PLUStok multiplicative_expression");
  }
  | additive_expression UNARY_MINUStok multiplicative_expression {
      reductionOut("additive_expression -> additive_expression UNARY_MINUStok multiplicative_expression");
  }
  ;

multiplicative_expression
  : cast_expression {
      reductionOut("multiplicative_expression -> cast_expression");
  }
  | multiplicative_expression UNARY_ASTERISKtok cast_expression {
      reductionOut("multiplicative_expression -> multiplicative_expression UNARY_ASTERISKtok cast_expression");
  }
  | multiplicative_expression FORWARD_SLASHtok cast_expression {
      reductionOut("multiplicative_expression -> multiplicative_expression FORWARD_SLASHtok cast_expression");
  }
  | multiplicative_expression PERCENTtok cast_expression {
      reductionOut("multiplicative_expression -> multiplicative_expression PERCENTtok cast_expression");
  }
  ;

cast_expression
  : unary_expression {
      reductionOut("cast_expression -> unary_expression");
  }
  | OPEN_PARENtok type_name CLOSE_PARENtok cast_expression {
      reductionOut("cast_expression -> OPEN_PARENtok type_name CLOSE_PARENtok cast_expression");
  }
  ;

unary_expression
  : postfix_expression {
      reductionOut("unary_expression -> postfix_expression");
  }
  | INC_OPtok unary_expression {
      reductionOut("unary_expression -> INC_OPtok unary_expression");
  }
  | DEC_OPtok unary_expression {
      reductionOut("unary_expression -> DEC_OPtok unary_expression");
  }
  | unary_operator cast_expression {
      reductionOut("unary_expression -> unary_operator cast_expression");
  }
  | SIZEOFtok unary_expression {
      reductionOut("unary_expression -> SIZEOFtok unary_expression");
  }
  | SIZEOFtok OPEN_PARENtok type_name CLOSE_PARENtok {
      reductionOut("unary_expression -> SIZEOFtok OPEN_PARENtok type_name CLOSE_PARENtok");
  }
  ;

unary_operator
  : UNARY_ANDtok {
      reductionOut("unary_operator -> UNARY_ANDtok");
  }
  | UNARY_ASTERISKtok {
      reductionOut("unary_operator -> UNARY_ASTERISKtok");
  }
  | UNARY_PLUStok {
      reductionOut("unary_operator -> UNARY_PLUStok");
  }
  | UNARY_MINUStok {
      reductionOut("unary_operator -> UNARY_MINUStok");
  }
  | UNARY_TILDEtok {
      reductionOut("unary_operator -> UNARY_TILDEtok");
  }
  | UNARY_BANGtok {
      reductionOut("unary_operator -> UNARY_BANGtok");
  }
  ;

postfix_expression
  : primary_expression {
      reductionOut("postfix_expression -> primary_expression");
  }
  | postfix_expression OPEN_SQUAREtok expression CLOSE_SQUAREtok {
      reductionOut("postfix_expression -> postfix_expression OPEN_SQUAREtok expression CLOSE_SQUAREtok");
  }
  | postfix_expression OPEN_PARENtok CLOSE_PARENtok {
      reductionOut("postfix_expression -> postfix_expression OPEN_PARENtok CLOSE_PARENtok");
  }
  | postfix_expression OPEN_PARENtok argument_expression_list CLOSE_PARENtok {
      reductionOut("postfix_expression -> postfix_expression OPEN_PARENtok argument_expression_list CLOSE_PARENtok");
  }
  | postfix_expression PERIODtok identifier {
      reductionOut("postfix_expression -> postfix_expression PERIODtok identifier");
  }
  | postfix_expression PTR_OPtok identifier {
      reductionOut("postfix_expression -> postfix_expression PTR_OPtok identifier");
  }
  | postfix_expression INC_OPtok {
      reductionOut("postfix_expression -> postfix_expression INC_OPtok");
  }
  | postfix_expression DEC_OPtok {
      reductionOut("postfix_expression -> postfix_expression DEC_OPtok");
  }
  ;

primary_expression
  : identifier {
      reductionOut("primary_expression -> identifier");
  }
  | constant {
      reductionOut("primary_expression -> constant");
  }
  | string {
      reductionOut("primary_expression -> string");
  }
  | OPEN_PARENtok expression CLOSE_PARENtok {
      reductionOut("primary_expression -> OPEN_PARENtok expression CLOSE_PARENtok");
  }
  ;

argument_expression_list
  : assignment_expression {
      reductionOut("argument_expression_list -> assignment_expression");
  }
  | argument_expression_list COMMAtok assignment_expression {
      reductionOut("argument_expression_list -> argument_expression_list COMMAtok assignment_expression");
  }
  ;

constant
  : INTEGER_CONSTANTtok {
      reductionOut("constant -> INTEGER_CONSTANTtok");
  }
  | CHARACTER_CONSTANTtok {
      reductionOut("constant -> CHARACTER_CONSTANTtok");
  }
  | FLOATING_CONSTANTtok {
      reductionOut("constant -> FLOATING_CONSTANTtok");
  }
  | ENUMERATION_CONSTANTtok {
      reductionOut("constant -> ENUMERATION_CONSTANTtok");
  }
  ;

string
  : STRING_LITERALtok {
      reductionOut("string -> STRING_LITERALtok");
  }
  ;

identifier
  : IDENTIFIERtok {
      reductionOut("identifier -> IDENTIFIERtok");
      strcpy($$, $1);
  }
  ;

%%
/* user code ****************************************************************/
void yyerror (char* s) {
    fflush(stdout);
    printf("%s on line %d - %s\n", s, yylineno, yytext);
}


