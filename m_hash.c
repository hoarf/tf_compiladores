#include "m_hash.h"


/* fonte: http://research.cs.vt.edu/AVresearch/hashing/strings.php */
int getAddress(const char* value) {
	int i, soma = 0;
	for(i=0; i<strlen(value); ++i)
		soma += value[i];
	return soma % HASH_SIZE;
}

HASH_NODE * insertNode(const char* value, int type) {

	int address = getAddress(value);
	HASH_NODE * nodo = malloc(sizeof(HASH_NODE));
	nodo->type = type;
	nodo->value = calloc(strlen(value)+1,sizeof(char));
	strcpy(nodo->value, value);
	nodo->next = NULL;
	nodo->next = tabela[address];
	tabela[address] = nodo;
	return nodo;

}


void initMe(void) {
	int i;
	for (i = 0; i < HASH_SIZE; ++i) {
		tabela[i] = NULL;
	}
}

void print(void) {
	int i;
	for (i = 0; i < HASH_SIZE; ++i) {
		if (tabela[i] != NULL) {
			HASH_NODE * node = tabela[i];
			while (node != NULL) {
				printf("P: %d V: %s T: %d\n",i, node->value,node->type);
				node = node->next;
			}
		}
	}
}

