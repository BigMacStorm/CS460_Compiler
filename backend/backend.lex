/* Helpful regex's */

letter [a-zA-Z_]
digit [0-9]
id {letter}({letter}|{digit})*
label [a-zA-Z_]+:
temp [a-zA-Z_]+
assign " := "

%%

%{ /* Actual regex's for 3ac code */ %}

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
  //prints number continuing a list
  //yytext + , + space
}

%{ /* Niki */ %}
<DECLARE>{letter} {
  //prints letter continuing a list
  //yytext + , + space
}

%{ /* Niki */ %}
<DECLARE>{digit}+";" {
  //prints single number or number at the end of a list
  //yytext
}

%{ /* Niki */ %}
<DECLARE>{letter}";" {
  //prints single letter or letter at the end of a list
  //yytext
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
%{ /* assignments here */ %}
{id}{assign}{id} {
}

%{ /* Niki */ %}
%{ /* comparisons here */ %}

%{ /* David */ %}
%{ /* address stuff here */ %}

%%

int main() {
	yyparse();
	return 0;
}
