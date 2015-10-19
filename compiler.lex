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
extern void yyerror(const char* s);
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
void dumpNextSymbol(const char* token);

unsigned long long btoi(char*);
unsigned long long otoi(char* text);
unsigned long long htoi(char* text);
int myatoi(char*);

const char* LEX_FILE = "llog.txt";
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

%x COMMENT

/* token rules and actions ***************************************************/
%%
{scomment}"!!S" {  symTable.writeFile(); }
{newlines}   {
               addLine(yyleng);
               zeroCol();
             }
{ws}         {  addCol(yyleng); }
{scomment}   {  addLine(1); }
"/*"            {
                    //start of comment block
                    BEGIN(COMMENT);
                }
<COMMENT>\n     {   addLine(yyleng); }
<COMMENT>.      ;
<COMMENT>"*/"   {
                    //end comment block
                    BEGIN(INITIAL);
                }

"sizeof"     {
               dumpNextSymbol("SIZEOFtok");
               addCol(yyleng);
               return(SIZEOFtok);
             }
"->"         {
               dumpNextSymbol("PTR_OPtok");
               addCol(yyleng);
               return(PTR_OPtok);
             }
"++"         {
               dumpNextSymbol("INC_OPtok");
               addCol(yyleng);
               return(INC_OPtok);
             }
"--"         {
               dumpNextSymbol("DEC_OPtok");
               addCol(yyleng);
               return(DEC_OPtok);
             }
"<<"         {
               dumpNextSymbol("LEFT_OPtok");
               addCol(yyleng);
               return(LEFT_OPtok);
             }
">>"         {
               dumpNextSymbol("RIGHT_OPtok");
               addCol(yyleng);
               return(RIGHT_OPtok);
             }
"<="         {
               dumpNextSymbol("LE_OPtok");
               addCol(yyleng);
               return(LE_OPtok);
             }
">="         {
               dumpNextSymbol("GE_OPtok");
               addCol(yyleng);
               return(GE_OPtok);
             }
"=="         {
               dumpNextSymbol("EQ_OPtok");
               addCol(yyleng);
               return(EQ_OPtok);
             }
"!="         {
               dumpNextSymbol("NE_OPtok");
               addCol(yyleng);
               return(NE_OPtok);
             }
"&&"         {
               dumpNextSymbol("AND_OPtok");
               addCol(yyleng);
               return(AND_OPtok);
             }
"||"         {
               dumpNextSymbol("OR_OPtok");
               addCol(yyleng);
               return(OR_OPtok);
             }

"*="         {
               dumpNextSymbol("MUL_ASSIGNtok");
               addCol(yyleng);
               return(MUL_ASSIGNtok);
             }
"/="         {
               dumpNextSymbol("DIV_ASSIGNtok");
               addCol(yyleng);
               return(DIV_ASSIGNtok);
             }
"%="         {
               dumpNextSymbol("MOD_ASSIGNtok");
               addCol(yyleng);
               return(MOD_ASSIGNtok);
             }
"+="         {
               dumpNextSymbol("ADD_ASSIGNtok");
               addCol(yyleng);
               return(ADD_ASSIGNtok);
             }
"-="         {
               dumpNextSymbol("SUB_ASSIGNtok");
               addCol(yyleng);
               return(SUB_ASSIGNtok);
             }
"<<="        {
               dumpNextSymbol("LEFT_ASSIGNtok");
               addCol(yyleng);
               return(LEFT_ASSIGNtok);
             }
">>="        {
               dumpNextSymbol("RIGHT_ASSIGNtok");
               addCol(yyleng);
               return(RIGHT_ASSIGNtok);
             }
"&="         {
               dumpNextSymbol("AND_ASSIGNtok");
               addCol(yyleng);
               return(AND_ASSIGNtok);
             }
"^="         {
               dumpNextSymbol("XOR_ASSIGNtok");
               addCol(yyleng);
               return(XOR_ASSIGNtok);
             }
"|="         {
               dumpNextSymbol("OR_ASSIGNtok");
               addCol(yyleng);
               return(OR_ASSIGNtok);
             }
"("          {
               dumpNextSymbol("OPEN_PARENtok");
               addCol(yyleng);
               return(OPEN_PARENtok);
             }
")"          {
               dumpNextSymbol("CLOSE_PARENtok");
               addCol(yyleng);
               return(CLOSE_PARENtok);
             }
("{"|"<%")   {
               dumpNextSymbol("OPEN_CURLYtok");
               addCol(yyleng);
               return(OPEN_CURLYtok);
             }
("}"|"%>")   {
               dumpNextSymbol("CLOSE_CURLYtok");
               addCol(yyleng);
               return(CLOSE_CURLYtok);
             }
("["|"<:")   {
               dumpNextSymbol("OPEN_SQUAREtok");
               addCol(yyleng);
               return(OPEN_SQUAREtok);
             }
("]"|":>")   {
               dumpNextSymbol("CLOSE_SQUAREtok");
               addCol(yyleng);
               return(CLOSE_SQUAREtok);
             }

"."          {
               dumpNextSymbol("PERIODtok");
               addCol(yyleng);
               return(PERIODtok);
             }
","          {
               dumpNextSymbol("COMMAtok");
               addCol(yyleng);
               return(COMMAtok);
             }
":"          {
               dumpNextSymbol("COLONtok");
               addCol(yyleng);
               return(COLONtok);
             }
";"          {
               dumpNextSymbol("SEMItok");
               addCol(yyleng);
               return(SEMItok);
             }
"="          {
               dumpNextSymbol("EQUALtok");
               addCol(yyleng);
               return(EQUALtok);
             }
"&"          {
               dumpNextSymbol("UNARY_ANDtok");
               addCol(yyleng);
               return(UNARY_ANDtok);
             }
"!"          {
               dumpNextSymbol("UNARY_BANGtok");
               addCol(yyleng);
               return(UNARY_BANGtok);
             }
"~"          {
               dumpNextSymbol("UNARY_TILDEtok");
               addCol(yyleng);
               return(UNARY_TILDEtok);
             }
"*"          {
               dumpNextSymbol("UNARY_ASTERISKtok");
               addCol(yyleng);
               return(UNARY_ASTERISKtok);
             }
"/"          {
               dumpNextSymbol("FORWARD_SLASHtok");
               addCol(yyleng);
               return(FORWARD_SLASHtok);
             }
"+"          {
               dumpNextSymbol("UNARY_PLUStok");
               addCol(yyleng);
               return(UNARY_PLUStok);
             }
"-"          {
               dumpNextSymbol("UNARY_MINUStok");
               addCol(yyleng);
               return(UNARY_MINUStok);
             }
"%"          {
               dumpNextSymbol("PERCENTtok");
               addCol(yyleng);
               return(PERCENTtok);
             }
"<"          {
               dumpNextSymbol("LEFT_ANGLEtok");
               addCol(yyleng);
               return(LEFT_ANGLEtok);
             }
">"          {
               dumpNextSymbol("RIGHT_ANGLEtok");
               addCol(yyleng);
               return(RIGHT_ANGLEtok);
             }
"^"          {
               dumpNextSymbol("UP_CARROTtok");
               addCol(yyleng);
               return(UP_CARROTtok);
             }
"|"          {
               dumpNextSymbol("PIPEtok");
               addCol(yyleng);
               return(PIPEtok);
             }
"?"          {
               dumpNextSymbol("QUESTION_MARKtok");
               addCol(yyleng);
               return(QUESTION_MARKtok);
             }

"typedef"    {
               dumpNextSymbol("TYPEDEFtok");
               addCol(yyleng);
               return(TYPEDEFtok);
             }
"extern"     {
               dumpNextSymbol("EXTERNtok");
               addCol(yyleng);
               return(EXTERNtok);
             }
"static"     {
               dumpNextSymbol("STATICtok");
               addCol(yyleng);
               return(STATICtok);
             }
"auto"       {
               dumpNextSymbol("AUTOtok");
               addCol(yyleng);
               return(AUTOtok);
             }
"register"   {
               dumpNextSymbol("REGISTERtok");
               addCol(yyleng);
               return(REGISTERtok);
             }
"char"       {
               dumpNextSymbol("CHARtok");
               addCol(yyleng);
               return(CHARtok);
             }
"short"      {
               dumpNextSymbol("SHORTtok");
               addCol(yyleng);
               return(SHORTtok);
             }
"int"        {
               dumpNextSymbol("INTtok");
               addCol(yyleng);
               return(INTtok);
             }
"long"       {
               dumpNextSymbol("LONGtok");
               addCol(yyleng);
               return(LONGtok);
             }
"signed"     {
               dumpNextSymbol("SIGNEDtok");
               addCol(yyleng);
               return(SIGNEDtok);
             }
"unsigned"   {
               dumpNextSymbol("UNSIGNEDtok");
               addCol(yyleng);
               return(UNSIGNEDtok);
             }
"float"      {
               dumpNextSymbol("FLOATtok");
               addCol(yyleng);
               return(FLOATtok);
             }
"double"     {
               dumpNextSymbol("DOUBLEtok");
               addCol(yyleng);
               return(DOUBLEtok);
             }
"const"      {
               dumpNextSymbol("CONSTtok");
               addCol(yyleng);
               return(CONSTtok);
             }
"volatile"   {
               dumpNextSymbol("VOLATILEtok");
               addCol(yyleng);
               return(VOLATILEtok);
             }
"void"       {
               dumpNextSymbol("VOIDtok");
               addCol(yyleng);
               return(VOIDtok);
             }
"struct"     {
               dumpNextSymbol("STRUCTtok");
               addCol(yyleng);
               return(STRUCTtok);
             }
"union"      {
               dumpNextSymbol("UNIONtok");
               addCol(yyleng);
               return(UNIONtok);
             }
"enum"       {
               dumpNextSymbol("ENUMtok");
               addCol(yyleng);
               return(ENUMtok);
             }
"..."        {
               dumpNextSymbol("ELIPSIStok");
               addCol(yyleng);
               return(ELIPSIStok);
             }
"case"       {
               dumpNextSymbol("CASEtok");
               addCol(yyleng);
               return(CASEtok);
             }
"default"    {
               dumpNextSymbol("DEFAULTtok");
               addCol(yyleng);
               return(DEFAULTtok);
             }
"if"         {
               dumpNextSymbol("IFtok");
               addCol(yyleng);
               return(IFtok);
             }
"else"       {
               dumpNextSymbol("ELSEtok");
               addCol(yyleng);
               return(ELSEtok);
             }
"switch"     {
               dumpNextSymbol("SWITCHtok");
               addCol(yyleng);
               return(SWITCHtok);
             }
"while"      {
               dumpNextSymbol("WHILEtok");
               addCol(yyleng);
               return(WHILEtok);
             }
"do"         {
               dumpNextSymbol("DOtok");
               addCol(yyleng);
               return(DOtok);
             }
"for"        {
               dumpNextSymbol("FORtok");
               addCol(yyleng);
               return(FORtok);
             }
"goto"       {
               dumpNextSymbol("GOTOtok");
               addCol(yyleng);
               return(GOTOtok);
             }
"continue"   {
               dumpNextSymbol("CONTINUEtok");
               addCol(yyleng);
               return(CONTINUEtok);
             }
"break"      {
               dumpNextSymbol("BREAKtok");
               addCol(yyleng);
               return(BREAKtok);
             }
"return"     {
               dumpNextSymbol("RETURNtok");
               addCol(yyleng);
               return(RETURNtok);
             }

{id}         {
                dumpNextSymbol("id");
                std::string name(yytext);
                strcpy(yylval.sval, yytext);
                // SymbolNode * symNode = new SymbolNode(name, NULL, yylineno);
                // symTable.insertSymbol(name, symNode);
                addCol(yyleng);
                checkIDLength(yytext);

                strcpy(yylval.sval, name.c_str()); // Pass the id's name to yacc
                return(IDENTIFIERtok);
             }
{int_const}       {
                    dumpNextSymbol("INTEGER_CONSTANTtok");
                    yylval.ival = myatoi(yytext);
                    addCol(yyleng);
                    return(INTEGER_CONSTANTtok);
                  }
{real_const}      {
                    dumpNextSymbol("FLOATING_CONSTANTtok");
                    yylval.dval = atof(yytext);
                    addCol(yyleng);
                    return(FLOATING_CONSTANTtok);
                  }
{char_const}      {
                    dumpNextSymbol("CHARACTER_CONSTANTtok");
                    yylval.cval = *yytext;
                    addCol(yyleng);
                    return(CHARACTER_CONSTANTtok);
                  }
{string_literal}  {
                    dumpNextSymbol("STRING_LITERALtok");
                    strcpy(yylval.sval, yytext);
                    addCol(yyleng);
                    return(STRING_LITERALtok);
                  }

.                 {
                    addCol(yyleng);
                    sprintf(errormsg, "ERROR: illegal character: line %d, col %d", linenum, colnum);
                    yyerror(errormsg);
                    return(ERRORtok);
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

    if (len >= 32){
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

void dumpNextSymbol(const char* token){
  std::stringstream ss;
  ss << "//" << yytext << std::endl << token << std::endl;
  lexSymbolDebugger.debug(ss.str());
}
