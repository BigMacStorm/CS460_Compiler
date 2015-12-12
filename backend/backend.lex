digit [0-9]
letter [a-zA-Z_]
ws   [ \r\t\v\f]
newlines \n+
%%

"Decl:" {
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

[a-zA-Z_]+:	{
							printf("%s\n", yytext);
						}

%%

int main() {
	yyparse();
	return 0;
}
