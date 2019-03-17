#include <stdio.h>
#include <stdlib.h>

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

        unsigned int buf = (unsigned int)malloc(tmp*sizeof(char) + 1);

        fseek(f, 0, SEEK_SET);
        //为了兼容Unix/Linux和Windows
        tmp = fread((char*)buf, 1, tmp, f);
        *(char*)(buf+tmp) = '\0';
        //for test
        //printf("%s", (char*)buf);

    //预处理





    fclose(f);
    free((char*)buf);
    return 0;
}

