#ifndef M_HASH_H_
#define M_HASH_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define HASH_SIZE 977

#define SYMBOL_UNDEFINED	0
#define SYMBOL_LIT_INTEGER	1
#define SYMBOL_LIT_FLOATING	2
#define SYMBOL_LIT_TRUE		3
#define SYMBOL_LIT_FALSE	4
#define SYMBOL_LIT_CHAR		5
#define SYMBOL_LIT_STRING	6
#define SYMBOL_IDENTIFIER	7

typedef struct _Hash_Node HASH_NODE;

struct _Hash_Node {
	char * value;
	int type;
	HASH_NODE * next;
};

int getAddress(const char* value);

HASH_NODE* tabela[HASH_SIZE];

HASH_NODE * insertNode(const char* value, int type);

void print(void);

void initMe(void);

#endif /* M_HASH_H_ */
