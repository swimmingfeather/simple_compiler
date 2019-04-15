%{
//该部分为c语言的各项声明，和c语言语法一致
#include <stdlib.h>
#include "word.h"
int nchar, nword, nline = 1;
extern struct word* words;

//%}后的部分为Lex的宏定义，用于在第一个%%后替换字符串
//第一个%%后的部分为Lex的正则表达式，表达式后的{}内为c语言的语句，匹配到特定表达式后执行语句块内语句
%}

keywords auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|int|long|register|return|short|signed|sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|while

operantor \+|\-|\*|\/|\<|\<=|\>|\>=|=|==|!=|\(|\)|\^|'|#|&|&&|\||\|\||%|~|<<|>>|\[|\]|\{|\}|\.|!|\\

separator ,|;|:

id [_a-zA-Z][_a-zA-Z0-9]*

constant ([0-9])+|\".*\"
%%
\n {
	nline++;
	nchar = 0;
}
[ \t]+ { nword++, nchar += yyleng; }
{keywords} {chain_add_node(words, 1, yytext, nline, nchar);nword++, nchar += yyleng;}
{id} {chain_add_node(words, 4, yytext, nline, nchar);nword++, nchar += yyleng;}
{constant} {chain_add_node(words, 5, yytext, nline, nchar);nword++, nchar += yyleng;}
{operantor} {chain_add_node(words, 2, yytext, nline, nchar);nword++, nchar += yyleng;}
{separator}  {chain_add_node(words, 3, yytext, nline, nchar);nword++, nchar += yyleng;}
. {
	nchar++;
}
%%
//该部分也符合c语言的语法，可更改lex及yywrap函数内容或者新建函数，
//以下部分和"%{、%}"之间的部分皆会直接复制到lex.yy.c文件中
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
