%{
	#include "tokens.h"
	#include "m_hash.h"
	#include "scanner.h"
%}
%%

. {}

%%

int yywrap(void) {
	running = 0;
	return 1;
}


