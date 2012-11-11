#ifndef ASTREE_H_
#define ASTREE_H_

#include "m_hash.h"

#define ASTN_ 1
#define ASTN_VAD 2
#define ASTN_IT 3
#define ASTN_FT 4
#define ASTN_BT 5
#define ASTN_CT 6
#define ASTN_VED 7
#define ASTN_IV 8
#define ASTN_LIST 9
#define ASTN_FUNCTION 10
#define ASTN_HEADER 11
#define ASTN_INPUT 12
#define ASTN_OUTPUT 13
#define ASTN_RETURN 14
#define ASTN_ASSIGNMENT 15
#define ASTN_IF 16
#define ASTN_WHILE 17


typedef struct _ASTREE ASTREE;

struct _ASTREE {
	int type;
	ASTREE* sons[4];
	HASH_NODE * symbol;

} ;

ASTREE* ast;

ASTREE * astree_create(int type, HASH_NODE* symbol,ASTREE* son1, ASTREE* son2, ASTREE* son3, ASTREE* son4);

ASTREE * astree_create_symbol(int type, HASH_NODE* symbol);

ASTREE * astree_create_default(int type, ASTREE * son1);

ASTREE * astree_create_basic(int type, HASH_NODE* symbol,ASTREE * son1);

ASTREE * astree_create_empty(int type);


void astree_exibe(ASTREE* arvore, int level);

void astree_toFile(ASTREE* arvore,const char* filenName);

#endif /* ASTREE_H_ */
