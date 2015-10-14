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

%start translation_unit



%{
#include <stdio.h>
typedef int YYSTYPE;
%}

%%

translation_unit
	: external_declaration
	| translation_unit external_declaration
	;

external_declaration
	: function_definition
	| declaration
	;

function_definition
	: declarator compound_statement
	| declarator declaration_list compound_statement
	| declaration_specifiers declarator compound_statement
	| declaration_specifiers declarator declaration_list compound_statement
	;

declaration
	: declaration_specifiers SEMItok
	| declaration_specifiers init_declarator_list SEMItok
	;

declaration_list
	: declaration
	| declaration_list declaration
	;

declaration_specifiers
	: storage_class_specifier
	| storage_class_specifier declaration_specifiers
	| type_specifier
	| type_specifier declaration_specifiers
	| type_qualifier
	| type_qualifier declaration_specifiers
	;

storage_class_specifier
	: AUTOtok
	| REGISTERtok
	| STATICtok
	| EXTERNtok
	| TYPEDEFtok
	;

type_specifier
	: VOIDtok
	| CHARtok
	| SHORTtok
	| INTtok
	| LONGtok
	| FLOATtok
	| DOUBLEtok
	| SIGNEDtok
	| UNSIGNEDtok
	| struct_or_union_specifier
	| enum_specifier
	| TYPEDEF_NAMEtok
	;

type_qualifier
	: CONSTtok
	| VOLATILEtok
	;

struct_or_union_specifier
	: struct_or_union identifier OPEN_CURLYtok struct_declaration_list CLOSE_CURLYtok
	| struct_or_union OPEN_CURLYtok struct_declaration_list CLOSE_CURLYtok
	| struct_or_union identifier
	;

struct_or_union
	: STRUCTtok
	| UNIONtok
	;

struct_declaration_list
	: struct_declaration
	| struct_declaration_list struct_declaration
	;

init_declarator_list
	: init_declarator
	| init_declarator_list COMMAtok init_declarator
	;

init_declarator
	: declarator
	| declarator EQUALtok initializer
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list SEMItok
	;

specifier_qualifier_list
	: type_specifier
	| type_specifier specifier_qualifier_list
	| type_qualifier
	| type_qualifier specifier_qualifier_list
	;

struct_declarator_list
	: struct_declarator
	| struct_declarator_list COMMAtok struct_declarator
	;

struct_declarator
	: declarator
	| COLONtok constant_expression
	| declarator COLONtok constant_expression
	;

enum_specifier
	: ENUMtok OPEN_CURLYtok enumerator_list CLOSE_CURLYtok
	| ENUMtok identifier OPEN_CURLYtok enumerator_list CLOSE_CURLYtok
	| ENUMtok identifier
	;

enumerator_list
	: enumerator
	| enumerator_list COMMAtok enumerator
	;

enumerator
	: identifier
	| identifier EQUALtok constant_expression
	;

declarator
	: direct_declarator
	| pointer direct_declarator
	;

direct_declarator
	: identifier
	| OPEN_PARENtok declarator CLOSE_PARENtok
	| direct_declarator OPEN_SQUAREtok CLOSE_SQUAREtok
	| direct_declarator OPEN_SQUAREtok constant_expression CLOSE_SQUAREtok
	| direct_declarator OPEN_PARENtok CLOSE_PARENtok
	| direct_declarator OPEN_PARENtok parameter_type_list CLOSE_PARENtok
	| direct_declarator OPEN_PARENtok identifier_list CLOSE_PARENtok
	;

pointer
	: UNARY_ASTERISKtok
	| UNARY_ASTERISKtok type_qualifier_list
	| UNARY_ASTERISKtok pointer
	| UNARY_ASTERISKtok type_qualifier_list pointer
	;

type_qualifier_list
	: type_qualifier
	| type_qualifier_list type_qualifier
	;

parameter_type_list
	: parameter_list
	| parameter_list COMMAtok ELIPSIStok
	;

parameter_list
	: parameter_declaration
	| parameter_list COMMAtok parameter_declaration
	;

parameter_declaration
	: declaration_specifiers declarator
	| declaration_specifiers
	| declaration_specifiers abstract_declarator
	;

identifier_list
	: identifier
	| identifier_list COMMAtok identifier
	;

initializer
	: assignment_expression
	| OPEN_CURLYtok initializer_list CLOSE_CURLYtok
	| OPEN_CURLYtok initializer_list COMMAtok CLOSE_CURLYtok
	;

initializer_list
	: initializer
	| initializer_list COMMAtok initializer
	;

type_name
	: specifier_qualifier_list
	| specifier_qualifier_list abstract_declarator
	;

abstract_declarator
	: pointer
	| direct_abstract_declarator
	| pointer direct_abstract_declarator
	;

direct_abstract_declarator
	: OPEN_PARENtok abstract_declarator CLOSE_PARENtok
	| OPEN_SQUAREtok CLOSE_SQUAREtok
	| OPEN_SQUAREtok constant_expression CLOSE_SQUAREtok
	| direct_abstract_declarator OPEN_SQUAREtok CLOSE_SQUAREtok
	| direct_abstract_declarator OPEN_SQUAREtok constant_expression CLOSE_SQUAREtok
	| OPEN_PARENtok CLOSE_PARENtok
	| OPEN_PARENtok parameter_type_list CLOSE_PARENtok
	| direct_abstract_declarator OPEN_PARENtok CLOSE_PARENtok
	| direct_abstract_declarator OPEN_PARENtok parameter_type_list CLOSE_PARENtok
	;

statement
	: labeled_statement
	| compound_statement
	| expression_statement
	| selection_statement
	| iteration_statement
	| jump_statement
	;

labeled_statement
	: identifier COLONtok statement
	| CASEtok constant_expression COLONtok statement
	| DEFAULTtok COLONtok statement
	;

expression_statement
	: SEMItok
	| expression SEMItok
	;

compound_statement
	: OPEN_CURLYtok CLOSE_CURLYtok
	| OPEN_CURLYtok statement_list CLOSE_CURLYtok
	| OPEN_CURLYtok declaration_list CLOSE_CURLYtok
	| OPEN_CURLYtok declaration_list statement_list CLOSE_CURLYtok
	;

statement_list
	: statement
	| statement_list statement
	;

selection_statement
	: IFtok OPEN_PARENtok expression CLOSE_PARENtok statement
	| IFtok OPEN_PARENtok expression CLOSE_PARENtok statement ELSEtok statement
	| SWITCHtok OPEN_PARENtok expression CLOSE_PARENtok statement
	;

iteration_statement
	: WHILEtok OPEN_PARENtok expression CLOSE_PARENtok statement
	| DOtok statement WHILEtok OPEN_PARENtok expression CLOSE_PARENtok SEMItok
	| FORtok OPEN_PARENtok SEMItok SEMItok CLOSE_PARENtok statement
	| FORtok OPEN_PARENtok SEMItok SEMItok expression CLOSE_PARENtok statement
	| FORtok OPEN_PARENtok SEMItok expression SEMItok CLOSE_PARENtok statement
	| FORtok OPEN_PARENtok SEMItok expression SEMItok expression CLOSE_PARENtok statement
	| FORtok OPEN_PARENtok expression SEMItok SEMItok CLOSE_PARENtok statement
	| FORtok OPEN_PARENtok expression SEMItok SEMItok expression CLOSE_PARENtok statement
	| FORtok OPEN_PARENtok expression SEMItok expression SEMItok CLOSE_PARENtok statement
	| FORtok OPEN_PARENtok expression SEMItok expression SEMItok expression CLOSE_PARENtok statement
	;

jump_statement
	: GOTOtok identifier SEMItok
	| CONTINUEtok SEMItok
	| BREAKtok SEMItok
	| RETURNtok SEMItok
	| RETURNtok expression SEMItok
	;

expression
	: assignment_expression
	| expression COMMAtok assignment_expression
	;

assignment_expression
	: conditional_expression
	| unary_expression assignment_operator assignment_expression
	;

assignment_operator
	: EQUALtok
	| MUL_ASSIGNtok
	| DIV_ASSIGNtok
	| MOD_ASSIGNtok
	| ADD_ASSIGNtok
	| SUB_ASSIGNtok
	| LEFT_ASSIGNtok
	| RIGHT_ASSIGNtok
	| AND_ASSIGNtok
	| XOR_ASSIGNtok
	| OR_ASSIGNtok
	;

conditional_expression
	: logical_or_expression
	| logical_or_expression QUESTION_MARKtok expression COLONtok conditional_expression
	;

constant_expression
	: conditional_expression
	;

logical_or_expression
	: logical_and_expression
	| logical_or_expression OR_OPtok logical_and_expression
	;

logical_and_expression
	: inclusive_or_expression
	| logical_and_expression AND_OPtok inclusive_or_expression
	;

inclusive_or_expression
	: exclusive_or_expression
	| inclusive_or_expression PIPEtok exclusive_or_expression
	;

exclusive_or_expression
	: and_expression
	| exclusive_or_expression UP_CARROTtok and_expression
	;

and_expression
	: equality_expression
	| and_expression UNARY_ANDtok equality_expression
	;

equality_expression
	: relational_expression
	| equality_expression EQ_OPtok relational_expression
	| equality_expression NE_OPtok relational_expression
	;

relational_expression
	: shift_expression
	| relational_expression LEFT_ANGLEtok shift_expression
	| relational_expression RIGHT_ANGLEtok shift_expression
	| relational_expression LE_OPtok shift_expression
	| relational_expression GE_OPtok shift_expression
	;

shift_expression
	: additive_expression
	| shift_expression LEFT_OPtok additive_expression
	| shift_expression RIGHT_OPtok additive_expression
	;

additive_expression
	: multiplicative_expression
	| additive_expression UNARY_PLUStok multiplicative_expression
	| additive_expression UNARY_MINUStok multiplicative_expression
	;

multiplicative_expression
	: cast_expression
	| multiplicative_expression UNARY_ASTERISKtok cast_expression
	| multiplicative_expression FORWARD_SLASHtok cast_expression
	| multiplicative_expression PERCENTtok cast_expression
	;

cast_expression
	: unary_expression
	| OPEN_PARENtok type_name CLOSE_PARENtok cast_expression
	;

unary_expression
	: postfix_expression
	| INC_OPtok unary_expression
	| DEC_OPtok unary_expression
	| unary_operator cast_expression
	| SIZEOFtok unary_expression
	| SIZEOFtok OPEN_PARENtok type_name CLOSE_PARENtok
	;

unary_operator
	: UNARY_ANDtok
	| UNARY_ASTERISKtok
	| UNARY_PLUStok
	| UNARY_MINUStok
	| UNARY_TILDEtok
	| UNARY_BANGtok
	;

postfix_expression
	: primary_expression
	| postfix_expression OPEN_SQUAREtok expression CLOSE_SQUAREtok
	| postfix_expression OPEN_PARENtok CLOSE_PARENtok
	| postfix_expression OPEN_PARENtok argument_expression_list CLOSE_PARENtok
	| postfix_expression PERIODtok identifier
	| postfix_expression PTR_OPtok identifier
	| postfix_expression INC_OPtok
	| postfix_expression DEC_OPtok
	;

primary_expression
	: identifier
	| constant
	| string
	| OPEN_PARENtok expression CLOSE_PARENtok
	;

argument_expression_list
	: assignment_expression
	| argument_expression_list COMMAtok assignment_expression
	;

constant
	: INTEGER_CONSTANTtok
	| CHARACTER_CONSTANTtok
	| FLOATING_CONSTANTtok
	| ENUMERATION_CONSTANTtok
	;

string
	: STRING_LITERALtok
	;

identifier
	: IDENTIFIERtok
	;
%%

int main() {
    yyparse();
    return 0;
}

// This causes a warning right now
// Not sure how to suppress it yet
void yyerror(const char* msg) {
    printf("%s\n", msg);
}
