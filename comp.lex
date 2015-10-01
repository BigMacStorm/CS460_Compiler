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
string_literal L?\"(\\.|[^"])*\"

mcomment "/*"(.|"\n")"*/"
scomment "//".*

/* token rules and actions ***************************************************/
%%
"!!S"      {symTable.writeFile();}
{ws}       {}
{scomment} {}
{mcomment} {}

"sizeof"  { return(SIZEOF); }

"->"      { return(PTR_OP); }
"++"      { return(INC_OP); }
"--"      { return(DEC_OP); }
"<<"      { return(LEFT_OP); }
">>"      { return(RIGHT_OP); }
"<="      { return(LE_OP); }
">="      { return(GE_OP); }
"=="      { return(EQ_OP); }
"!="      { return(NE_OP); }
"&&"      { return(AND_OP); }
"||"      { return(OR_OP); }

"*="      { return(MUL_ASSIGN); }
"/="      { return(DIV_ASSIGN); }
"%="      { return(MOD_ASSIGN); }
"+="      { return(ADD_ASSIGN); }
"-="      { return(SUB_ASSIGN); }
"<<="     { return(LEFT_ASSIGN); }
">>="     { return(RIGHT_ASSIGN); }
"&="      { return(AND_ASSIGN); }
"^="      { return(XOR_ASSIGN); }
"|="      { return(OR_ASSIGN); }

"("           { return('('); }
")"           { return(')'); }
("{"|"<%")    { symTable.pushTable(); return('{'); }
("}"|"%>")    { symTable.popTable(); return('}'); }
("["|"<:")    { return('['); }
("]"|":>")    { return(']'); }

"."     { return('.'); }
","     { return(','); }
":"     { return(':'); }
";"     { return(';'); }
"="     { return('='); }
"&"     { return('&'); }
"!"     { return('!'); }
"~"     { return('~'); }
"*"     { return('*'); }
"/"     { return('/'); }
"+"     { return('+'); }
"-"     { return('-'); }
"%"     { return('%'); }
"<"     { return('<'); }
">"     { return('>'); }
"^"     { return('^'); }
"|"     { return('|'); }
"?"     { return('?'); }

"typedef"   { return(TYPEDEF); }
"extern"    { return(EXTERN); }
"static"    { return(STATIC); }
"auto"      { return(AUTO); }
"register"  { return(REGISTER); }
"char"      { return(CHAR); }
"short"     { return(SHORT); }
"int"       { return(INT); }
"long"      { return(LONG); }
"signed"    { return(SIGNED); }
"unsigned"  { return(UNSIGNED); }
"float"     { return(FLOAT); }
"double"    { return(DOUBLE); }
"const"     { return(CONST); }
"volatile"  { return(VOLATILE); }
"void"      { return(VOID); }
"struct"    { return(STRUCT); }
"union"     { return(UNION); }
"enum"      { return(ENUM); }
"..."       { return(ELIPSIS); }
"case"      { return(CASE); }
"default"   { return(DEFAULT); }
"if"        { return(IF); }
"else"      { return(ELSE); }
"switch"    { return(SWITCH); }
"while"     { return(WHILE); }
"do"        { return(DO); }
"for"       { return(FOR); }
"goto"      { return(GOTO); }
"continue"  { return(CONTINUE); }
"break"     { return(BREAK); }
"return"    { return(RETURN); }

{id}      {
            std::string name = yytext;
            SymbolNode * symNode = new SymbolNode(name, NULL, yylineno);
            symTable.insertSymbol(name, symNode);
            return(IDENTIFIER);
            }

{int_const}       { return(INTEGER_CONSTANT); }
{real_const}      { return(FLOATING_CONSTANT); }
{char_const}      { return(CHARACTER_CONSTANT); }
{string_literal}  { return(STRING_LITERAL); }

.         { return(ERROR); }

%%
/* user code **************************************************************/
