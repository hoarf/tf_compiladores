#include "main.h"

int main(int argc, char **argv) {

	printf("Compiling %s...\n",argv[1]);
	if (argc >= 2) {
		initMe();
	    yyin= fopen(argv[1],"r");
#if YYDEBUG
	    yydebug = 1;
#endif
	    yyparse();
	    printf("%s","Success! \n");
	    exit(3);

	}
}
