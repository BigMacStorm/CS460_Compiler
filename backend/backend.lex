
%%

/* Helpful regex's */

letter [a-zA-Z_]
digit [0-9]
id {letter}({letter}|{digit})*
label [a-zA-Z_]+:
temp [a-zA-Z_]+

/* Actual regex's for 3ac code */

"Decl:"
{
}

label {
  printf("%s\n", yytext);
}

"if "id" goto "label {
}

"if "temp" goto "label {
}

%%

int main() {
	yyparse();
	return 0;
}
