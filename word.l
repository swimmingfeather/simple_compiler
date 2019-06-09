%{
//该部分为c语言的各项声明，和c语言语法一致
#include <stdlib.h>
#include <string.h>
#include "syntax_tree.h"
#include "syntax_tree.tab.h"
//int nchar, nword, nline = 1;
//extern struct syntax_tree* syn_tree_root;
struct syntax_tree* new_node();
//%}后的部分为Lex的宏定义，用于在第一个%%后替换字符串
//第一个%%后的部分为Lex的正则表达式，表达式后的{}内为c语言的语句，匹配到特定表达式后执行语句块内语句
%}

GOTO goto
IF if
ELSE else
MAIN main
NUMBER [0-9]+
TYPE int|double|char
left_s_bracket \(
right_s_bracket \)
left_b_bracket	\{
right_b_bracket \}
semicolon ;
sign_opt_l \+|\-
sign_opt_h \*|\/
equal =
comma ,
TAG [_a-zA-Z][_a-zA-Z0-9]*:
ID [_a-zA-Z][_a-zA-Z0-9]*

%%
{TYPE} {
	new_node();
	return type;
}

{GOTO} {
	new_node();
	return _goto;
}

{IF} {
	new_node();
	return _if;
}
{ELSE} {
	new_node();
	return _else;
}
{NUMBER} {
	new_node();
	return number;
}
{MAIN} {
	new_node();
	return _main;
}
{TAG} {
	new_node();
	return tag;
}
{ID} {
	new_node();
	return id;
}
{left_s_bracket} {
	new_node();
	return left_s_bracket;
}
{right_s_bracket} {
	new_node();
	return right_s_bracket;
}
{left_b_bracket} {
	new_node();
	return left_b_bracket;
}
{right_b_bracket} {
	new_node();
	return right_b_bracket;
}
{semicolon} {
	new_node();
	return semicolon;
}
{sign_opt_l} {
	new_node();
	return sign_opt_l;
}
{sign_opt_h} {
	new_node();
	return sign_opt_h;
}
{equal} {
	new_node();
	return equal;
}
{comma} {
	new_node();
	return comma;
}
%%
//该部分也符合c语言的语法，可更改lex及yywrap函数内容或者新建函数，
//以下部分和"%{、%}"之间的部分皆会直接复制到lex.yy.c文件中
struct syntax_tree* new_node(){
	yylval.node = (struct syntax_tree*)malloc(sizeof(struct syntax_tree));
	yylval.node->value = strdup(yytext);
	yylval.node->left = NULL;
	yylval.node->right = NULL;
	//printf("%s\n", yytext);
	return yylval.node;
}
int yywrap()
{
	return 1;
}
