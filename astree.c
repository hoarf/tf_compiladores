  #include "astree.h"
  #include <stdio.h>

  #define TAB  0x5F;


//Private prototypes

const char * selecionaMensagemPorTipo(int tipo);
const char * getNodeString(int tipo);

void check_declarations_and_usage(ASTREE * root);
void check_data_types(ASTREE * root);
void check_argument_matching(ASTREE * root);
void lookFor(int type, char* value);

//End Private Prototypes

ASTREE * astree_create(int type, HASH_NODE* symbol,ASTREE* son1, ASTREE* son2, ASTREE* son3, ASTREE* son4) {
	ASTREE* ast = (ASTREE*) malloc(sizeof(ASTREE));
	ast->symbol = symbol;
	ast->type = type;
	ast->sons[0] = son1;
	ast->sons[1] = son2;
	ast->sons[2] = son3;
	ast->sons[3] = son4;
	return ast;
}

ASTREE * astree_create_symbol(int type, HASH_NODE* symbol) {
	ASTREE* ast = (ASTREE*) malloc(sizeof(ASTREE));
	ast->symbol = symbol;
	ast->type = type;
	ast->sons[0] = 0;
	ast->sons[1] = 0;
	ast->sons[2] = 0;
	ast->sons[3] = 0;
	return ast;
}

ASTREE * astree_create_basic(int type, HASH_NODE* symbol,ASTREE * son1) {
	ASTREE* ast = (ASTREE*) malloc(sizeof(ASTREE));
	ast->symbol = symbol;
	ast->type = type;
	ast->sons[0] = son1;
	ast->sons[1] = 0;
	ast->sons[2] = 0;
	ast->sons[3] = 0;
	return ast;	
}

ASTREE * astree_create_default(int type,ASTREE* son1) {
	ASTREE* ast = (ASTREE*) malloc(sizeof(ASTREE));
	ast->symbol = 0;
	ast->type = type;
	ast->sons[0] = son1;
	ast->sons[1] = 0;
	ast->sons[2] = 0;
	ast->sons[3] = 0;
	return ast;
}

ASTREE * astree_create_empty(int type) {
	ASTREE* ast = (ASTREE*) malloc(sizeof(ASTREE));
	ast->symbol = 0;
	ast->type = type;
	ast->sons[0] = 0;
	ast->sons[1] = 0;
	ast->sons[2] = 0;
	ast->sons[3] = 0;
	return ast;
}

char * insereTabulacao(int level) {
	if (level != 0) {
		int i;
		char * ret = calloc(level-1,sizeof(char));
		for (i = 0; i < level; ++i) {
			ret[i] = TAB;
		}
		return ret;
	} else {
		return "";
	}
}

void imprimeNodo(ASTREE* arvore,FILE * file) {  
	if (arvore) {
		fprintf(file,"%s",getNodeString(arvore->type)); 
		int i;
		for (i = 0; i < 4; ++i) {
			imprimeNodo(arvore->sons[i],file);
		}
	}
}

void astree_toFile(ASTREE*arvore, const char* filenName) {
	FILE * fp = fopen( filenName,  "w" );
	imprimeNodo(arvore,fp);
	fclose(fp);
}

void astree_exibe(ASTREE* arvore, int level) {
	if (arvore != NULL) 
	{
		int i;
		printf("%s%s\n",insereTabulacao(level),selecionaMensagemPorTipo(arvore->type));
		int nextLevel= ++level;
		for (i = 0; i < 4; ++i) 
			astree_exibe(arvore->sons[i], nextLevel);
	}
}
void astree_exibe_bottom_up(ASTREE* arvore, int level) {
	if (arvore != NULL) 
	{
		int i;
		int nextLevel= ++level;
		for (i = 0; i < 4; ++i) 
			astree_exibe(arvore->sons[i], nextLevel);
		printf("%s%s\n",insereTabulacao(level),selecionaMensagemPorTipo(arvore->type));
		
	}
}
void astree_seek_dec_var(ASTREE* arvore, HASH_NODE* symbol) {		
	if (arvore != NULL)
	{				    
		if (arvore->type == ASTN_VAD)
		{
			if (strcmp(symbol->value, arvore->symbol->value))	
			{		
				printf("declarada: %s\n", symbol->value);
				return;
			}
		}
		int i;
		for (i = 0; i < 4; ++i)
			astree_seek_dec_var(arvore->sons[i], symbol);			
	}
}
void astree_sem_dec_var(ASTREE* arvore, ASTREE* topo) {
	if (arvore != NULL)
	{				    
		if (arvore->type == ASTN_SYMBOL_VAR)
		{
			printf("buscando: %s\n", arvore->symbol->value);
			astree_seek_dec_var(topo, arvore->symbol);
		}	
		int i;
		for (i = 0; i < 4; ++i)
			astree_sem_dec_var(arvore->sons[i], topo);			
	}
}
const char * selecionaMensagemPorTipo(int tipo) {
	switch (tipo) {	
		case ASTN_SYMBOL:
			return "symbol";
		case ASTN_FUNCALL:
			return "function call";
		case ASTN_SYMBOL_VAR:
			return "variavel";
		case ASTN_SYMBOL_VEC:
			return "vetor";
		case ASTN_VAD:
			return "VAD";
		case ASTN_VED:
			return "VED";
		case ASTN_IT:
			return "int";
		case ASTN_FT:
			return "float";
		case ASTN_CT:
			return "char";
		case ASTN_BT:
			return "bool";
		case ASTN_IV:
			return "inteiro";
		case ASTN_LIST:
			return "lista";
		case ASTN_FUNCTION:
			return "funcao";
		case ASTN_HEADER:
			return "cabecalho";
		case ASTN_IF:
			return "if";
		case ASTN_WHILE:
			return "while";
		case ASTN_INPUT:
			return "input";
		case ASTN_OUTPUT:
			return "output";
		case ASTN_RETURN:
			return "return";
		default:
			return "????";
	}
}


const ASTREE * gRoot;

void astree_check_semantics(ASTREE * tree) {
	//gRoot = tree;
	check_declarations_and_usage(tree);
}

void check_declarations_and_usage(ASTREE * root){
	if (root != NULL) {
		int i;
		if (root->type == ASTN_VAD) root->symbol->usage_type = SYMBOL_USAGE_TYPE_VARIABLE;
		if (root->type == ASTN_VED) root->symbol->usage_type = SYMBOL_USAGE_TYPE_VECTOR;
		if (root->type == ASTN_HEADER) root->symbol->usage_type = SYMBOL_USAGE_TYPE_FUNCTION;
		
		for (i=0;i<4;++i)
			check_declarations_and_usage(root->sons[i]);	

		if (root != NULL) {
			if (root->type == ASTN_SYMBOL_VAR && root->symbol->usage_type == -1)
				printf("Simbolo %s não declarado. \n", root->symbol->value);
			else if (root->type == ASTN_SYMBOL_VAR && root->symbol->usage_type != SYMBOL_USAGE_TYPE_VARIABLE) 
				printf("Simbolo %s declarado como variável, mas usado como outro tipo. \n", root->symbol->value);
		}
	}
}

const char * getNodeString(int tipo) {
	switch (tipo) {
		default:
		return "????";
	}
}