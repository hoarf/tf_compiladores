#include "main.h"

/* uso: ./etapa1 nome_do_arquivo */
int main(int argc, char **argv) {
	int token;
	initMe();
	token = yylex();
	if (argc < 2) {
		yyin= fopen(argv[1],"r");

		while(running) {
			token = yylex();
			if ( running) {
			
				switch(token) {
					case TK_IDENTIFIER:
					insertNode(yytext, token);
					break;
					case LIT_INTEGER:
					insertNode(yytext, token);
					break;
					case KW_INT:
					break;
					case LIT_CHAR:
					insertNode(yytext, token);
					break;
					case LIT_STRING:
					insertNode(yytext, token);
					break;
					case LIT_FLOA:
					insertNode(yytext, token);
					break;
				}

			}

		}

		print();
	}
}
