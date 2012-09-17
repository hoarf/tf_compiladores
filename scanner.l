%{
	#include "tokens.h"
	#include "m_hash.h"
	#include "scanner.h"
%}
%%

. {}

%%

int getLineNumber(void) { return lineNumber; }

int yywrap(void) {
	running = 0;
	return 1;
}


