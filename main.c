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
	//Ϊ�˼���Unix/Linux��Windows��\n\r�Ĵ���
	tmp = fread(&input_buf, 1, tmp, f);
	fclose(f);
	input_buf[tmp] = '\0';
	//=====for test=====
	//printf("%s", &input_buf);

    //Ԥ����
    //ֻ����ɾ��ע�ͼ�ȥ���ǻ��еĸ�ʽ�����ַ�

	char scan_buf[tmp*sizeof(char) + 1];
	tmp = 0;

	while(1){
        //ֱ��������һ��'/'������һ�ַ��Ƿ�Ϊ'/'��'*'
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
        //scan_buf��ֻ�����ɼ��ַ�������
		while(input_buf[tmp]== '\n' || input_buf[tmp]>=' '){

			scan_buf[j++] = input_buf[tmp++];
		}
		if(input_buf[tmp] == '\0'){
			scan_buf[j] = '\0';
			tmp = 0;
			tmp = (unsigned int)j;//�洢scan_buf��ʵ�����ô�С
			break;
		}
	}
	//=====for test=====
	//printf("%s", &scan_buf);

	f=tmpfile();//c�����д�����ʱ�ļ��ı�׼�⺯��
	fwrite(&scan_buf, 1, tmp, f);
	//�ڴ˴������ļ���λ�ã�����lex�������ļ���ĩβ��ʼƥ��
	fseek(f, 0, SEEK_SET);
}
int main(int argc, char** args)
{
	FILE* f = fopen(args[1], "r");
	if( NULL == f){
		printf("�ļ�������\nThe file is not existed.");
		return -1;
	}
    preprocess(f);//�ļ�Ԥ����

    //����YACC�����﷨����

    //yyinΪYACC��LEX���е��ļ��������Դ��������﷨������Դ�����ļ�
	extern FILE *yyin;
	yyin = f;
	//���º�����syntax_tree.tab.c��
	yyparse();

    fclose(f);

    //����﷨����syntax_tree_out.txt���ͷ�����ռ�
    PrintSyntaxTree(syn_tree_root, 0, fopen("syntax_tree_out.txt", "w+"));
    //PrintSyntaxTree(syn_tree_root, 0, stdout);

	//free_node(syn_tree_root);


    return 0;
}

