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

%}

%token type
%token id 
%token _goto tag
%token _if _else
%token number
%start function

%%
	
statement
	: declare
	| assignment
	| jump
	| branch
	| function
	;
	
declare
	: type id_list ';'	{
							
						}
	;
id_list: id ids
	;
ids
	: ids ',' id
	| /*该条为空产生式*/
	;


assignment
	: id '=' expression ';'	{
							}							
	;
expression
	: arithmetic
	;
arithmetic
	: e
	;
e
	: e '+' t
	| t
	;
t
	: t '*' f
	| f
	;
f
	: '(' e ')'
	| number
	;
	
	
jump
	: _goto tag ';'	{
					}									
	;
	
branch
	: _if '(' expression ')' '{' statement '}' other_part	{
															}
	;	
other_part
	: many_elseif_parts
	| else_part
	;
many_elseif_parts
	: many_elseif_parts elseif_part
	|
	;
elseif_part
	: _else _if '(' expression ')' '{' statement '}'
	;
else_part
	: _else '{' statement '}'
	;
	
function
	: id '(' ')' ';' 	{
						}
	;
%%