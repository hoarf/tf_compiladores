#include "astree.h"
#include <stdio.h>

#define TAB  0x5F;

//Private prototypes

int isUsageNotComaptible(ASTREE* root);
void fetchTypeFromSons(ASTREE* node);
const char * selecionaMensagemPorTipo(int tipo);
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
int isOperationNotDefined(int dataType, int nodeType);
int isCallNotCompatible(ASTREE* node,CALL_LIST* list);
void createParamList(ASTREE * node, ASTREE* son);
int isSymbolicItem(int type);
int getUsageType(int type);
char * getDataypeName(int dataType);
CALL_LIST* revertParamList(CALL_LIST* list);

//End Private Prototypes

ASTREE * astree_create(int type, HASH_NODE* symbol,ASTREE* son1, ASTREE* son2, ASTREE* son3, ASTREE* son4) 
{
	ASTREE* ast = (ASTREE*) malloc(sizeof(ASTREE));
	ast->symbol = symbol;
	ast->type = type;
	ast->data_type = HASH_DATA_TYPE_UNDEFINED;
	ast->lineNumber = getLineNumber();
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
	ast->data_type = HASH_DATA_TYPE_UNDEFINED;
	ast->sons[1] = 0;
	ast->lineNumber = getLineNumber();
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
	ast->data_type = HASH_DATA_TYPE_UNDEFINED;
	ast->lineNumber = getLineNumber();
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
	ast->data_type = HASH_DATA_TYPE_UNDEFINED;
	ast->sons[2] = 0;
	ast->lineNumber = getLineNumber();
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
	ast->lineNumber = getLineNumber();
	ast->sons[2] = 0;
	ast->data_type = HASH_DATA_TYPE_UNDEFINED;
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

void astree_exibe(ASTREE* arvore, int level) 
{
	if (arvore != NULL) 
	{
		int i;
		printf("%s%s",insereTabulacao(level),selecionaMensagemPorTipo(arvore->type));
		if (arvore->data_type != HASH_DATA_TYPE_UNDEFINED) printf("(T: %d)",arvore->data_type);
		if (arvore->symbol && arvore->symbol->data_type != HASH_DATA_TYPE_UNDEFINED) printf("(ST: %d)",arvore->symbol->data_type);
		if (arvore->symbol) printf("(%s)",arvore->symbol->value);
		if (isDeclarationType(arvore->type)) printf("*");
		printf("\n");
		int nextLevel= ++level;
		for (i = 0; i < 4; ++i) 
			astree_exibe(arvore->sons[i], nextLevel);
	}
}
const char * selecionaMensagemPorTipo(int tipo) 
{
	switch (tipo) 
	{	
		case ASTN_ASSIGNMENT:
			return "atribuicao";
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
		case ASTN_STATEMENT_LIST:
			return "HL STMT";
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
		case ASTN_EXP_OP:
			return "binary op";
		case ASTN_EXP:
			return "( exp )";
		default:
			return "????";
	}
}


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
	check_declarations_and_usage(tree);
	if (display_symbol) print();
}

int getUsageType(int type)
{
	switch (type)
	{
		case ASTN_VAD:
			return SYMBOL_USAGE_TYPE_VARIABLE;
		case ASTN_VED:
			return SYMBOL_USAGE_TYPE_VECTOR;
		case ASTN_HEADER:
			return SYMBOL_USAGE_TYPE_FUNCTION;
		default:
			return SYMBOL_USAGE_TYPE_UNUSED;
	}
}

void check_declarations_and_usage(ASTREE * root)
{
	if (root != NULL)
	{
		int i;

		//ATRIBUI O TIPO DOS NODOS BASE
		root->data_type = getDataTypeByNodeType(root->type);

		//DEFINE O TIPO DE USO DE CADA SYMBOLO
		if (root->symbol != NULL) 
		{
			// root->symbol->data_type = getDataTypeByNodeType(root->type);
			if (root->symbol->usage_type != SYMBOL_USAGE_TYPE_UNUSED && isDeclarationType(root->type))
				printf("Simbolo %s já declarado na linha %i\n", root->symbol->value, root->lineNumber);
			else if (isDeclarationType(root->type))
			{
				root->symbol->usage_type = getUsageType(root->type);
				root->symbol->data_type = getDataTypeByNodeType(root->sons[root->sons[1]?1:0]->type);
			}
		}

	

		// vvvvvv top-down 
		//=============================================================================
		for (i=0;i<4;++i)
			check_declarations_and_usage(root->sons[i]);	
		//=============================================================================
		// ^^^^^^ botton-up

		//ASSOCIA A CADA SYMBOLO DO TIPO FUNCAO A SUA LISTA DE SYMBOLOS PARAMETROS
		if (root->type == ASTN_HEADER )
		{
			createParamList(root,root->sons[1]);	
			root->symbol->list = revertParamList(root->symbol->list);
		} 
		 
		fetchTypeFromSons(root);

		if (root->symbol && root->symbol->usage_type == SYMBOL_USAGE_TYPE_UNUSED && root->symbol->type == SYMBOL_IDENTIFIER)
			printf("Simbolo %s não declarado na linha %i. \n", 
				root->symbol->value,
				root->lineNumber);

		if (isUsageNotComaptible(root)) 
			printf("Simbolo %s usado como %s, mas declarado como %s na linha %i\n", 
				root->symbol->value, 
				selecionaMensagemPorTipo(root->type),
				get_usage_type_name(root->symbol->usage_type),root->lineNumber);

		if (root->type == ASTN_SYMBOL_VEC && root->sons[0]->data_type != HASH_DATA_TYPE_INT)
				printf("Índices de vetores não inteiro na linha %i \n", root->lineNumber);


		if (root->type == ASTN_EXP_OP && (
			root->sons[0]->data_type == HASH_DATA_TYPE_UNDEFINED || root->sons[2]->data_type == HASH_DATA_TYPE_UNDEFINED
			|| isOperationNotDefined(root->sons[0]->symbol->data_type,root->sons[1]->type) 
			|| root->sons[0]->data_type != root->sons[2]->data_type))
			
			printf("Operação não suportada para os tipos destes operadores %s e %s na linha %i\n",
				getDataypeName(root->sons[0]->data_type),
				getDataypeName(root->sons[2]->data_type),
				root->lineNumber);
			
		if (root->type == ASTN_FUNCALL && isCallNotCompatible(root->sons[0],root->symbol->list))
			printf("A lista de argumentos chamada não confere com a declarada em %s na linha %i\n", root->symbol->value, root->lineNumber);
		
		if (root->type == ASTN_ASSIGNMENT && root->sons[1]->data_type != root->sons[0]->symbol->data_type)
			printf("Tipos diferentes na atribuicao %s na linha %i\n", root->sons[0]->symbol->value,root->sons[0]->lineNumber);
		
		
	}
}

CALL_LIST * revertParamList(CALL_LIST* list)
{
	CALL_LIST * new_list = NULL;

	while (list)
	{
		CALL_LIST * head = list;
		list = list->next;
		head->next = new_list;
		new_list = head;
	}

	return new_list;
}

void fetchTypeFromSons(ASTREE* node)
{
	switch (node->type)
	{
		case ASTN_SYMBOL_VAR:
			node->data_type = node->symbol->data_type;
			break;
		case ASTN_EXP_OP: case ASTN_SYMBOL_VEC:
			node->data_type = node->sons[0]->data_type;
			break;
		case ASTN_ASSIGNMENT:
			node->data_type = node->sons[1]->data_type;
			break;
	}
}

int isUsageNotComaptible(ASTREE* root)
{
	return (root->type == ASTN_SYMBOL_VAR && root->symbol->usage_type != SYMBOL_USAGE_TYPE_VARIABLE) || 
	(root->type == ASTN_SYMBOL_VEC && root->symbol->usage_type != SYMBOL_USAGE_TYPE_VECTOR) ||
	(root->type == ASTN_FUNCALL && root->symbol->usage_type != SYMBOL_USAGE_TYPE_FUNCTION);
}

int isCallNotCompatible(ASTREE* node, CALL_LIST* list) 
{
	if (list == NULL && node == NULL) return 0;
	if (list && node == NULL) return 1;
	if (list == NULL && node) return 1;
	if (node->sons[0] == NULL) return node->data_type != list->data_type;
	return (list->data_type != node->sons[1]->data_type) || isCallNotCompatible(node->sons[0],list->next);
}


void createParamList(ASTREE * node, ASTREE * son)
{
	if (son)
	{
		CALL_LIST * item = malloc(sizeof(CALL_LIST));
		item->data_type = son->sons[(son->sons[1])? 1 : 0]->data_type;
		item->next = node->symbol->list;
		node->symbol->list = item;
		if (son->sons[1])
			createParamList(node,son->sons[0]);
	}

}

char * getDataypeName(int dataType)
{
	switch (dataType)
	{
		case HASH_DATA_TYPE_STRING:
			return "string";
		case HASH_DATA_TYPE_INT:
			return "inteiro";
		case HASH_DATA_TYPE_FLOAT:
			return "float";
		case HASH_DATA_TYPE_BOOL:
			return "bool";
		case HASH_DATA_TYPE_CHAR:
			return "char";
		case HASH_DATA_TYPE_UNDEFINED:
			return "indefinido";
	}
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

int isOperationNotDefined(int dataType, int nodeType) 
{
	switch (dataType)
	{
		case HASH_DATA_TYPE_INT: case HASH_DATA_TYPE_FLOAT:
			return !(isOperationArithmetic(nodeType) || isOperationRelational(nodeType));
		case HASH_DATA_TYPE_BOOL:
			return !isOperationLogical(nodeType);
		case HASH_DATA_TYPE_CHAR: case HASH_DATA_TYPE_STRING:
			return 1;
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
	return (type  == ASTN_VAD) || (type == ASTN_VED) || (type == ASTN_HEADER) ;
}