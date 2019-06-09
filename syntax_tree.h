#ifndef syntax_tree_h
#define syntax_tree_h
//syntax_tree.h文件由先前词法分析的word.h文件修改而来
#include <stdarg.h>
#include <stdio.h>
struct syntax_tree{
	int type;		//节点类型
	char* value;	//节点值
	int line;		//行号
	int colume;		//列号
	struct syntax_tree* left;	//左孩子地址
	struct syntax_tree* right;
};
extern struct syntax_tree* chain_add_node(int num, ...);
//extern void free_node(struct syntax_tree* words);
extern int PrintSpace(int Count,FILE* out);
extern int PrintSyntaxTree(struct syntax_tree* Head,int Count,FILE* out);
#endif
