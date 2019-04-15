%{

#include <stdlib.h>
#include "word.h"
int nchar, nword, nline = 1;
extern struct word* words;

%}

keywords auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|int|long|register|return|short|signed|sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|while

operantor \+|\-|\*|\/|\<|\<=|\>|\>=|=|==|!=|\(|\)|\^|'|#|&|&&|\||\|\||%|~|<<|>>|\[|\]|\{|\}|\.|!|\\

separator ,|;|:

id [_a-zA-Z][_a-zA-Z0-9]*

constant ([0-9])+|(".*")
%%
\n {
	nline++;
	nchar = 0;
}
[ \t]+ { nword++, nchar += yyleng; }
{keywords} {chain_add_node(words, 1, yytext, nline, nchar);nword++, nchar += yyleng;}
{operantor} {chain_add_node(words, 2, yytext, nline, nchar);nword++, nchar += yyleng;}
{separator}  {chain_add_node(words, 3, yytext, nline, nchar);nword++, nchar += yyleng;}
{id} {chain_add_node(words, 4, yytext, nline, nchar);nword++, nchar += yyleng;}
{constant} {chain_add_node(words, 5, yytext, nline, nchar);nword++, nchar += yyleng;}
. {
	nchar++;
}
%%
void lex(FILE* f)
{
	yyin = f;
	yylex();
	//printf("%d\t%d\t%d\n", nchar, nword, nline);
}
int yywrap()
{
	return 1;
}
