#ifndef M_HASH_H_
#define M_HASH_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define HASH_SIZE 					977

#define SYMBOL_UNDEFINED			0
#define SYMBOL_LIT_INTEGER			1
#define SYMBOL_LIT_FLOATING			2
#define SYMBOL_LIT_TRUE				3
#define SYMBOL_LIT_FALSE			4
#define SYMBOL_LIT_CHAR				5
#define SYMBOL_LIT_STRING			6
#define SYMBOL_IDENTIFIER			7
#define SYMBOL_VARIABLE				8
#define SYMBOL_LABEL				9
#define SYMBOL_USAGE_TYPE_FUNCTION	0
#define SYMBOL_USAGE_TYPE_VARIABLE 	1
#define SYMBOL_USAGE_TYPE_VECTOR 	2
#define SYMBOL_USAGE_TYPE_UNUSED 	3

#define HASH_DATA_TYPE_INT 			0
#define HASH_DATA_TYPE_FLOAT 		1
#define HASH_DATA_TYPE_CHAR 		2
#define HASH_DATA_TYPE_BOOL 		3
#define HASH_DATA_TYPE_UNDEFINED 	4
#define HASH_DATA_TYPE_STRING 		5

typedef struct _Hash_Node HASH_NODE;
typedef struct _Call_List CALL_LIST;

struct _Call_List 
{
	int data_type;
	CALL_LIST * next;
};

struct _Hash_Node 
{
	char * value;
	int type;
	int usage_type;
	int data_type;
	CALL_LIST * list;
	HASH_NODE * next;
};

int getAddress(const char* value);

void print(void);
void initMe(void);
HASH_NODE * fixedSymbol(int type);

HASH_NODE* makeTmp(void);
HASH_NODE* tabela[HASH_SIZE];
HASH_NODE* insertNode(const char* value, int type);
HASH_NODE* makeLabel(void);


int display_ast;
int display_tac;
int display_symbol;
int display_file;
int numberOfErrors;

int getTypeSize(HASH_NODE* symbol);


#endif /* M_HASH_H_ */
