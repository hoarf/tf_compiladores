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

				//*switch

			}

		}

		print();
	}
}
