#include <stdio.h>
#include <stdlib.h>
#include "word.h"

/*
    �ʷ�����
    ���룺�ַ�����ʽ��Դ����
    ���������ض����ݽṹ�ĵ��ʷ���
*/
struct word * words = NULL;
extern void lex(FILE* f);


int main(int argc, char** args)
{
	FILE* f = fopen(args[1], "r");
	unsigned int tmp = 0;
	if( NULL == f){
		printf("�ļ�������\nThe file is not existed.");
		return -1;
	}

	fseek(f, 0, SEEK_END);
	tmp = ftell(f);

	char input_buf[tmp*sizeof(char) + 1];

	fseek(f, 0, SEEK_SET);
	//Ϊ�˼���Unix/Linux��Windows
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
    //tmp�Ž�forѭ����ʼ�������ⲿ��tmpʵ���ϲ�����ͬһ����������ֹ���߻�������forѭ�����ʼ��
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
			tmp = (unsigned int)j;//�洢scan_buf��ʵ�����ô�С
			break;
		}
	}
	//=====for test=====
	//printf("%s", &scan_buf);

    //����lex���дʷ�����
	char* type_for_print[6] = {" ", "�ؼ���", "������", "�ָ���", "ID", "����"};
	f=tmpfile();
	fwrite(&scan_buf, 1, tmp, f);
	//�ڴ˴������ļ���λ�ã�����lex�������ļ���ĩβ��ʼƥ��
	fseek(f, 0, SEEK_SET);

    words = (struct word*)malloc(sizeof(struct word));
    words->next = NULL;
    words->value = NULL;
	lex(f);
	fclose(f);


	tmp = (unsigned int)(words->next);
	f = fopen("output.txt", "w");
	//printf("����\tֵ\t�к�\t�к�\n");
	fprintf(f, "����\tֵ\t�к�\t�к�\n");
	while((struct word*)tmp != NULL){
		//printf("%s\t%s\t%d\t%d\n",type_for_print[((struct word*)tmp)->type], ((struct word*)tmp)->value, ((struct word*)tmp)->line, ((struct word*)tmp)->colume );
        fprintf(f, "%s\t%s\t%d\t%d\n",type_for_print[((struct word*)tmp)->type], ((struct word*)tmp)->value, ((struct word*)tmp)->line, ((struct word*)tmp)->colume );

		tmp = (unsigned int)(((struct word*)tmp)->next);
	}
    fclose(f);


	//�ͷ�����ռ�
	free_node(words);


    return 0;
}

