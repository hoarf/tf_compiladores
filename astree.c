#include "astree.h";
#include <stdio.h>;

#define TAB = 0x9;

ASTREE * create(int type, HASH_NODE* symbol,ASTREE* son1, ASTREE* son2, ASTREE* son3, ASTREE* son4) {
	ASTREE* ast = malloc(sizeof(ASTREE));
	ast->symbol = symbol;
	ast->type = type;
	ast->son1 = son1;
	ast->son2 = son2;
	ast->son3 = son3;
	ast->son4 = son4;
	return ast;
}

void exibeASTREE(ASTREE* arvore, int level) {
	if (arvore != NULL) {
		printf("%s%s",insereTabulacao(level),selecionaMensagemPorTipo(arvore->type));
		exibeASTREE(arvore->son1, ++level);
		exibeASTREE(arvore->son2, ++level);
		exibeASTREE(arvore->son3, ++level);
		exibeASTREE(arvore->son4, ++level);
	}
}

char * insereTabulacao(int level) {
	if (level != 0) {
		int i;
		char ret[level-1];
		for (i = 0; i < level; ++i) {
			ret[i] = 0x9;
		}
		return ret;
	} else {
		return "";
	}
}

char * selecionaMensagemPorTipo(int tipo) {
	switch (tipo) {
	case AST_SYMBOL:
		return "0";
	case AST_PROGRAM:
		return "1";
	case AST_LDAN:
		return "2";
	case AST_DAN:
		return "3";
	case AST_DG:
		return "4";
	case AST_TIPO:
		return "5";
	case AST_FUNCAO:
		return "6";
	case AST_CAB:
		return "7";
	case AST_LPAR:
		return "8";
	case AST_PAR:
		return "9";
	case AST_LDEC:
		return "10";
	case AST_BCOM:
		return "11";
	case AST_COM:
		return "12";
	case AST_LCOM:
		return "13";
	case AST_COMV:
		return "14";
	case AST_COM:
		return "15";
	case AST_COMS:
		return "16";
	case AST_ESQ:
		return "17";
	case AST_INPUT:
		return "18";
	case AST_OUTPUT:
		return "19";
	case AST_RETURN:
		return "20";
	case AST_LSTELEM:
		return "21";
	case AST_ELEM:
		return "22";
	case AST_GVARDEC:
		return "23";
	case AST_GVECDEC:
		return "24";
	case AST_ADD:
		return "25";
	case AST_SUB:
		return "26";
	case AST_MUL:
		return "27";
	case AST_DIV:
		return "28";
	case AST_INT:
		return "29";
	case AST_FLOA:
		return "30";
	case AST_CHAR:
		return "31";
	case AST_BOOL:
		return "32";
	case AST_IF:
		return "33";
	case AST_IFEL:
		return "34";
	case AST_WHILE:
		return "35";
	case AST_ATTRIB:
		return "36";
	case AST_INPUT:
		return "37";
	case AST_OUTPUT:
		return "38";
	case AST_RETURN:
		return "39";
	case AST_ESQVAR:
		return "40";
	case AST_ESQVEC:
		return "41";
	case AST_CALL:
		return "42";
	case AST_VAR:
		return "43";
	case AST_VEC:
		return "44";
	case AST_LSTEXPR:
		return "45";
	case AST_EXPRS:
		return "46";
	case AST_EXPR:
		return "47";
	}
}
