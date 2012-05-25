%{
%}
%x
space [ \t\n]
number [0-9]
grammar_name [gG]{number}
%%
<INITIAL>{space}*{grammar_name}{space}*={space}*\( fprintf(yyout, "Gramar %s\n", yytext);

