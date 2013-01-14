#ifndef ASTREE_H_
#define ASTREE_H_

#include "m_hash.h"

#define TAC_POP				81
#define TAC_PUSH			80
#define TAC_STO				79
#define TAC_LOAD			77
#define TAC_GOTO			76
#define TAC_SYMBOL 			1
#define TAC_STRING			37
#define TAC_SYMBOL_TRUE 	36
#define TAC_SYMBOL_FALSE 	35
#define TAC_VAR_DEC			30
#define TAC_VECTOR_ACCES	32
#define TAC_IF 				34
#define TAC_VEC_DEC			33
#define TAC_ATTR 			4
#define TAC_LABEL 			5
#define TAC_WHILE	 		31
#define TAC_IFFALSE 		6
#define TAC_BEGINFUN 		7
#define TAC_ENDFUN 			8
#define TAC_ARG 			9
#define TAC_READVEC 		10
#define TAC_WRITEVEC 		11
#define TAC_CALL 			12
#define TAC_RETURN 			13
#define TAC_INPUT 			14
#define TAC_OUTPUT 			15
#define TAC_IF_GT	 		16
#define TAC_IF_GT	 		16
#define TAC_IF_LT	 		21
#define TAC_IF_NE	 		22
#define TAC_IF_EQ	 		23
#define TAC_IF_LE	 		24
#define TAC_IF_GE	 		25
#define TAC_MINUS			78
#define TAC_ 				20
#define TAC_IFZ				40

#define ASTN_ 			1
#define ASTN_VAD 		2
#define ASTN_PAR		20
#define ASTN_IT 		3
#define ASTN_FT 		4
#define ASTN_BT 		5
#define ASTN_CT 		6
#define ASTN_VED 		7
#define ASTN_IV 		80
#define ASTN_FV 		81
#define ASTN_CV 		82
#define ASTN_SV 		84
#define ASTN_BV 		85
#define ASTN_LIST 		9
#define ASTN_FUNCTION 	10
#define ASTN_HEADER 	11
#define ASTN_INPUT 		12
#define ASTN_OUTPUT 	13
#define ASTN_RETURN 	14
#define ASTN_ASSIGNMENT 15
#define ASTN_IF 		16
#define ASTN_IF_ELSE	98
#define ASTN_WHILE 		17
#define ASTN_FUNCALL 	20
#define ASTN_SYMBOL_VAR 19
#define ASTN_SYMBOL_VEC 33
#define ASTN_EXP_OP 	34
#define ASTN_EXP 		35
#define UMINUS 			99
#define ASTN_TRUE 		61
#define ASTN_FALSE		60
#define ASTN_RELOP		64
#define ASTN_BINOP		65
#define ASTN_BOO1L_BINOP 66


#define TAC_ADD			200
#define TAC_SUB			201
#define TAC_MUL			202
#define TAC_DIV			203
#define TAC_EQ			204
#define TAC_NE			205
#define TAC_GT			206
#define TAC_LT			207
#define TAC_GE			208
#define TAC_LE			209
#define TAC_OR			300
#define TAC_AND			301

#define ASTN_OP_ADD 	200
#define ASTN_OP_SUB 	201
#define ASTN_OP_MUL 	202
#define ASTN_OP_DIV 	203
#define ASTN_OP_EQ 		204
#define ASTN_OP_NE 		205
#define ASTN_OP_GT 		206
#define ASTN_OP_LT 		207
#define ASTN_OP_GE 		208
#define ASTN_OP_LE 		209
#define ASTN_OP_OR 		300
#define ASTN_OP_AND 	301


typedef struct _TAC TAC;


struct _TAC
{
	int type;
	HASH_NODE* res;
	HASH_NODE* op1;
	HASH_NODE* op2;
	int size;
	TAC* next;
}; 

typedef struct _ASTREE ASTREE;

struct _ASTREE 
{
	int type;
	ASTREE* sons[4];
	int data_type;
	int lineNumber;
	TAC* codigo;
	HASH_NODE * addr;
	HASH_NODE * symbol;
	HASH_NODE* true;
	HASH_NODE* false;
	HASH_NODE * next;

} ;

ASTREE * astree_create(int type, HASH_NODE* symbol,ASTREE* son1, ASTREE* son2, ASTREE* son3, ASTREE* son4);
ASTREE * astree_create_symbol(int type, HASH_NODE* symbol);
ASTREE * astree_create_default(int type, ASTREE * son1);
ASTREE * astree_create_basic(int type, HASH_NODE* symbol,ASTREE * son1);
ASTREE * astree_create_op(int type,ASTREE* son1, ASTREE* son2);
ASTREE * astree_create_empty(int type);

void astree_exibe(ASTREE* arvore, int level);
void astree_check_semantics(ASTREE * tree);
void astree_exibe_bottom_up(ASTREE* arvore, int level);
void astree_toFile(ASTREE* arvore,const char* filenName);


void genco(ASTREE* tree);
TAC* tac_create(int type, HASH_NODE* res, HASH_NODE* op1, HASH_NODE* op2);
TAC* tac_join(TAC* list1, TAC* list2);
void tac_print(ASTREE* tree);
const char * getTypeName(int type);

#endif /* ASTREE_H_ */
