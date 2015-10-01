/*  A minimal Lex scanner generator
    Passes tokens which are undefined yet to yacc
	col and line numbers are recorded but not used in an error function yet
*/
%{
	#include "y.tab.h"
	#include <stdlib.h>
	int linenum = 0;
	int colnum = 0;
	char errormsg [70];
%}

%%
auto			{
				colnum = colnum + yyleng; //if you can think of a more efficient way for this go for it
				return(AUTO);
				}

break			{
				colnum = colnum + yyleng;
				return(BREAK);
				}

case			{
				colnum = colnum + yyleng;
				return(CASE);
				}

char			{
				colnum = colnum + yyleng;
				return(CHAR);
				}

const			{
				colnum = colnum + yyleng;
				return(CONST);
				}

continue		{
				colnum = colnum + yyleng;
				return(CONT);
				}

default			{
				colnum = colnum + yyleng;
				return(DEFAULT);
				}

do				{
				colnum = colnum + yyleng;
				return(DO);
				}

double			{
				colnum = colnum + yyleng;
				return(DOUBLE);
				}

else			{
				colnum = colnum + yyleng;
				return(ELSE);
				}

enum			{
				colnum = colnum + yyleng;
				return(ENUM);
				}

extern			{
				colnum = colnum + yyleng;
				return(EXTERN);
				}

float			{
				colnum = colnum + yyleng;
				return(FLOAT);
				}

for				{
				colnum = colnum + yyleng;
				return(FOR);
				}

goto			{
				colnum = colnum + yyleng;
				return(GOTO);
				}

if				{
				colnum = colnum + yyleng;
				return(IF);
				}

int				{
				colnum = colnum + yyleng;
				return(INT);
				}

long			{
				colnum = colnum + yyleng;
				return(LONG);
				}

register		{
				colnum = colnum + yyleng;
				return(REG);
				}

return			{
				colnum = colnum + yyleng;
				return(RETURN);
				}

short			{
				colnum = colnum + yyleng;
				return(SHORT);
				}

signed			{
				colnum = colnum + yyleng;
				return(SIGNED);
				}

sizeof			{
				colnum = colnum + yyleng;
				return(SIZEOF);
				}

static			{
				colnum = colnum + yyleng;
				return(STATIC);
				}

struct			{
				colnum = colnum + yyleng;
				return(STRUCT);
				}

switch			{
				colnum = colnum + yyleng;
				return(SWITCH);
				}

typedef			{
				colnum = colnum + yyleng;
				return(TYPED);
				}

union			{
				colnum = colnum + yyleng;
				return(UNION);
				}

unsigned		{
				colnum = colnum + yyleng;
				return(UNSIGNED);
				}

void			{
				colnum = colnum + yyleng;
				return(VOID);
				}

volatile		{
				colnum = colnum + yyleng;
				return(VOLATILE);
				}

while			{
				colnum = colnum + yyleng;
				return(WHILE);
				}

\+				{
				colnum = colnum + 1;
				return(PLUS);
				}

\-				{
				colnum = colnum + 1;
				return(MINUS);
				}

\*				{
				colnum = colnum + 1;
				return(MULT);
				}

\/				{
				colnum = colnum + 1;
				return(DIV);
				}

[0-9]+			{
				//do symbol table stuff if connected to a variable
				colnum = colnum + yyleng;
				return(INTEGER);
				}

[0-9]+\.[0-9]+	{
				//do symbol table stuff if connected to a variable
				colnum = colnum + yyleng;
				return(FLOATNUM);
				}

;				{
				colnum = colnum + 1;
				return(SEMI);
				}

\(				{
				colnum = colnum + 1;
				return(OPEN);
				}

\)				{
				colnum = colnum + 1;
				return(CLOSE);
				}

[ \t]+			{
				colnum = colnum + yyleng;
				}
				
\n+				{
				colnum = 1;
				linenum = linenum +1;
				}
				
"[a-zA-Z0-9]+"	{
				colnum = colnum + yyleng;
				return(STRING);
				}
				
[a-zA-Z0-9]+	{ 
				//Check mode of symbol table
				//edit mode of symbol table?
				//insert or update ID
				colnum = colnum + yyleng;
				return(ID);
				}
				
.				{
				sprintf(errormsg, "invalid character or operation at line %d, col %d", linenum, colnum);
				//also print line of error
				yyerror(errormsg);
				return(ERROR);
				}

%%

int yywrap (void) {
	return 1;
}
