%{
/*该文件实现C语言中的语法单位如下
	变量声明语句：type id_list;
	赋值语句：id = expression;
	跳转语句: goto tag;
	分支语句：	if_part{statement}
				elseif_part{statement}
				else_part{statement}
	函数调用语句：id();


*/
#include "syntax_tree.h"
extern struct syntax_tree * syn_tree_root;
extern char* yytext;
extern struct syntax_tree* new_node();
%}
//以下共用体为属性文法的具体实现数据结构
%union{
	struct syntax_tree* node;
}

//以%token开头的为终结符
%token <node> type
%token <node> id 
%token <node> _goto 
%token <node> tag
%token <node> _if 
%token <node> _else
%token <node> number
%token <node> _main

%token <node> left_s_bracket
%token <node> right_s_bracket
%token <node> left_b_bracket
%token <node> right_b_bracket
%token <node> semicolon
%token <node> sign_opt_l
%token <node> sign_opt_h
%token <node> equal
%token <node> comma

//以%type开头的为非终结符
%type <node> main_function
%type <node> statements
%type <node> statement
%type <node> declare
%type <node> assignment
%type <node> jump
%type <node> branch
%type <node> function
%type <node> id_list
%type <node> ids
%type <node> expression
%type <node> arithmetic
%type <node> e
%type <node> t
%type <node> f
%type <node> other_part
%type <node> many_elseif_parts
%type <node> else_part
%type <node> elseif_part

//以%start开头的为文法的开始符号，若不特别指出则默认为第一条文法的左部符号
%start main_function

%%
/*
	以下内容格式为：
		左部
		：右部1{
			进行归约时所做的操作，符合c语言语法；
		}
		| 右部2{
			进行归约时所做的操作，符合c语言语法；
		}
	每个“左部：右部”都代指一条文法
	$$代指左部符号的语义值，$1、$2、$3分别指第1、2、3个右部符号的语义值
*/
main_function
	: type _main left_s_bracket right_s_bracket left_b_bracket statements right_b_bracket	{
												$$ = chain_add_node(7, $1,$2,$3,$4,$5,$6,$7);
												$$->value = "main_function";
												syn_tree_root = $$;
											}
											
statements
	: statements statement	{
								
								$$ = chain_add_node(2,$1,$2);
								$$->value = "statements";
							}
	|	/*该条为空产生式，后续不再提示*/{
			$$ = (struct syntax_tree*)malloc(sizeof(struct syntax_tree));
			$$->value = "statements";
			yytext = "null";
			$$->left = new_node();
			
		}

statement
	: declare 	{
					//printf("\t%s\n", $1->value);
					$$  = chain_add_node(1,$1);
					$$->value = "statement";
				}
	| assignment{
					$$  = chain_add_node(1,$1);
					$$->value = "statement";
				}
				
	| jump	{
				$$  = chain_add_node(1,$1);
				$$->value = "statement";
			}
	| branch	{
					$$ = chain_add_node(1,$1);
					$$->value = "statement";
				}
	| function	{
					$$ = chain_add_node(1,$1);
					$$->value = "statement";
				}
	;
	
declare
	: type id_list semicolon	{
							//printf("\t%s--%s--%s\n", $1->value, $2->value, $3->value);
							$$ = chain_add_node(3,$1,$2,$3);
							$$->value = "declare";
						}
	;
id_list: id ids	{
					//printf("\t%s--%s\n", $1->value, $2->value);
					$$ = chain_add_node(2,$1,$2);
					$$->value = "id_list";
				}
	;
ids
	: ids comma id	{
						//printf("\t%s--%s--%s\n", $1->value, $2->value, $3->value);
						$$ = chain_add_node(3,$1,$2,$3);
						$$->value = "ids";
					}
	| 	{
			$$ = (struct syntax_tree*)malloc(sizeof(struct syntax_tree));
			$$->value = "ids";
			yytext = "null";
			$$->left = new_node();
		}
	;


assignment
	: id equal expression semicolon	{
										$$ = chain_add_node(4,$1,$2,$3,$4);
										$$->value = "assignment";
									}							
	;
expression
	: arithmetic	{
						//printf("\t%s\n", $1->value);
						$$ = chain_add_node(1,$1);
						$$->value = "expression";
					}
	;
arithmetic
	: e	{
			$$ = chain_add_node(1,$1);
			$$->value = "arithmetic";
		}
	;
e
	: e sign_opt_l t	{
					$$ = chain_add_node(3,$1,$2,$3);
					$$->value = "e";
				}
	| t	{
			$$ = chain_add_node(1,$1);
			$$->value = "e";
		}
	;
t
	: t sign_opt_h f	{
					$$ = chain_add_node(3,$1,$2,$3);
					$$->value = "t";
				}
	| f	{
			$$ = chain_add_node(1,$1);
			$$->value = "t";
		}
	;
f
	: left_s_bracket e right_s_bracket	{
					$$ = chain_add_node(3,$1,$2,$3);
					$$->value = "f";
				}
	| number	{
					$$ = chain_add_node(1,$1);
					$$->value = "f";
				}
	;
	
	
jump
	: _goto id semicolon	{
						$$ = chain_add_node(3,$1,$2,$3);
						$$->value = "jump";
					}									
	;
	
branch
	: _if left_s_bracket expression right_s_bracket left_b_bracket statement right_b_bracket other_part	{
								$$ = chain_add_node(8,$1,$2,$3,$4,$5,$6,$7,$8);
								$$->value = "branch";
															}
	;	
other_part
	: many_elseif_parts else_part	{
										$$ = chain_add_node(2,$1,$2);
										$$->value = "other_part";
									}
	;
many_elseif_parts
	: many_elseif_parts elseif_part	{
										$$ = chain_add_node(2,$1,$2);
										$$->value = "many_elseif_parts";
									}
	|	{
			$$ = (struct syntax_tree*)malloc(sizeof(struct syntax_tree));
			$$->value = "many_elseif_parts";
			yytext = "null";
			$$->left = new_node();
		}
	;
elseif_part
	: _else _if left_s_bracket expression right_s_bracket left_b_bracket statement right_b_bracket	{
								$$ = chain_add_node(8,$1,$2,$3,$4,$5,$6,$7,$8);
								$$->value = "elseif_part";
														}
	;
else_part
	: _else left_b_bracket statement right_b_bracket	{
									$$ = chain_add_node(4,$1,$2,$3,$4);
									$$->value = "else_part";
								}
	|	{
			$$ = (struct syntax_tree*)malloc(sizeof(struct syntax_tree));
			$$->value = "else_part";
			yytext = "null";
			$$->left = new_node();
		}
	;
	
function
	: id left_s_bracket right_s_bracket semicolon 	{
							$$ = chain_add_node(4,$1,$2,$3,$4);
							$$->value = "function";
						}
	;
%%
//以下为YACC出错时的回调函数
void yyerror () {
   printf("There is a error");
}