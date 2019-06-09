#ifndef syntax_tree_h
#define syntax_tree_h
//syntax_tree.h�ļ�����ǰ�ʷ�������word.h�ļ��޸Ķ���
#include <stdarg.h>
#include <stdio.h>
struct syntax_tree{
	int type;		//�ڵ�����
	char* value;	//�ڵ�ֵ
	int line;		//�к�
	int colume;		//�к�
	struct syntax_tree* left;	//���ӵ�ַ
	struct syntax_tree* right;
};
extern struct syntax_tree* chain_add_node(int num, ...);
//extern void free_node(struct syntax_tree* words);
extern int PrintSpace(int Count,FILE* out);
extern int PrintSyntaxTree(struct syntax_tree* Head,int Count,FILE* out);
#endif
