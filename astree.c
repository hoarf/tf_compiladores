#include "astree.h"
#include <stdio.h>

#define TAB  0x5F;

//Private prototypes

const char * selecionaMensagemPorTipo(int tipo);
const char * getNodeString(int tipo);

void check_declarations_and_usage(ASTREE * root);
void check_data_types(ASTREE * root);
void check_argument_matching(ASTREE * root);
int getDataTypeByNodeType(int nodeType);
int getExpressionType(ASTREE* node);
int isExpressionOfType(int type, ASTREE * expressionNode); 
int isDeclarationType(int type);
int isOperationLogical(int nodeType);
int isOperationArithmetic(int nodeType);
int isOperationRelational(int nodeType);
int isCallCompatible(CALL_LIST* list, ASTREE* node);
int createParamList(ASTREE * node,ASTREE* son, int dataType);

//End Private Prototypes

ASTREE * astree_create(int type, HASH_NODE* symbol,ASTREE* son1, ASTREE* son2, ASTREE* son3, ASTREE* son4) 
{
	ASTREE* ast = (ASTREE*) malloc(sizeof(ASTREE));
	ast->symbol = symbol;
	ast->type = type;
	ast->sons[0] = son1;
	ast->sons[1] = son2;
	ast->sons[2] = son3;
	ast->sons[3] = son4;
	return ast;
}

ASTREE * astree_create_symbol(int type, HASH_NODE* symbol) 
{
	ASTREE* ast = (ASTREE*) malloc(sizeof(ASTREE));
	ast->symbol = symbol;
	ast->type = type;
	ast->sons[0] = 0;
	ast->sons[1] = 0;
	ast->sons[2] = 0;
	ast->sons[3] = 0;
	return ast;
}

ASTREE * astree_create_basic(int type, HASH_NODE* symbol,ASTREE * son1) 
{
	ASTREE* ast = (ASTREE*) malloc(sizeof(ASTREE));
	ast->symbol = symbol;
	ast->type = type;
	ast->sons[0] = son1;
	ast->sons[1] = 0;
	ast->sons[2] = 0;
	ast->sons[3] = 0;
	return ast;	
}

ASTREE * astree_create_default(int type,ASTREE* son1) 
{
	ASTREE* ast = (ASTREE*) malloc(sizeof(ASTREE));
	ast->symbol = 0;
	ast->type = type;
	ast->sons[0] = son1;
	ast->sons[1] = 0;
	ast->sons[2] = 0;
	ast->sons[3] = 0;
	return ast;
}

ASTREE * astree_create_empty(int type) 
{
	ASTREE* ast = (ASTREE*) malloc(sizeof(ASTREE));
	ast->symbol = 0;
	ast->type = type;
	ast->sons[0] = 0;
	ast->sons[1] = 0;
	ast->sons[2] = 0;
	ast->sons[3] = 0;
	return ast;
}

char * insereTabulacao(int level) 
{
	if (level != 0) 
	{
		int i;
		char * ret = calloc(level-1,sizeof(char));
		for (i = 0; i < level; ++i) 
			ret[i] = TAB;
		return ret;
	} else 
		return "";
}

void imprimeNodo(ASTREE* arvore,FILE * file) 
{  
	if (arvore) 
	{
		fprintf(file,"%s",getNodeString(arvore->type)); 
		int i;
		for (i = 0; i < 4; ++i) 
			imprimeNodo(arvore->sons[i],file);
	}
}

void astree_toFile(ASTREE*arvore, const char* filenName) 
{
	FILE * fp = fopen( filenName,  "w" );
	imprimeNodo(arvore,fp);
	fclose(fp);
}

void astree_exibe(ASTREE* arvore, int level) 
{
	if (arvore != NULL) 
	{
		int i;
		printf("%s%s\n",insereTabulacao(level),selecionaMensagemPorTipo(arvore->type));
		int nextLevel= ++level;
		for (i = 0; i < 4; ++i) 
			astree_exibe(arvore->sons[i], nextLevel);
	}
}
const char * selecionaMensagemPorTipo(int tipo) 
{
	switch (tipo) 
	{	
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
		case ASTN_FV:
			return "float value";
		case ASTN_BV:
			return "boolean value";
		case ASTN_CV:
			return "char value";
		case ASTN_IV:
			return "int value";
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
		case ASTN_LIST_ARG:
			return "lista de argumentos";
		case ASTN_EXP_OP:
			return "binary op";
		case ASTN_EXP:
			return "( exp )";
		default:
			return "????";
	}
}


const ASTREE * gRoot;
char* get_usage_type_name(int t)
{
	switch (t)
	{
		case SYMBOL_USAGE_TYPE_FUNCTION:
			return "função";			
		case SYMBOL_USAGE_TYPE_VARIABLE:
			return "variável";
		case SYMBOL_USAGE_TYPE_VECTOR:
			return "vetor";
		default:
			return "erro";
	}	
}


void astree_check_semantics(ASTREE * tree) {
	//gRoot = tree;
	// print();
	check_declarations_and_usage(tree);
	print();
}



void check_declarations_and_usage(ASTREE * root)
{
	if (root != NULL)
	{
		int i;
		if (root->symbol)
			root->symbol->data_type = getDataTypeByNodeType(root->type);

		if (root->symbol != NULL) 
		{
			if (root->symbol->usage_type != SYMBOL_USAGE_TYPE_UNUSED && (isDeclarationType(root->type)))
				printf("Simbolo %s já declarado\n", root->symbol->value);
			else 
			{
				if (root->type == ASTN_VAD || root->type == ASTN_VED ) 
					{
						root->symbol->usage_type = SYMBOL_USAGE_TYPE_VARIABLE;
						root->symbol->data_type = getDataTypeByNodeType(root->sons[0]->type);
					}
				if (root->type == ASTN_VED) root->symbol->usage_type = SYMBOL_USAGE_TYPE_VECTOR;
				if (root->type == ASTN_HEADER) root->symbol->usage_type = SYMBOL_USAGE_TYPE_FUNCTION;
			}
			if (root->type == ASTN_HEADER && root->sons[1])
			{
				if (root->sons[1]->type == ASTN_LIST_ARG)
					createParamList(root,root->sons[1]->sons[0], getDataTypeByNodeType(root->sons[1]->sons[1]->type));
				else 
				{
					CALL_LIST * item = malloc(sizeof(CALL_LIST));
					item->dataType = getDataTypeByNodeType(root->sons[1]->sons[0]->type);
					root->symbol->list = item;
				}		
			}	
		}	
		// vvvvvv top-down 
		//=============================================================================
		for (i=0;i<4;++i)
			check_declarations_and_usage(root->sons[i]);	
		//=============================================================================
		// ^^^^^^ botton-up

		if ((root->type == ASTN_SYMBOL_VAR || root->type == ASTN_INPUT) && root->symbol->usage_type == SYMBOL_USAGE_TYPE_UNUSED) 
			printf("Simbolo %s não declarado. \n", root->symbol->value);
		else 
			if (root->type == ASTN_SYMBOL_VAR && root->symbol->usage_type != SYMBOL_USAGE_TYPE_VARIABLE) 
				printf("Simbolo %s usado como variável, mas declarado como %s \n", root->symbol->value, get_usage_type_name(root->symbol->usage_type));
		else 
			if (root->type == ASTN_SYMBOL_VAR && root->symbol->usage_type != SYMBOL_USAGE_TYPE_VARIABLE) 
				printf("Simbolo %s usado como variável, mas declarado como %s \n", root->symbol->value, get_usage_type_name(root->symbol->usage_type));
		else 
			if (root->type == ASTN_SYMBOL_VEC && getExpressionType(root->sons[0]) != HASH_DATA_TYPE_INT)  
				printf("Índices de vetores devem ser inteiros %s \n", root->symbol->value);
		else
			if (root->type == ASTN_EXP_OP)
			{
				int type1 = getExpressionType(root->sons[0]);
				int type2 = getExpressionType(root->sons[2]);
				if (!isOperationDefined(type1,root->sons[1]->type) || type1 != type2 )
				 	printf("Operação não suportada para os tipos destes operadores\n"); 
			}
		else
			if (root->type == ASTN_FUNCALL) 
			{
				if ((root->sons[0] && !root->symbol->list) || (!root->sons[0] && root->symbol->list)) 
				{	
					printf("A lista de argumentos chamada não confere com a declarada em %s\n", root->symbol->value);				 
				}
				else if (root->type == ASTN_FUNCALL && !isCallCompatible(root->symbol->list,root->sons[0]))
					printf("A lista de argumentos chamada não confere com a declarada em %s\n", root->symbol->value);
			}
	}
}


int isCallCompatible(CALL_LIST* list,ASTREE* item) 
{
	if (item->sons[1])
		return  list && item->sons[1]->symbol->data_type == list->dataType &&
				  isCallCompatible(list->next, item->sons[0]);
	else	
		return list && getDataTypeByNodeType( item->type) == list->dataType;  
}


int createParamList(ASTREE * node, ASTREE* son, int dataType)
{
	if (son)
	{
		if (son->sons[0])
			  createParamList(
		      node,
			  son->sons[0],
			  son->sons[1]?getDataTypeByNodeType(son->sons[1]->type):getDataTypeByNodeType(son->sons[0]->type));
		CALL_LIST * item = malloc(sizeof(CALL_LIST));
		item->dataType = dataType;	
		item->next = node->symbol->list;
		node->symbol->list = item;

	}
}


int getExpressionType(ASTREE* node) 
{
	if (node->symbol)
		return node->symbol->data_type;
	else if (node->type == ASTN_EXP_OP || node->type == ASTN_EXP)
		return getExpressionType(node->sons[0]);
}

int getDataTypeByNodeType(int nodeType) 
{
	switch (nodeType) 
	{
		case ASTN_IT: case ASTN_IV:
			return HASH_DATA_TYPE_INT;
		case ASTN_FT: case ASTN_FV:
			return HASH_DATA_TYPE_FLOAT;
		case ASTN_BT:  case ASTN_BV:
			return HASH_DATA_TYPE_BOOL;
		case ASTN_CT: case ASTN_CV:
			return HASH_DATA_TYPE_CHAR;
		case ASTN_SV:
			return HASH_DATA_TYPE_STRING;
		default:
			return HASH_DATA_TYPE_UNDEFINED;
	}
}

const char * getNodeString(int tipo) 
{
	switch (tipo) {
		default:
		return "????";
	}
}

int isOperationDefined(int dataType, int nodeType) 
{
	switch (dataType)
	{
		case HASH_DATA_TYPE_INT: case HASH_DATA_TYPE_FLOAT:
			return isOperationArithmetic(nodeType) || isOperationRelational(nodeType);
		case HASH_DATA_TYPE_BOOL:
			return isOperationLogical(nodeType);
		case HASH_DATA_TYPE_CHAR: case HASH_DATA_TYPE_STRING:
			return 0;
	}
}

int isOperationLogical(int nodeType)
{
	return nodeType == ASTN_OP_OR ||nodeType == ASTN_OP_AND; 
}

int isOperationArithmetic(int nodeType)
{
	return nodeType == ASTN_OP_ADD ||nodeType == ASTN_OP_SUB ||nodeType == ASTN_OP_DIV || nodeType == ASTN_OP_MUL; 
}

int isOperationRelational(int nodeType)
{
	return nodeType == ASTN_OP_LT ||nodeType == ASTN_OP_GT ||nodeType == ASTN_OP_NE || nodeType == ASTN_OP_EQ 
			|| nodeType == ASTN_OP_LE || nodeType == ASTN_OP_GE; 
}

int isDeclarationType(int type)
{
	return type  == ASTN_VAD || type == ASTN_VED || type == ASTN_FUNCTION;
}



