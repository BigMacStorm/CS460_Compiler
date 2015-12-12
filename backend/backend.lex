/* Helpful regex's */

letter [a-zA-Z_]
digit [0-9]
id {letter}({letter}|{digit})*
label [a-zA-Z_]+:
temp [a-zA-Z_]+
%%

/* Actual regex's for 3ac code */

"Decl:"
{
  BEGIN(DECLARE);
}

<DECLARE>{letter}+{digit}+  {
  //prints match as the label of the variable and .word
  //yytext + : + \t + .word + \t
}
<DECLARE>{digit}+ {
  //prints number
  //yytext + , + space
}
<DECLARE>{letter} {
  //prints letter
  //yytext + , + space
}
<DECLARE>";"  {
  //returns to regular lex
  BEGIN(INITIAL);
}

label {
  printf("%s\n", yytext);
}

"if "id" goto "label {
}

"if "temp" goto "label {
}

"goto "label {
}

%%

int main() {
	yyparse();
	return 0;
}
