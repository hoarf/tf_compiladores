#include "astree.h"
#include <stdio.h>

#define TAB = 0x9;

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

const char * selecionaMensagemPorTipo(int tipo) {
	switch (tipo) {
	case AST_SYMBOL:
		return "AST_SYMBOL";
	case AST_PROGRAM:
		return "AST_PROGRAM";
	case AST_LDAN:
		return "AST_LDAN";
	case AST_DAN:
		return "AST_DAN";
	case AST_DG:
		return "AST_DG";
	case AST_TIPO:
		return "AST_TIPO";
	case AST_FUNCAO:
		return "AST_FUNCAO";
	case AST_CAB:
		return "AST_CAB";
	case AST_LPAR:
		return "AST_LPAR";
	case AST_PAR:
		return "AST_PAR";
	case AST_LDEC:
		return "AST_LDEC";
	case AST_BCOM:
		return "AST_BCOM";
	case AST_LCOM:
		return "AST_LCOM";
	case AST_COMV:
		return "AST_COMV";
	case AST_COMS:
		return "AST_COMS";
	case AST_ESQ:
		return "AST_ESQ";
	case AST_LSTELEM:
		return "AST_LSTELEM";
	case AST_ELEM:
		return "AST_ELEM";
	case AST_GVARDEC:
		return "AST_GVARDEC";
	case AST_GVECDEC:
		return "AST_GVECDEC";
	case AST_ADD:
		return "AST_ADD";
	case AST_SUB:
		return "AST_SUB";
	case AST_MUL:
		return "AST_MUL";
	case AST_DIV:
		return "AST_DIV";
	case AST_INT:
		return "AST_INT";
	case AST_FLOA:
		return "AST_FLOA";
	case AST_CHAR:
		return "AST_CHAR";
	case AST_BOOL:
		return "AST_BOOL";
	case AST_IF:
		return "AST_IF";
	case AST_IFEL:
		return "AST_IFEL";
	case AST_WHILE:
		return "AST_WHILE";
	case AST_ATTRIB:
		return "AST_ATTRIB";
	case AST_ESQVAR:
		return "AST_ESQVAR";
	case AST_ESQVEC:
		return "AST_ESQVEC";
	case AST_CALL:
		return "AST_CALL";
	case AST_VAR:
		return "AST_VAR";
	case AST_VEC:
		return "AST_VEC";
	case AST_LSTEXPR:
		return "AST_LSTEXPR";
	case AST_EXPRS:
		return "AST_EXPRS";
	case AST_EXPR:
		return "AST_EXPR";
	default:
		return "????";
	}
}

const char * getNodeString(int tipo) {
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
	case AST_LCOM:
		return "13";
	case AST_COMV:
		return "14";
	case AST_COMS:
		return "16";
	case AST_ESQ:
		return "17";
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
	default:
		return "????";
	}
}

char * insereTabulacao(int level) {
	if (level != 0) {
		int i;
		char * ret = calloc(level-1,sizeof(char));
		for (i = 0; i < level; ++i) {
			ret[i] = 0x9;
		}
		return ret;
	} else {
		return "";
	}
}

void imprimeNodo(ASTREE* arvore,FILE * file) {
	//puts(getNodeString(arvore->type));
	int i;
	for (i = 0; i < 4; ++i) {
		imprimeNodo(arvore->sons[i],file);
	}
}

void astree_toFile(ASTREE*arvore, const char* filenName) {
	FILE * fp = fopen( filenName,  "w" );
	//imprimeNodo(arvore,fp);
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
