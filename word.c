#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "word.h"
void chain_add_node(struct word* words,int type, char* value, int nline, int nchar){
	struct word* tmp = words;
	while(tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = (struct word*)malloc(sizeof(struct word));
	(tmp->next)->next = NULL;
	(tmp->next)->type = type;
	(tmp->next)->value = (char *)malloc(sizeof(*value));
	strcpy((tmp->next)->value, value);
	(tmp->next)->line = nline;
	(tmp->next)->colume = nchar;
}
void free_node(struct word* words){
    struct word* i = words->next;
    while(i != NULL){
        if(words->value)
            free(words->value);
        free(words);
        words = i;
        i = i->next;
    }
    free(words->value);
    free(words);
}
