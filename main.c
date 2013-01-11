#include "main.h"

int main(int argc, char **argv) {

	int i;
	if (argc >= 2) {
		initMe();

		display_symbol = 0;
		display_tac = 0;
		display_ast = 0;
		display_file = 0;

		for (i = 0; i < argc; ++i)
		{
			if (argv[i][0] == '-' && argv[i][1])
			{
				switch (argv[i][1])
				{
					case 's':
						display_symbol = 1;
						break;
					case 'a':
						display_ast = 1;
						break;
					case 't':
						display_tac = 1;
						break;
					case 'f':
						display_file =1;
						break;
				}
			}
		}



		if (argv[1])
		{

		    yyin= fopen(argv[1],"r");
			printf("Compiling %s...\n",argv[1]);
	#if YYDEBUG
		    yydebug = 1;
	#endif
		    yyparse();

		}
	    printf("%s%i%s","Build Finished! ",numberOfErrors," erro(s).\n");
	    exit(0);

	}
}