#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    词法分析
    输入：字符串形式的源程序
    输出：诸多特定数据结构的单词符号
*/
//struct word{

//};

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
	//for test
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
	for(
		int i = 0, tmp = 0;
		1; tmp++){

		while(input_buf[tmp]== '\n' || input_buf[tmp]>=' '){

			scan_buf[i++] = input_buf[tmp++];
		}
		if(input_buf[tmp] == '\0'){
			scan_buf[i] = '\0';
			break;
		}
	}
	//for test
	printf("%s", &scan_buf);



    return 0;
}

