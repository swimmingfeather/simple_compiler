#include <stdio.h>
#include <stdlib.h>
#include "word.h"

/*
    词法分析
    输入：字符串形式的源程序
    输出：诸多特定数据结构的单词符号
*/
struct word * words = NULL;
extern void lex(FILE* f);


int main(int argc, char** args)
{
	FILE* f = fopen(args[1], "r");
	unsigned int tmp = 0;
	if( NULL == f){
		printf("文件不存在\nThe file is not existed.");
		return -1;
	}

	fseek(f, 0, SEEK_END);
	tmp = ftell(f);

	char input_buf[tmp*sizeof(char) + 1];

	fseek(f, 0, SEEK_SET);
	//为了兼容Unix/Linux和Windows
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
    //tmp放进for循环初始化后与外部的tmp实际上并不是同一个变量，防止两者混淆放在for循环外初始化
    tmp = 0;
	for(
		int j = 0;
		1; tmp++){

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

    //调用lex进行词法分析
	char* type_for_print[6] = {" ", "关键字", "操作符", "分隔符", "ID", "常量"};
	f=tmpfile();
	fwrite(&scan_buf, 1, tmp, f);
	//在此处重置文件流位置，否则lex将会在文件流末尾开始匹配
	fseek(f, 0, SEEK_SET);

    words = (struct word*)malloc(sizeof(struct word));
    words->next = NULL;
    words->value = NULL;
	lex(f);
	fclose(f);


	tmp = (unsigned int)(words->next);
	f = fopen("output.txt", "w");
	//printf("类型\t值\t行号\t列号\n");
	fprintf(f, "类型\t值\t行号\t列号\n");
	while((struct word*)tmp != NULL){
		//printf("%s\t%s\t%d\t%d\n",type_for_print[((struct word*)tmp)->type], ((struct word*)tmp)->value, ((struct word*)tmp)->line, ((struct word*)tmp)->colume );
        fprintf(f, "%s\t%s\t%d\t%d\n",type_for_print[((struct word*)tmp)->type], ((struct word*)tmp)->value, ((struct word*)tmp)->line, ((struct word*)tmp)->colume );

		tmp = (unsigned int)(((struct word*)tmp)->next);
	}
    fclose(f);


	//释放链表空间
	free_node(words);


    return 0;
}

