/* definitions ****************************************************************/
%{
extern "C"{
  int yyparse();
  int yylex();
}
#include "SymbolTable.h"
#include "Debugger.h"
#include "y.tab.h"
extern SymbolTable symTable;
extern Debugger lexDebugger;
%}

%option noyywrap
%option yylineno

ws   [ \r\t\v\f\n]
bind [01]
octd [0-7]
digit [0-9]
hexd [a-fA-F0-9]
exp [eE][+-]?{digit}+
letter [a-zA-Z_]

isuffix (u|U|l|L)*
fsuffix (f|F|l|L)

id {letter}({letter}|{digit})*

bi 0[bB]{bind}+{isuffix}?
oct 0{octd}+{isuffix}?
dec {digit}+{isuffix}?
hex 0[xX]{hexd}+{isuffix}?
int_const ({bi}|{oct}|{dec}|{hex})

real1 {digit}{exp}{fsuffix}?
real2 {digit}*"."{digit}+{exp}?{fsuffix}?
real3 {digit}+"."{digit}*{exp}?{fsuffix}?
real_const ({real1}|{real2}|{real3})

char_const L?'(\\.|[^\\'])+'
string_literal L?\"(\\.|[^\\"])*\"

mcomment "/*"(.|"\n")"*/"
scomment "//".*

/* token rules and actions ***************************************************/
%%
"!!S"      {symTable.writeFile();}
{ws}       {}
{scomment} {}
{mcomment} {}

"sizeof"  { return(SIZEOFtok); }

"->"      { return(PTR_OPtok); }
"++"      { return(INC_OPtok); }
"--"      { return(DEC_OPtok); }
"<<"      { return(LEFT_OPtok); }
">>"      { return(RIGHT_OPtok); }
"<="      { return(LE_OPtok); }
">="      { return(GE_OPtok); }
"=="      { return(EQ_OPtok); }
"!="      { return(NE_OPtok); }
"&&"      { return(AND_OPtok); }
"||"      { return(OR_OPtok); }

"*="      { return(MUL_ASSIGNtok); }
"/="      { return(DIV_ASSIGNtok); }
"%="      { return(MOD_ASSIGNtok); }
"+="      { return(ADD_ASSIGNtok); }
"-="      { return(SUB_ASSIGNtok); }
"<<="     { return(LEFT_ASSIGNtok); }
">>="     { return(RIGHT_ASSIGNtok); }
"&="      { return(AND_ASSIGNtok); }
"^="      { return(XOR_ASSIGNtok); }
"|="      { return(OR_ASSIGNtok); }

"("           { return(OPEN_PARENtok); }
")"           { return(CLOSE_PARENtok); }
("{"|"<%")    { return(OPEN_CURLYtok); }
("}"|"%>")    { return(CLOSE_CURLYtok); }
("["|"<:")    { return(OPEN_SQUAREtok); }
("]"|":>")    { return(CLOSE_SQUAREtok); }

"."     { return(PERIODtok); }
","     { return(COMMAtok); }
":"     { return(COLONtok); }
";"     { return(SEMItok); }
"="     { return(EQUALtok); }
"&"     { return(UNARY_ANDtok); }
"!"     { return(UNARY_BANGtok); }
"~"     { return(UNARY_TILDEtok); }
"*"     { return(UNARY_ASTERISKtok); }
"/"     { return(FORWARD_SLASHtok); }
"+"     { return(UNARY_PLUStok); }
"-"     { return(UNARY_MINUStok); }
"%"     { return(PERCENTtok); }
"<"     { return(LEFT_ANGLEtok); }
">"     { return(RIGHT_ANGLEtok); }
"^"     { return(UP_CARROTtok); }
"|"     { return(PIPEtok); }
"?"     { return(QUESTION_MARKtok); }

"typedef"   { return(TYPEDEFtok); }
"extern"    { return(EXTERNtok); }
"static"    { return(STATICtok); }
"auto"      { return(AUTOtok); }
"register"  { return(REGISTERtok); }
"char"      { return(CHARtok); }
"short"     { return(SHORTtok); }
"int"       { return(INTtok); }
"long"      { return(LONGtok); }
"signed"    { return(SIGNEDtok); }
"unsigned"  { return(UNSIGNEDtok); }
"float"     { return(FLOATtok); }
"double"    { return(DOUBLEtok); }
"const"     { return(CONSTtok); }
"volatile"  { return(VOLATILEtok); }
"void"      { return(VOIDtok); }
"struct"    { return(STRUCTtok); }
"union"     { return(UNIONtok); }
"enum"      { return(ENUMtok); }
"..."       { return(ELIPSIStok); }
"case"      { return(CASEtok); }
"default"   { return(DEFAULTtok); }
"if"        { return(IFtok); }
"else"      { return(ELSEtok); }
"switch"    { return(SWITCHtok); }
"while"     { return(WHILEtok); }
"do"        { return(DOtok); }
"for"       { return(FORtok); }
"goto"      { return(GOTOtok); }
"continue"  { return(CONTINUEtok); }
"break"     { return(BREAKtok); }
"return"    { return(RETURNtok); }

{id}      {
            std::string name = yytext;
            SymbolNode * symNode = new SymbolNode(name, NULL, yylineno);
            symTable.insertSymbol(name, symNode);
            return(IDENTIFIERtok);
            }

{int_const}       { return(INTEGER_CONSTANTtok); }
{real_const}      { return(FLOATING_CONSTANTtok); }
{char_const}      { return(CHARACTER_CONSTANTtok); }
{string_literal}  { return(STRING_LITERALtok); }

.                 { return(ERRORtok); }

%%
/* user code **************************************************************/
