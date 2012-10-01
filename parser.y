%{

#include <stdio.h>
#include <stdlib.h>

%}

%token KW_INT
%token KW_FLOAT
%token KW_BOOL
%token KW_CHAR
%token KW_IF
%token KW_THEN
%token KW_ELSE
%token KW_WHILE
%token KW_DO
%token KW_INPUT
%token KW_RETURN
%token KW_OUTPUT

%token OPERATOR_LE
%token OPERATOR_GE
%token OPERATOR_EQ
%token OPERATOR_NE
%token OPERATOR_AND
%token OPERATOR_OR

%token TK_IDENTIFIER
%token LIT_INTEGER
%token LIT_FLOA
%token LIT_FALSE
%token LIT_TRUE
%token LIT_CHAR
%token LIT_STRING

%token TOKEN_ERROR


%%

program:					declaracoes_globais funcoes
		;
declaracoes_globais:		declaracao_global resto_declaracoes
		;	
resto_declaracoes:			declaracao_global
		| 
		;
declaracao_global: 			TK_IDENTIFIER ':' tipo ;
		|					tipo '[' LIT_INTEGER ']' ;
		;
tipo:						KW_INT | KW_FLOAT | KW_CHAR | KW_BOOL
		;		
funcoes:		 			funcao 	resto_funcoes
		;	
resto_funcoes:				funcao
		|
		;
funcao: 					cabecalho declaracoes_locais corpo	
		;
cabecalho:					TK_IDENTIFIER ':' tipo '(' lista_de_parametros ')'
		;	
lista_de_parametros: 		parametro ',' parametro | parametro | 
		;
parametro:					TK_IDENTIFIER ':' tipo
		;
declaracoes_locais: 
		;

%%

int yyerror(char* s) {
	fprintf(stdout, "%s\n", s);
	exit(0);
}