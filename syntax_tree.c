#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "syntax_tree.h"
//syntax_tree.c�ļ�����ǰ�ʷ�������word.c�޸Ķ���
struct syntax_tree* chain_add_node(int num, ...){
	struct syntax_tree* tmp = NULL, *parent_node = NULL;

	va_list valist;
	va_start(valist, num);

	tmp = va_arg(valist, struct syntax_tree *);
	parent_node = (struct syntax_tree*)malloc(sizeof(struct syntax_tree));
	parent_node->left = tmp;
	parent_node->right = NULL;
	//printf("\t%s--%s\n", tmp->value, tmp->left ? (tmp->left)->value : "��");
	for(int i = 0; i < num - 1; i++){
		tmp->right = va_arg(valist, struct syntax_tree *);
		tmp = tmp->right;
		//printf("\t%s--%s\n", tmp->value, tmp->left ? (tmp->left)->value : "��");
	}
	//printf("\t====\n");
	tmp->right = NULL;

	va_end(valist);
	//strcpy((tmp->next)->value, value);
	return parent_node;
}
//void free_node(struct syntax_tree* words){
    //if(words == NULL)
    //    return;
    //free_node(words->left);
    //free_node(words->right);
    //free(words->value);
    //free(words);
//}

/*
��ӡ�ո�,��ӡ�﷨��ʱ����,���﷨������
*/
int PrintSpace(int Count,FILE*out)
{
    int i=0;
    for(i=0; i<Count; i++)
        fprintf(out," ");
    return 0;
}
/*
��ӡ�﷨�����ͷ��ڴ�
*/
int PrintSyntaxTree(struct syntax_tree* Head,int Count,FILE*out)
{
    if(Head)
    {
        int i=0;
        i=fprintf(out,"<%s>",Head->value);
        if(Head->right)
            fprintf(out,"-");
        PrintSyntaxTree(Head->right,Count+i+2,out);
        if(Head->left)
        {
            fprintf(out,"\n");
            PrintSpace(Count+3,out);
            fprintf(out,"|");
            PrintSyntaxTree(Head->left,Count,out);
        }
		free(Head->value);
		free(Head);
    }
    return 0;
}
