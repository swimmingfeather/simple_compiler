#ifndef word_h
#define word_h
struct word{
	int type;
	char* value;
	int line;
	int colume;
	struct word* next;
};
extern void chain_add_node(struct word* words,int type, char* value, int nline, int nchar);
extern void free_node(struct word* words);
#endif
