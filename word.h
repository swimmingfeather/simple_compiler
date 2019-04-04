#ifndef word_h
#define word_h
struct word{
	int type;
	char* value;
	int line;
	int colume;
	struct word* next;
};
#endif
