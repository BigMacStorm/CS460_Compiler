/*  A minimal Lex scanner generator
    Passes tokens which are undefined yet to yacc
*/
%top {
	#include "y.tab.h"
	#include <stdlib.h>
}

%%
auto			return(AUTO);
break			return(BREAK);
case			return(CASE);
char			return(CHAR);
const			return(CONST);
continue		return(CONT);
default			return(DEFAULT);
do				return(DO);
double			return(DOUBLE);
else			return(ELSE);
enum			return(ENUM);
extern			return(EXTERN);
float			return(FLOAT);
for				return(FOR);
goto			return(GOTO);
if				return(IF);
int				return(INT);
long			return(LONG);
register		return(REG);
return			return(RETURN);
short			return(SHORT);
signed			return(SIGNED);
sizeof			return(SIZEOF);
static			return(STATIC);
struct			return(STRUCT);
switch			return(SWITCH);
typedef			return(TYPED);
union			return(UNION);
unsigned		return(UNSIGNED);
void			return(VOID);
volatile		return(VOLATILE);
while			return(WHILE);
\+				return(PLUS);
\-				return(MINUS);
\*				return(MULT);
\/				return(DIV);
[0-9]+			{
				yylval = atoi(yytext);
				return(INTEGER);
				}
;				return(SEMI);
\(				return(OPEN);
\)				return(CLOSE);
[ \t\n]+		{
				//do stuff for line numbers
				}
([a-zA-Z]+[0-9]*)+	{
					//Check mode of symbol table
					//insert or update ID
					return(ID);
					}
.				return(ERROR);

%%

int yywrap (void) {
	return 1;
}
