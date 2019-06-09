#include <stdio.h>
#include <stdlib.h>
#include "syntax_tree.h"


struct syntax_tree * syn_tree_root = NULL;
extern void yyparse();

void preprocess(FILE* f){
    unsigned int tmp = 0;


    fseek(f, 0, SEEK_END);
	tmp = ftell(f);

	char input_buf[tmp*sizeof(char) + 1];

	fseek(f, 0, SEEK_SET);
	//为了兼容Unix/Linux和Windows对\n\r的处理
	tmp = fread(&input_buf, 1, tmp, f);
	fclose(f);
	input_buf[tmp] = '\0';
	//=====for test=====
	//printf("%s", &input_buf);

    //预处理
    //只进行删除注释及去除非换行的格式控制字符

	char scan_buf[tmp*sizeof(char) + 1];
	tmp = 0;

	while(1){
        //直到遇到第一个'/'后检测下一字符是否为'/'或'*'
        while(input_buf[tmp++] != '/'){
            if(tmp > sizeof(input_buf))
                goto here;
        }

        if(input_buf[tmp] == '/'){
            input_buf[tmp-1] = '\t';
            while(1){
                input_buf[tmp++] = '\t';
                if(input_buf[tmp] == '\n')
                    break;
            }
        }
        else if(input_buf[tmp] == '*'){
            input_buf[tmp-1] = '\t';
            while(1){
                input_buf[tmp++] = '\t';
                if(input_buf[tmp] == '*' && input_buf[tmp+1] == '/'){
                    input_buf[tmp] = '\t';
                    input_buf[tmp+1] = '\t';
                    break;
                }
            }
        }
	}
here:
    tmp = 0;
	for(
		int j = 0;
		1; tmp++){
        //scan_buf中只保留可见字符及换行
		while(input_buf[tmp]== '\n' || input_buf[tmp]>=' '){

			scan_buf[j++] = input_buf[tmp++];
		}
		if(input_buf[tmp] == '\0'){
			scan_buf[j] = '\0';
			tmp = 0;
			tmp = (unsigned int)j;//存储scan_buf的实际有用大小
			break;
		}
	}
	//=====for test=====
	//printf("%s", &scan_buf);

	f=tmpfile();//c语言中创建临时文件的标准库函数
	fwrite(&scan_buf, 1, tmp, f);
	//在此处重置文件流位置，否则lex将会在文件流末尾开始匹配
	fseek(f, 0, SEEK_SET);
}
int main(int argc, char** args)
{
	FILE* f = fopen(args[1], "r");
	if( NULL == f){
		printf("文件不存在\nThe file is not existed.");
		return -1;
	}
    preprocess(f);//文件预处理

    //调用YACC进行语法分析

    //yyin为YACC和LEX共有的文件流，用以存放需进行语法分析的源代码文件
	extern FILE *yyin;
	yyin = f;
	//以下函数在syntax_tree.tab.c中
	yyparse();

    fclose(f);

    //输出语法树至syntax_tree_out.txt并释放链表空间
    PrintSyntaxTree(syn_tree_root, 0, fopen("syntax_tree_out.txt", "w+"));
    //PrintSyntaxTree(syn_tree_root, 0, stdout);

	//free_node(syn_tree_root);


    return 0;
}

