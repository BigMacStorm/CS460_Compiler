/* definitions ****************************************************************/
%{
extern "C"{
  int yyparse();
  int yylex();
}
#include "SymbolTable.h"
#include "Debugger.h"
#include "y.tab.h"
#include <string.h>

extern SymbolTable symTable;
extern void yyerror(char* s);
extern Debugger lexDebugger;
extern Debugger lexSymbolDebugger;
unsigned int linenum = 1;
unsigned int colnum = 1;

char errormsg [70];
void addCol(int);
void addLine(int);
void zeroCol();
bool checkOverflow(unsigned long long);
void checkIDLength(char*);
void printToStderr(char*);
void printLine();
void dumpNextSymbol();

unsigned long long btoi(char*);
unsigned long long otoi(char* text);
unsigned long long htoi(char* text);
int myatoi(char*);
%}

%option noyywrap
%option yylineno

ws   [ \r\t\v\f]
newlines \n+

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
{scomment}"!!S"        {symTable.writeFile();}
{newlines}   {
               addLine(yyleng);
               zeroCol();
             }
{ws}         {addCol(yyleng);}
{scomment}   {}
{mcomment}   {}

"sizeof"     {
               dumpNextSymbol();
               addCol(yyleng);
               return(SIZEOFtok);
             }
"->"         {
               dumpNextSymbol();
               addCol(yyleng);
               return(PTR_OPtok);
             }
"++"         {
               dumpNextSymbol();
               addCol(yyleng);
               return(INC_OPtok);
             }
"--"         {
               dumpNextSymbol();
               addCol(yyleng);
               return(DEC_OPtok);
             }
"<<"         {
               dumpNextSymbol();
               addCol(yyleng);
               return(LEFT_OPtok);
             }
">>"         {
               dumpNextSymbol();
               addCol(yyleng);
               return(RIGHT_OPtok);
             }
"<="         {
               dumpNextSymbol();
               addCol(yyleng);
               return(LE_OPtok);
             }
">="         {
               dumpNextSymbol();
               addCol(yyleng);
               return(GE_OPtok);
             }
"=="         {
               dumpNextSymbol();
               addCol(yyleng);
               return(EQ_OPtok);
             }
"!="         {
               dumpNextSymbol();
               addCol(yyleng);
               return(NE_OPtok);
             }
"&&"         {
               dumpNextSymbol();
               addCol(yyleng);
               return(AND_OPtok);
             }
"||"         {
               dumpNextSymbol();
               addCol(yyleng);
               return(OR_OPtok);
             }

"*="         {
               dumpNextSymbol();
               addCol(yyleng);
               return(MUL_ASSIGNtok);
             }
"/="         {
               dumpNextSymbol();
               addCol(yyleng);
               return(DIV_ASSIGNtok);
             }
"%="         {
               dumpNextSymbol();
               addCol(yyleng);
               return(MOD_ASSIGNtok);
             }
"+="         {
               dumpNextSymbol();
               addCol(yyleng);
               return(ADD_ASSIGNtok);
             }
"-="         {
               dumpNextSymbol();
               addCol(yyleng);
               return(SUB_ASSIGNtok);
             }
"<<="        {
               dumpNextSymbol();
               addCol(yyleng);
               return(LEFT_ASSIGNtok);
             }
">>="        {
               dumpNextSymbol();
               addCol(yyleng);
               return(RIGHT_ASSIGNtok);
             }
"&="         {
               dumpNextSymbol();
               addCol(yyleng);
               return(AND_ASSIGNtok);
             }
"^="         {
               dumpNextSymbol();
               addCol(yyleng);
               return(XOR_ASSIGNtok);
             }
"|="         {
               dumpNextSymbol();
               addCol(yyleng);
               return(OR_ASSIGNtok);
             }
"("          {
               dumpNextSymbol();
               addCol(yyleng);
               return(OPEN_PARENtok);
             }
")"          {
               dumpNextSymbol();
               addCol(yyleng);
               return(CLOSE_PARENtok);
             }
("{"|"<%")   {
               dumpNextSymbol();
               addCol(yyleng);
               return(OPEN_CURLYtok);
             }
("}"|"%>")   {
               dumpNextSymbol();
               addCol(yyleng);
               return(CLOSE_CURLYtok);
             }
("["|"<:")   {
               dumpNextSymbol();
               addCol(yyleng);
               return(OPEN_SQUAREtok);
             }
("]"|":>")   {
               dumpNextSymbol();
               addCol(yyleng);
               return(CLOSE_SQUAREtok);
             }

"."          {
               dumpNextSymbol();
               addCol(yyleng);
               return(PERIODtok);
             }
","          {
               dumpNextSymbol();
               addCol(yyleng);
               return(COMMAtok);
             }
":"          {
               dumpNextSymbol();
               addCol(yyleng);
               return(COLONtok);
             }
";"          {
               dumpNextSymbol();
               addCol(yyleng);
               return(SEMItok);
             }
"="          {
               dumpNextSymbol();
               addCol(yyleng);
               return(EQUALtok);
             }
"&"          {
               dumpNextSymbol();
               addCol(yyleng);
               return(UNARY_ANDtok);
             }
"!"          {
               dumpNextSymbol();
               addCol(yyleng);
               return(UNARY_BANGtok);
             }
"~"          {
               dumpNextSymbol();
               addCol(yyleng);
               return(UNARY_TILDEtok);
             }
"*"          {
               dumpNextSymbol();
               addCol(yyleng);
               return(UNARY_ASTERISKtok);
             }
"/"          {
               dumpNextSymbol();
               addCol(yyleng);
               return(FORWARD_SLASHtok);
             }
"+"          {
               dumpNextSymbol();
               addCol(yyleng);
               return(UNARY_PLUStok);
             }
"-"          {
               dumpNextSymbol();
               addCol(yyleng);
               return(UNARY_MINUStok);
             }
"%"          {
               dumpNextSymbol();
               addCol(yyleng);
               return(PERCENTtok);
             }
"<"          {
               dumpNextSymbol();
               addCol(yyleng);
               return(LEFT_ANGLEtok);
             }
">"          {
               dumpNextSymbol();
               addCol(yyleng);
               return(RIGHT_ANGLEtok);
             }
"^"          {
               dumpNextSymbol();
               addCol(yyleng);
               return(UP_CARROTtok);
             }
"|"          {
               dumpNextSymbol();
               addCol(yyleng);
               return(PIPEtok);
             }
"?"          {
               dumpNextSymbol();
               addCol(yyleng);
               return(QUESTION_MARKtok);
             }

"typedef"    {
               dumpNextSymbol();
               addCol(yyleng);
               return(TYPEDEFtok);
             }
"extern"     {
               dumpNextSymbol();
               addCol(yyleng);
               return(EXTERNtok);
             }
"static"     {
               dumpNextSymbol();
               addCol(yyleng);
               return(STATICtok);
             }
"auto"       {
               dumpNextSymbol();
               addCol(yyleng);
               return(AUTOtok);
             }
"register"   {
               dumpNextSymbol();
               addCol(yyleng);
               return(REGISTERtok);
             }
"char"       {
               dumpNextSymbol();
               addCol(yyleng);
               return(CHARtok);
             }
"short"      {
               dumpNextSymbol();
               addCol(yyleng);
               return(SHORTtok);
             }
"int"        {
               dumpNextSymbol();
               addCol(yyleng);
               return(INTtok);
             }
"long"       {
               dumpNextSymbol();
               addCol(yyleng);
               return(LONGtok);
             }
"signed"     {
               dumpNextSymbol();
               addCol(yyleng);
               return(SIGNEDtok);
             }
"unsigned"   {
               dumpNextSymbol();
               addCol(yyleng);
               return(UNSIGNEDtok);
             }
"float"      {
               dumpNextSymbol();
               addCol(yyleng);
               return(FLOATtok);
             }
"double"     {
               dumpNextSymbol();
               addCol(yyleng);
               return(DOUBLEtok);
             }
"const"      {
               dumpNextSymbol();
               addCol(yyleng);
               return(CONSTtok);
             }
"volatile"   {
               dumpNextSymbol();
               addCol(yyleng);
               return(VOLATILEtok);
             }
"void"       {
               dumpNextSymbol();
               addCol(yyleng);
               return(VOIDtok);
             }
"struct"     {
               dumpNextSymbol();
               addCol(yyleng);
               return(STRUCTtok);
             }
"union"      {
               dumpNextSymbol();
               addCol(yyleng);
               return(UNIONtok);
             }
"enum"       {
               dumpNextSymbol();
               addCol(yyleng);
               return(ENUMtok);
             }
"..."        {
               dumpNextSymbol();
               addCol(yyleng);
               return(ELIPSIStok);
             }
"case"       {
               dumpNextSymbol();
               addCol(yyleng);
               return(CASEtok);
             }
"default"    {
               dumpNextSymbol();
               addCol(yyleng);
               return(DEFAULTtok);
             }
"if"         {
               dumpNextSymbol();
               addCol(yyleng);
               return(IFtok);
             }
"else"       {
               dumpNextSymbol();
               addCol(yyleng);
               return(ELSEtok);
             }
"switch"     {
               dumpNextSymbol();
               addCol(yyleng);
               return(SWITCHtok);
             }
"while"      {
               dumpNextSymbol();
               addCol(yyleng);
               return(WHILEtok);
             }
"do"         {
               dumpNextSymbol();
               addCol(yyleng);
               return(DOtok);
             }
"for"        {
               dumpNextSymbol();
               addCol(yyleng);
               return(FORtok);
             }
"goto"       {
               dumpNextSymbol();
               addCol(yyleng);
               return(GOTOtok);
             }
"continue"   {
               dumpNextSymbol();
               addCol(yyleng);
               return(CONTINUEtok);
             }
"break"      {
               dumpNextSymbol();
               addCol(yyleng);
               return(BREAKtok);
             }
"return"     {
               dumpNextSymbol();
               addCol(yyleng);
               return(RETURNtok);
             }

{id}         {
                dumpNextSymbol();
                std::string name(yytext);
<<<<<<< HEAD

                // Node construction and insertion is done by the parser
                //SymbolNode * symNode = new SymbolNode(name, NULL, yylineno);
                //symTable.insertSymbol(name, symNode);

=======
                strcpy(yylval.sval, yytext);
                // SymbolNode * symNode = new SymbolNode(name, NULL, yylineno);
                // symTable.insertSymbol(name, symNode);
>>>>>>> symbol
                addCol(yyleng);
                checkIDLength(yytext);

                strcpy(yylval.sval, name.c_str()); // Pass the id's name to yacc
                return(IDENTIFIERtok);
             }
{int_const}       {
                    dumpNextSymbol();
                    yylval.ival = myatoi(yytext);
                    addCol(yyleng);
                    return(INTEGER_CONSTANTtok);
                  }
{real_const}      {
                    dumpNextSymbol();
                    yylval.dval = atof(yytext);
                    addCol(yyleng);
                    return(FLOATING_CONSTANTtok);
                  }
{char_const}      {
                    dumpNextSymbol();
                    yylval.cval = *yytext;
                    addCol(yyleng);
                    return(CHARACTER_CONSTANTtok);
                  }
{string_literal}  {
                    dumpNextSymbol();
<<<<<<< HEAD
                    //yylval.sval = yytext;
=======
>>>>>>> symbol
                    strcpy(yylval.sval, yytext);
                    addCol(yyleng);
                    return(STRING_LITERALtok);
                  }

.                 {
                    return(ERRORtok);
                    addCol(yyleng);
                    sprintf(errormsg, "ERROR: illegal character: line %d, col %d", linenum, colnum);
                    yyerror(errormsg);
                  }

%%
/* user code **************************************************************/
bool checkOverflow (unsigned long long val){
  std::stringstream ss;
  if (val > 4294967295){
        ss << "[L]: WARNING: Integer overflow" << ", line " << linenum << " col " << colnum;
        lexDebugger.debug(ss.str());
        return true;
  }
  return false;
}

void checkIDLength(char* charInput){
    int len = strlen(charInput);
    std::stringstream ss;

    if (len >= 10){
        ss << "[L]: WARNING: Very long ID " << charInput << ", line " << linenum << " col " << colnum;
        lexDebugger.debug(ss.str());
    }
}

void addCol(int matchedCol){
  colnum += matchedCol;
}

void addLine(int matchedLine){
  linenum += matchedLine;
}

void zeroCol(){
  colnum = 1;
}

void printToStderr(char* errormsg){
    fprintf(stderr, "%s\n", errormsg);
}
void printErrorLine(){
  //open current file(?)
  //print entire line
  //print ^ colnum spaces over on next line
}

unsigned long long btoi(char* text){
  unsigned long long val = 0;
  bool isValid = true;
  std::stringstream ss;

  while (*text && isValid){
    val <<= 1;
    if(*text == '0' || *text == '1'){
      val += *text++ - '0';
    }else{
      isValid = false;
      ss << "[L]: ERROR: invalid digit \'" << *text << "\' in binary constant, line " << linenum << " col " << colnum;
      lexDebugger.debug(ss.str());
    }
  }
  return val;
}
unsigned long long htoi(char* text){
  unsigned long long val = 0;
  bool isValid = true;
  std::stringstream ss;

  while(*text && isValid){
    val <<= 4;
    if(*text >= 'A' && *text <= 'F'){
      val += *text++ - 'A' + 10;
    }else if(*text >= '0' && *text <= 'F'){
      val += *text++ - '0';
    }else{
      isValid = false;
      ss << "[L]: ERROR: invalid digit \'" << *text << "\' in octal constant, line " << linenum << " col " << colnum;
      lexDebugger.debug(ss.str());
    }
  }
  return val;
}
unsigned long long otoi(char* text){
  unsigned long long val = 0;
  bool isValid = true;
  std::stringstream ss;

  while(*text && isValid){
    if(*text >= '0' && *text < '8'){
      val <<= 3;
      val += *text++ - '0';
    }else{
      isValid = false;
      ss << "[L]: ERROR: invalid digit \'" << *text << "\' in hexadecimal constant, line " << linenum << " col " << colnum;
      lexDebugger.debug(ss.str());
    }
  }
  return val;
}
int myatoi(char* text){
  unsigned long long val = 0;
  if(text[0] == '0' && (text[1] == 'b' || text[1] == 'B')){
    val = btoi(text+2);
  }else if(text[0] == '0' && (text[1] == 'x' || text[1] == 'X')){
    val = htoi(text+2);
  }else if(text[0] == '0'){
    val = otoi(text+1);
  }else{
    val = atoll(text);
  }
  return val;
}

void dumpNextSymbol(){
  std::stringstream ss;
  ss << "[L]: Next symbol -> " << yytext;
  lexSymbolDebugger.debug(ss.str());
}
