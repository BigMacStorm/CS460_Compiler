/* definitions ****************************************************************/
%{
	#include "comp.tab.h"
	#include <string.h>
	//#include "SymbolTable.h"
	unsigned int linenum = 1;
	unsigned int colnum = 1;
	char errormsg [70];
	void addCol(int);
	void addLine(int);
	void zeroCol();
	void checkOverflow(char*);
	void checkIDLength(char*);
	void printToStderr(char*);
	void printLine();
%}

%option noyywrap
%option yylineno

ws   [ \r\t\v\f]
newline \n+
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

char_const '(\\.|[^\\'])+'
string_literal \"(\\.|[^"])*\"

mcomment "/*"(.|"\n")"*/"
scomment "//".*

/* token rules and actions ***************************************************/
%%
"!!S"
{ws}
{scomment}       { addLine(1); }
{mcomment}
{newline}       {   addLine(yyleng);
                    zeroCol();
                }

"sizeof"    {   addCol(yyleng);
                return(SIZEOFtok);
            }

"->"        {   addCol(yyleng);
                return(PTR_OPtok);
            }
"++"        {   addCol(yyleng);
                return(INC_OPtok);
            }
"--"        {   addCol(yyleng);
                return(DEC_OPtok);
            }
"<<"        {   addCol(yyleng);
                return(LEFT_OPtok);
            }
">>"        {   addCol(yyleng);
                return(RIGHT_OPtok);
            }
"<="        {   addCol(yyleng);
                return(LE_OPtok);
            }
">="        {   addCol(yyleng);
                return(GE_OPtok);
            }
"=="        {   addCol(yyleng);
                return(EQ_OPtok);
            }
"!="        {   addCol(yyleng);
                return(NE_OPtok);
            }
"&&"        {   addCol(yyleng);
                return(AND_OPtok);
            }
"||"        {   addCol(yyleng);
                return(OR_OPtok);
            }

"*="        {   addCol(yyleng);
                return(MUL_ASSIGNtok);
            }
"/="        {   addCol(yyleng);
                return(DIV_ASSIGNtok);
            }
"%="        {   addCol(yyleng);
                return(MOD_ASSIGNtok);
            }
"+="        {   addCol(yyleng);
                return(ADD_ASSIGNtok);
            }
"-="        {   addCol(yyleng);
                return(SUB_ASSIGNtok);
            }
"<<="       {   addCol(yyleng);
                return(LEFT_ASSIGNtok);
            }
">>="       {   addCol(yyleng);
                return(RIGHT_ASSIGNtok);
            }
"&="        {   addCol(yyleng);
                return(AND_ASSIGNtok);
            }
"^="        {   addCol(yyleng);
                return(XOR_ASSIGNtok);
            }
"|="        {   addCol(yyleng);
                return(OR_ASSIGNtok);
            }

"("         {   addCol(yyleng);
                return(OPEN_PARENtok);
            }
")"         {   addCol(yyleng);
                return(CLOSE_PARENtok);
            }
("{"|"<%")      {   addCol(yyleng);
                    return(OPEN_CURLYtok);
                }
("}"|"%>")      {   addCol(yyleng);
                    return(CLOSE_CURLYtok);
                }
("["|"<:")      {   addCol(yyleng);
                    return(OPEN_SQUAREtok);
                }
("]"|":>")      {   addCol(yyleng);
                    return(CLOSE_SQUAREtok);
                }

"."     {   addCol(yyleng);
            return(PERIODtok);
        }
","     {   addCol(yyleng);
            return(COMMAtok);
        }
":"     {   addCol(yyleng);
            return(COLONtok);
        }
";"     {   addCol(yyleng);
            return(SEMItok);
        }
"="     {   addCol(yyleng);
            return(EQUALtok);
        }
"&"     {   addCol(yyleng);
            return(UNARY_ANDtok);
        }
"!"     {   addCol(yyleng);
            return(UNARY_BANGtok);
        }
"~"     {   addCol(yyleng);
            return(UNARY_TILDEtok);
        }
"*"     {   addCol(yyleng);
            return(UNARY_ASTERISKtok);
        }
"/"     {   addCol(yyleng);
            return(FORWARD_SLASHtok);
        }
"+"     {   addCol(yyleng);
            return(UNARY_PLUStok);
        }
"-"     {   addCol(yyleng);
            return(UNARY_MINUStok);
        }
"%"     {   addCol(yyleng);
            return(PERCENTtok);
        }
"<"     {   addCol(yyleng);
            return(LEFT_ANGLEtok);
        }
">"     {   addCol(yyleng);
            return(RIGHT_ANGLEtok);
        }
"^"     {   addCol(yyleng);
            return(UP_CARROTtok);
        }
"|"     {   addCol(yyleng);
            return(PIPEtok);
        }
"?"     {   addCol(yyleng);
            return(QUESTION_MARKtok);
        }

"typedef"   {   addCol(yyleng);
                return(TYPEDEFtok);
            }
"extern"    {   addCol(yyleng);
                return(EXTERNtok);
            }
"static"    {   addCol(yyleng);
                return(STATICtok);
            }
"auto"      {   addCol(yyleng);
                return(AUTOtok);
            }
"register"  {   addCol(yyleng);
                return(REGISTERtok);
            }
"char"      {   addCol(yyleng);
                return(CHARtok);
            }
"short"     {   addCol(yyleng);
                return(SHORTtok);
            }
"int"       {   addCol(yyleng);
                return(INTtok);
            }
"long"      {   addCol(yyleng);
                return(LONGtok);
            }
"signed"    {   addCol(yyleng);
                return(SIGNEDtok);
            }
"unsigned"  {   addCol(yyleng);
                return(UNSIGNEDtok);
            }
"float"     {   addCol(yyleng);
                return(FLOATtok);
            }
"double"    {   addCol(yyleng);
                return(DOUBLEtok);
            }
"const"     {   addCol(yyleng);
                return(CONSTtok);
            }
"volatile"  {   addCol(yyleng);
                return(VOLATILEtok);
            }
"void"      {   addCol(yyleng);
                return(VOIDtok);
            }
"struct"    {   addCol(yyleng);
                return(STRUCTtok);
            }
"union"     {   addCol(yyleng);
                return(UNIONtok);
            }
"enum"      {   addCol(yyleng);
                return(ENUMtok);
            }
"..."       {   addCol(yyleng);
                return(ELIPSIStok);
            }
"case"      {   addCol(yyleng);
                return(CASEtok);
            }
"default"   {   addCol(yyleng);
                return(DEFAULTtok);
            }
"if"        {   addCol(yyleng);
                return(IFtok);
            }
"else"      {   addCol(yyleng);
                return(ELSEtok);
            }
"switch"    {   addCol(yyleng);
                return(SWITCHtok);
            }
"while"     {   addCol(yyleng);
                return(WHILEtok);
            }
"do"        {   addCol(yyleng);
                return(DOtok);
            }
"for"       {   addCol(yyleng);
                return(FORtok);
            }
"goto"      {   addCol(yyleng);
                return(GOTOtok);
            }
"continue"  {   addCol(yyleng);
                return(CONTINUEtok);
            }
"break"     {   addCol(yyleng);
                return(BREAKtok);
                
            }
"return"    {   addCol(yyleng);
                return(RETURNtok);
            }

{id}        {   //std::string name = yytext;
                //StokymbolNtokode * symNtokode = new StokymbolNtokode(name, NULLtok, yylineno);
                //symTtokable.insertStokymbol(name, symNtokode);
                addCol(yyleng);
                checkIDLength(yytext);
                return(IDENTIFIERtok);
            }

{int_const}     {   
                    addCol(yyleng);
                    checkOverflow(yytext);
                    return(INTEGER_CONSTANTtok);
                }
{real_const}    {   
                    addCol(yyleng);
                    return(FLOATING_CONSTANTtok);
                }
{char_const}    {   
                    addCol(yyleng);
                    return(CHARACTER_CONSTANTtok);
                }
{string_literal}    {   addCol(yyleng);
                        return(STRING_LITERALtok);
                    }

.         { //return(ERRORtok);
            addCol(yyleng);
            sprintf(errormsg, "ERROR: illegal character: line %d, col %d", linenum, colnum);
            yyerror(errormsg);
	      }

%%
/* user code **************************************************************/

/*  Atok minimal Ltokex scanner generator
    Ptokasses tokens which are undefined yet to yacc
	col and line numbers are recorded but not used in an error function yet

*/
void checkOverflow (char * intInput)
{
    char warning[100];
	if (strcmp(intInput, "2147483647") == 1)
    {
        sprintf(warning, "WARNING: Integer overflow, line %d col %d", linenum, colnum);
        printToStderr(warning);
    }
}

void checkIDLength(char* charInput)
{
    char warning[100];
    int len = strlen(charInput);
    if (len >= 10)
    {
        sprintf(warning, "WARNING: Very long ID %s, line %d, col %d", charInput, linenum, colnum);
        printToStderr(warning);
    }
}

void addCol(int matchedCol)
{
	colnum = colnum + matchedCol;
}

void addLine(int matchedLine)
{
	linenum = linenum + matchedLine;
}

void zeroCol()
{
	colnum = colnum = 1;
}

void printToStderr(char* errormsg)
{
    fprintf(stderr, "%s\n", errormsg);
}
void printErrorLine()
{
	//open current file(?)
	//print entire line
	//print ^ colnum spaces over on next line
}
