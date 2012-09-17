%{
	#include "tokens.h"
	#include "m_hash.h"
	#include "scanner.h"
%}
%%

","|";"|":"|"("|")"|"["|"]"|"{"|"}"|"+"|"-"|"*"|"/"|"<"|">"|"="|"!"|"&"|"$" { return yytext[0]; }

%%

int yywrap(void) {
	running = 0;
	return 1;
}


