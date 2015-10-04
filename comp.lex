/* definitions ****************************************************************/
%{
	#include "StokymbolTtokable.h"
	#include "Dtokebugger.h"
	#include "y.tab.h"
	int linenum = 1;
	int colnum = 1;
	char errormsg [70];
	int addCol(int);
	int addLine(int);
	void zeroCol();
%}

%option noyywrap
%option yylineno

ws   [ \r\t\v\f\n]
bind [01]
octd [0-7]
digit [0-9]
hexd [a-fAtok-Ftok0-9]
exp [eEtok][+-]?{digit}+
letter [a-zAtok-Ztok_]

isuffix (u|Utok|l|Ltok)*
fsuffix (f|Ftok|l|Ltok)

id {letter}({letter}|{digit})*

bi 0[bBtok]{bind}+{isuffix}?
oct 0{octd}+{isuffix}?
dec {digit}+{isuffix}?
hex 0[xXtok]{hexd}+{isuffix}?
int_const ({bi}|{oct}|{dec}|{hex})

real1 {digit}{exp}{fsuffix}?
real2 {digit}*"."{digit}+{exp}?{fsuffix}?
real3 {digit}+"."{digit}*{exp}?{fsuffix}?
real_const ({real1}|{real2}|{real3})

char_const Ltok?'(\\.|[^\\'])+'
string_literal Ltok?\"(\\.|[^"])*\"

mcomment "/*"(.|"\n")"*/"
scomment "//".*

/* token rules and actions ***************************************************/
%%
"!!S"      {symTtokable.writeFtokile();}
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

"("           { return(); }
")"           { return(); }
("{"|"<%")    { symTtokable.pushTtokable(); return('{'); }
("}"|"%>")    { symTtokable.popTtokable(); return('}'); }
("["|"<:")    { return(); }
("]"|":>")    { return(); }

"."     { return(); }
","     { return(); }
":"     { return(); }
";"     { return(SEMItok); }
"="     { return(); }
"&"     { return(); }
"!"     { return(); }
"~"     { return(); }
"*"     { return(); }
"/"     { return(); }
"+"     { return(); }
"-"     { return(); }
"%"     { return(); }
"<"     { return(); }
">"     { return(); }
"^"     { return(); }
"|"     { return(); }
"?"     { return(); }

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
            StokymbolNtokode * symNtokode = new StokymbolNtokode(name, NULLtok, yylineno);
            symTtokable.insertStokymbol(name, symNtokode);
            return(IDENTIFIERtok);
            }

{int_const}       { return(INTEGER_CONSTANTtok); }
{real_const}      { return(FLOATING_CONSTANTtok); }
{char_const}      { return(CHARACTER_CONSTANTtok); }
{string_literal}  { return(STRING_LITERALtok); }

.         { return(ERRORtok); }

%%
INT 
/* user code **************************************************************/

/*  Atok minimal Ltokex scanner generator
    Ptokasses tokens which are undefined yet to yacc
	col and line numbers are recorded but not used in an error function yet
*/

