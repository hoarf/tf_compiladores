%{
	#include "m_hash.h"
	#include "y.tab.h"
	#include "scanner.h"
	#include "astree.h"
%}



%x COMENTARIO

%%

int					{ return KW_INT; }
float				{ return KW_FLOAT; }
bool				{ return KW_BOOL; }
char				{ return KW_CHAR; }
if					{ return KW_IF; }
then				{ return KW_THEN; }
else				{ return KW_ELSE; }
while				{ return KW_WHILE; }
do					{ return KW_DO; }
input				{ return KW_INPUT; }
return				{ return KW_RETURN; }
output				{ return KW_OUTPUT; }

"<="				{ return OPERATOR_LE; }
">="				{ return OPERATOR_GE; }
"=="				{ return OPERATOR_EQ; }
"!="				{ return OPERATOR_NE; }
"&&"				{ return OPERATOR_AND; }
"||"				{ return OPERATOR_OR; }

false	 			{ return LIT_FALSE; }
true 				{ return LIT_TRUE; }

L?\"(\\.|[^\\"])*\"		{ trimQuotes(yytext) ; create(AST_SYMBOL, insertNode(yytext,SYMBOL_LIT_STRING), NULL, NULL, NULL, NULL) ; return LIT_STRING; }
[a-zA-Z][_a-zA-Z0-9]* 	{ create(AST_SYMBOL, insertNode(yytext,SYMBOL_IDENTIFIER),NULL,NULL,NULL,NULL) ; return TK_IDENTIFIER; }
[-]?[0-9]*"."[0-9]+ 	{ create(AST_SYMBOL,insertNode(yytext,SYMBOL_LIT_FLOATING),NULL,NULL,NULL,NULL) ; return LIT_FLOA; }
[-]?[0-9]+ 				{ create(AST_SYMBOL,insertNode(yytext,SYMBOL_LIT_INTEGER),NULL,NULL,NULL,NULL) ; return LIT_INTEGER; }
"'"[a-zA-Z]"'" 			{ char valorChar = yytext[1] ; create(AST_SYMBOL,insertNode(&valorChar,SYMBOL_LIT_CHAR),NULL,NULL,NULL,NULL) ; return LIT_CHAR; }

[ \t]				{}
\n					{ ++lineNumber; }

"/*"   			 	BEGIN(COMENTARIO);
<COMENTARIO>"*/"    BEGIN(0);
<COMENTARIO>.		{}
<COMENTARIO>"\n"	{ ++lineNumber;}

"//".*				{}
","|";"|":"|"("|")"|"["|"]"|"{"|"}"|"+"|"-"|"*"|"/"|"<"|">"|"="|"!"|"&"|"$" { return yytext[0]; }

. 					{ return TOKEN_ERROR; }

%%

int lineNumber = 1;
int getLineNumber(void) { return lineNumber; }

int yywrap(void) {
	return 1;
}


void trimQuotes(char * source) {
	int i;
	for (i =0 ; i < strlen(source)-2; ++i) 
		source[i] = source[i+1];
	
	source[strlen(source)-2] = '\0';
}
