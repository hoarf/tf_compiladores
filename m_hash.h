#ifndef M_HASH_H_
#define M_HASH_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define HASH_SIZE 977

typedef struct _Hash_Node HASH_NODE;

struct _Hash_Node {
	char * value;
	int type;
	HASH_NODE * next;
};

int getAddress(const char* value);

HASH_NODE* tabela[HASH_SIZE];

void insertNode(const char* value, int type);

void print(void);

void init(void);

#endif /* M_HASH_H_ */
