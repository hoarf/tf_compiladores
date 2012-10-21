#ifndef ASTREE_H_
#define ASTREE_H_

#include "m_hash.c"

typedef struct _ASTREE {
	int type;
	ASTREE* son1;
	ASTREE* son2;
	ASTREE* son3;
	ASTREE* son4;
	HASH_NODE * symbol;
} ASTREE;

ASTREE * create(void);

void print(void);

#endif /* ASTREE_H_ */
