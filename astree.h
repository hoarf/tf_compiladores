#ifndef ASTREE_H_
#define ASTREE_H_

#include "m_hash.h"


#define AST_SYMBOL 			0
#define AST_PROGRAM 		1
#define AST_LDAN 			2
#define AST_DAN 			3
#define AST_DG	 			4
#define AST_TIPO			5
#define AST_FUNCAO			6
#define AST_CAB				7
#define AST_LPAR			8
#define AST_PAR				9
#define AST_LDEC			10
#define AST_BCOM			11
#define AST_COM				12
#define AST_LCOM			13
#define AST_COMV			14
#define AST_COMS			16
#define AST_ESQ				17
#define AST_INPUT			18
#define AST_OUTPUT			19
#define AST_RETURN			20
#define AST_LSTELEM 		21
#define AST_ELEM 			22
#define AST_GVARDEC 		23
#define AST_GVECDEC 		24
#define AST_ADD 			25
#define AST_SUB 			26
#define AST_MUL 			27
#define AST_DIV 			28
#define AST_INT 			29
#define AST_FLOA 			30
#define AST_CHAR 			31
#define AST_BOOL 			32
#define AST_IF				33
#define AST_IFEL			34
#define AST_WHILE			35
#define AST_ATTRIB			36
#define AST_ESQVAR			40
#define AST_ESQVEC			41
#define AST_CALL			42
#define AST_VAR				43
#define AST_VEC				44
#define AST_LSTEXPR 		45
#define AST_EXPRS 			46
#define AST_EXPR 			47

// ?????
#define AST_CV 				50
#define AST_LSTEXPRS		51
#define AST_LE				52
#define AST_GE		 		53
#define AST_EQ	 			54
#define AST_NE	 			55
#define AST_AND				56
#define AST_OR				57
#define AST_MINUS	 		58
#define AST_MULT 			59
#define AST_LT	 			60
#define AST_PAREXP			61
#define AST_GT				62

typedef struct _ASTREE ASTREE;

struct _ASTREE {
	int type;
	ASTREE* sons[4];
	HASH_NODE * symbol;

} ;

ASTREE* ast;

ASTREE * astree_create(int type, HASH_NODE* symbol,ASTREE* son1, ASTREE* son2, ASTREE* son3, ASTREE* son4);

void astree_exibe(ASTREE* arvore, int level);

#endif /* ASTREE_H_ */
