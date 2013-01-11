#include "m_hash.h"

//PROTOTIPOS

int printList(CALL_LIST* list);

//

HASH_NODE * fixedSymbol(int type)
{
	switch (type)
	{
		case SYMBOL_LIT_TRUE:
			return insertNode("true",SYMBOL_LIT_TRUE);
		case SYMBOL_LIT_FALSE:
		  return insertNode("false",SYMBOL_LIT_FALSE);
		 default:
		 	return NULL;
	}
}

int printList(CALL_LIST* list)
{
	if (list)
	{
		printf("%i->", list->data_type);
		printList(list->next);
	}
}

/* fonte: http://research.cs.vt.edu/AVresearch/hashing/strings.php */
int getAddress(const char* value) 
{
	int i, soma = 0;
	for(i=0; i<strlen(value); ++i)
		soma += value[i];
	return soma % HASH_SIZE;
}

HASH_NODE * insertNode(const char* value, int type) 
{
	int address = getAddress(value);
	HASH_NODE* tmpNode = tabela[address];
	
	while (tmpNode) 
	{
		if (strcmp(tmpNode->value, value) == 0) 
			return tmpNode;
		tmpNode = tmpNode->next;
	}

	HASH_NODE * nodo = malloc(sizeof(HASH_NODE));
	nodo->type = type;
	nodo->value = calloc(strlen(value)+1,sizeof(char));
	nodo->usage_type = SYMBOL_USAGE_TYPE_UNUSED;
	nodo->list = NULL;
	nodo->data_type = HASH_DATA_TYPE_UNDEFINED;
	strcpy(nodo->value, value);
	nodo->next = tabela[address];
	tabela[address] = nodo;
	return tabela[address];
}

void initMe(void)
{
	int i;
	for (i = 0; i < HASH_SIZE; ++i)
		tabela[i] = NULL;
}

void print(void) 
{
	int i;
	printf("======= Tabela Hash ========================================================\n");
	printf("Posição		Conteúdo	Tipo		Uso	Dado\n");
	for (i = 0; i < HASH_SIZE; ++i) 
	{
		if (tabela[i] != NULL) 
		{
			HASH_NODE * node = tabela[i];
			while (node != NULL) 
			{
				printf("%d\t\t%s\t\t%d\t\t%i\t%i\n",i, node->value,node->type, node->usage_type, node->data_type);
				if (node->list){
					printf("		|_>: ");
					printList(node->list);
					printf("\n");
				} 
					
				node = node->next;
			}
		}
	}
}

HASH_NODE * makeTmp(void)
{
	static int nextTmp = 0; 
	static char buffer[32] = ""; 
	sprintf(buffer,"_mY_nEw_Temp%d",nextTmp++);

	return insertNode(buffer,SYMBOL_VARIABLE);
}

HASH_NODE * makeLabel(void)
{
	static int nextLabel = 0; 
	static char bufferlbl[32] = ""; 
	sprintf(bufferlbl,"_mY_nEw_Label%d",nextLabel++);
	return insertNode(bufferlbl,SYMBOL_LABEL);
}

int getTypeSize(HASH_NODE* symbol)
{
	switch (symbol->data_type)
	{
		case HASH_DATA_TYPE_UNDEFINED:
			return -1;
		case HASH_DATA_TYPE_FLOAT: case HASH_DATA_TYPE_INT: case HASH_DATA_TYPE_BOOL: 
			return 4;
		case HASH_DATA_TYPE_CHAR:
			return 1;	
		case HASH_DATA_TYPE_STRING:
			return strlen(symbol->value);
	}
}