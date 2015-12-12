
%%

"Decl:" {
				}

[a-zA-Z_]+:	{
							printf("%s\n", yytext);
						}

%%

int main() {
	yyparse();
	return 0;
}
