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
#include <vector>
#include <string>

extern SymbolTable symTable;
extern void yyerror(const char* s);
extern Debugger lexDebugger;
extern Debugger lexSymbolDebugger;
unsigned int linenum = 1;
unsigned int colnum = 1;

std::vector<std::string> sourceLine;
std::string listFileName;

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

               // Print the line of source code
               std::ofstream fout;
               fout.open(listFileName, std::ofstream::out | std::ofstream::app);
               for(int i = 0; i < sourceLine.size(); ++i)
                   fout << sourceLine[i] << " ";
               fout << std::endl;
               fout.close();

               sourceLine.clear();
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
               sourceLine.push_back(yytext);
               return(SIZEOFtok);
             }
"->"         {
               dumpNextSymbol("PTR_OPtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(PTR_OPtok);
             }
"++"         {
               dumpNextSymbol("INC_OPtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(INC_OPtok);
             }
"--"         {
               dumpNextSymbol("DEC_OPtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(DEC_OPtok);
             }
"<<"         {
               dumpNextSymbol("LEFT_OPtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(LEFT_OPtok);
             }
">>"         {
               dumpNextSymbol("RIGHT_OPtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(RIGHT_OPtok);
             }
"<="         {
               dumpNextSymbol("LE_OPtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(LE_OPtok);
             }
">="         {
               dumpNextSymbol("GE_OPtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(GE_OPtok);
             }
"=="         {
               dumpNextSymbol("EQ_OPtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(EQ_OPtok);
             }
"!="         {
               dumpNextSymbol("NE_OPtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(NE_OPtok);
             }
"&&"         {
               dumpNextSymbol("AND_OPtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(AND_OPtok);
             }
"||"         {
               dumpNextSymbol("OR_OPtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(OR_OPtok);
             }

"*="         {
               dumpNextSymbol("MUL_ASSIGNtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(MUL_ASSIGNtok);
             }
"/="         {
               dumpNextSymbol("DIV_ASSIGNtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(DIV_ASSIGNtok);
             }
"%="         {
               dumpNextSymbol("MOD_ASSIGNtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(MOD_ASSIGNtok);
             }
"+="         {
               dumpNextSymbol("ADD_ASSIGNtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(ADD_ASSIGNtok);
             }
"-="         {
               dumpNextSymbol("SUB_ASSIGNtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(SUB_ASSIGNtok);
             }
"<<="        {
               dumpNextSymbol("LEFT_ASSIGNtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(LEFT_ASSIGNtok);
             }
">>="        {
               dumpNextSymbol("RIGHT_ASSIGNtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(RIGHT_ASSIGNtok);
             }
"&="         {
               dumpNextSymbol("AND_ASSIGNtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(AND_ASSIGNtok);
             }
"^="         {
               dumpNextSymbol("XOR_ASSIGNtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(XOR_ASSIGNtok);
             }
"|="         {
               dumpNextSymbol("OR_ASSIGNtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(OR_ASSIGNtok);
             }
"("          {
               dumpNextSymbol("OPEN_PARENtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(OPEN_PARENtok);
             }
")"          {
               dumpNextSymbol("CLOSE_PARENtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(CLOSE_PARENtok);
             }
("{"|"<%")   {
               dumpNextSymbol("OPEN_CURLYtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(OPEN_CURLYtok);
             }
("}"|"%>")   {
               dumpNextSymbol("CLOSE_CURLYtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(CLOSE_CURLYtok);
             }
("["|"<:")   {
               dumpNextSymbol("OPEN_SQUAREtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(OPEN_SQUAREtok);
             }
("]"|":>")   {
               dumpNextSymbol("CLOSE_SQUAREtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(CLOSE_SQUAREtok);
             }

"."          {
               dumpNextSymbol("PERIODtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(PERIODtok);
             }
","          {
               dumpNextSymbol("COMMAtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(COMMAtok);
             }
":"          {
               dumpNextSymbol("COLONtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(COLONtok);
             }
";"          {
               dumpNextSymbol("SEMItok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(SEMItok);
             }
"="          {
               dumpNextSymbol("EQUALtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(EQUALtok);
             }
"&"          {
               dumpNextSymbol("UNARY_ANDtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(UNARY_ANDtok);
             }
"!"          {
               dumpNextSymbol("UNARY_BANGtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(UNARY_BANGtok);
             }
"~"          {
               dumpNextSymbol("UNARY_TILDEtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(UNARY_TILDEtok);
             }
"*"          {
               dumpNextSymbol("UNARY_ASTERISKtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(UNARY_ASTERISKtok);
             }
"/"          {
               dumpNextSymbol("FORWARD_SLASHtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(FORWARD_SLASHtok);
             }
"+"          {
               dumpNextSymbol("UNARY_PLUStok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(UNARY_PLUStok);
             }
"-"          {
               dumpNextSymbol("UNARY_MINUStok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(UNARY_MINUStok);
             }
"%"          {
               dumpNextSymbol("PERCENTtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(PERCENTtok);
             }
"<"          {
               dumpNextSymbol("LEFT_ANGLEtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(LEFT_ANGLEtok);
             }
">"          {
               dumpNextSymbol("RIGHT_ANGLEtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(RIGHT_ANGLEtok);
             }
"^"          {
               dumpNextSymbol("UP_CARROTtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(UP_CARROTtok);
             }
"|"          {
               dumpNextSymbol("PIPEtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(PIPEtok);
             }
"?"          {
               dumpNextSymbol("QUESTION_MARKtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(QUESTION_MARKtok);
             }

"typedef"    {
               dumpNextSymbol("TYPEDEFtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(TYPEDEFtok);
             }
"extern"     {
               dumpNextSymbol("EXTERNtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(EXTERNtok);
             }
"static"     {
               dumpNextSymbol("STATICtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(STATICtok);
             }
"auto"       {
               dumpNextSymbol("AUTOtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(AUTOtok);
             }
"register"   {
               dumpNextSymbol("REGISTERtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(REGISTERtok);
             }
"char"       {
               dumpNextSymbol("CHARtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(CHARtok);
             }
"short"      {
               dumpNextSymbol("SHORTtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(SHORTtok);
             }
"int"        {
               dumpNextSymbol("INTtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(INTtok);
             }
"long"       {
               dumpNextSymbol("LONGtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(LONGtok);
             }
"signed"     {
               dumpNextSymbol("SIGNEDtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(SIGNEDtok);
             }
"unsigned"   {
               dumpNextSymbol("UNSIGNEDtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(UNSIGNEDtok);
             }
"float"      {
               dumpNextSymbol("FLOATtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(FLOATtok);
             }
"double"     {
               dumpNextSymbol("DOUBLEtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(DOUBLEtok);
             }
"const"      {
               dumpNextSymbol("CONSTtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(CONSTtok);
             }
"volatile"   {
               dumpNextSymbol("VOLATILEtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(VOLATILEtok);
             }
"void"       {
               dumpNextSymbol("VOIDtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(VOIDtok);
             }
"struct"     {
               dumpNextSymbol("STRUCTtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(STRUCTtok);
             }
"union"      {
               dumpNextSymbol("UNIONtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(UNIONtok);
             }
"enum"       {
               dumpNextSymbol("ENUMtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(ENUMtok);
             }
"..."        {
               dumpNextSymbol("ELIPSIStok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(ELIPSIStok);
             }
"case"       {
               dumpNextSymbol("CASEtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(CASEtok);
             }
"default"    {
               dumpNextSymbol("DEFAULTtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(DEFAULTtok);
             }
"if"         {
               dumpNextSymbol("IFtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(IFtok);
             }
"else"       {
               dumpNextSymbol("ELSEtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(ELSEtok);
             }
"switch"     {
               dumpNextSymbol("SWITCHtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(SWITCHtok);
             }
"while"      {
               dumpNextSymbol("WHILEtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(WHILEtok);
             }
"do"         {
               dumpNextSymbol("DOtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(DOtok);
             }
"for"        {
               dumpNextSymbol("FORtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(FORtok);
             }
"goto"       {
               dumpNextSymbol("GOTOtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(GOTOtok);
             }
"continue"   {
               dumpNextSymbol("CONTINUEtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(CONTINUEtok);
             }
"break"      {
               dumpNextSymbol("BREAKtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
               return(BREAKtok);
             }
"return"     {
               dumpNextSymbol("RETURNtok");
               addCol(yyleng);
               sourceLine.push_back(yytext);
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
                sourceLine.push_back(yytext);
                return(IDENTIFIERtok);
             }
{int_const}       {
                    dumpNextSymbol("INTEGER_CONSTANTtok");
                    yylval.ival = myatoi(yytext);
                    addCol(yyleng);
                    sourceLine.push_back(yytext);
                    return(INTEGER_CONSTANTtok);
                  }
{real_const}      {
                    dumpNextSymbol("FLOATING_CONSTANTtok");
                    yylval.dval = atof(yytext);
                    addCol(yyleng);
                    sourceLine.push_back(yytext);
                    return(FLOATING_CONSTANTtok);
                  }
{char_const}      {
                    dumpNextSymbol("CHARACTER_CONSTANTtok");
                    yylval.cval = *yytext;
                    addCol(yyleng);
                    sourceLine.push_back(yytext);
                    return(CHARACTER_CONSTANTtok);
                  }
{string_literal}  {
                    dumpNextSymbol("STRING_LITERALtok");
                    strcpy(yylval.sval, yytext);
                    addCol(yyleng);
                    sourceLine.push_back(yytext);
                    return(STRING_LITERALtok);
                  }

.                 {
                    addCol(yyleng);
                    sourceLine.push_back(yytext);
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

  // Append the reduction to LEX_FILE
  std::ofstream fout;
  fout.open(LEX_FILE, std::ofstream::out | std::ofstream::app);
  fout << ss.str() << std::endl;
  fout.close();

  lexSymbolDebugger.debug(ss.str());
}
