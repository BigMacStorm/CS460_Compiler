/* Helpful regex's */

letter [a-zA-Z_]
digit [0-9]
id {letter}({letter}|{digit})*
label [a-zA-Z_]+:
temp [a-zA-Z_]+
assign " := "

%%

/* Actual regex's for 3ac code */

%{ /* Niki */ %}
"Decl:"
{
  BEGIN(DECLARE);
}

%{ /* Niki */ %}
<DECLARE>{letter}+{digit}+  {
  //prints match as the label of the variable and .word
  //yytext + : + \t + .word + \t
}

%{ /* Niki */ %}
<DECLARE>{digit}+ {
  //prints number
  //yytext + , + space
}

%{ /* Niki */ %}
<DECLARE>{letter} {
  //prints letter
  //yytext + , + space
}

%{ /* Niki */ %}
<DECLARE>";"  {
  //returns to regular lex
  BEGIN(INITIAL);
}

%{ /* David */ %}
{label} {
  printf("%s\n", yytext);
}

%{ /* David */ %}
"if "{id}" goto "{label} {
}

%{ /* David */ %}
"if "{temp}" goto "{label} {
}

%{ /* David */ %}
"goto "{label} {
}

%{ /* Aaron */ %}
%{ /* regex's for all the assignments */ %}
{id}{assign}{id} {
}

%{ /* assignments here */ %}

%{ /* comparisons here */ %}

%{ /* address stuff here */ %}

%%

int main() {
	yyparse();
	return 0;
}
