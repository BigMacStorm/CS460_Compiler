/*  A bare minimum Yacc parser generator
    Currently accepts all input
    David Vaughan
*/

%start program

%{
#include <stdio.h>
typedef int YYSTYPE;
%}

%%

program :
        ;

%%

int main() {
    yyparse();
    return 0;
}

// This causes a warning right now
// Not sure how to suppress it yet
void yyerror(char* msg) {
    printf("%s\n", msg);
}
