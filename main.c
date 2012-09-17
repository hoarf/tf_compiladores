#include "main.h"

/* uso: ./etapa1 nome_do_arquivo */
int main(int argc, char **argv) {
	printf("Compiling %s...",argv[1]);
	if (argc >= 2) {
		int token;
		initMe();
	    yyin= fopen(argv[1],"r");
		while(running) {
			token = yylex();
			if ( running) {
					switch(token) {
					case TK_IDENTIFIER:
						printf("Linha: %i Identificador: %s\n",getLineNumber(),yytext);
					break;
					case LIT_INTEGER:
						printf("Linha: %i Inteiro: %i\n",getLineNumber(),atoi(yytext));
					break;
					case LIT_CHAR:
						printf("Linha: %i CHAR: %c\n",getLineNumber(),yytext[0]);
					break;
					case LIT_STRING:
						printf("Linha: %i STRING: %s\n",getLineNumber(),yytext);
					break;
					}
			}
		}
		print();
	}
	printf("","Done.");
	exit(1);
}
