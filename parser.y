%{

#include <stdio.h>
#include <stdlib.h>
#define YYDEBUG 1

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

program:					
							declaracoes_globais funcoes
							;
declaracoes_globais:
							declaracao_global declaracoes_globais
							|
							;	
declaracao_global:
							declaracao_variavel ';'	
							| TK_IDENTIFIER ':'	tipo'['LIT_INTEGER']'';'
							;	
declaracao_variavel:		
							TK_IDENTIFIER ':' tipo 
							;		
tipo:						
							KW_INT
							| KW_FLOAT
							| KW_CHAR
							| KW_BOOL
							;		
funcoes:		 			
							funcoes funcao
							|
							;	
funcao: 					
							cabecalho declaracoes_locais bloco_de_comandos	
							;	
cabecalho:					
							TK_IDENTIFIER ':' tipo '(' lista_de_parametros ')'
							;
lista_de_parametros: 		
							| parametros
							;
parametros:					
							parametros , declaracao_variavel
							| declaracao_variavel
							;
declaracoes_locais: 		
							declaracoes_locais declaracao_variavel ';'
							|
							;

bloco_de_comandos:			
							'{' comandos '}' 
							| comando
							;
comandos:					
							comando ';' comandos
							| 
							;
comando:					
							bloco_de_comandos
							| atribuicao 
							| controle_fluxo 
							| input
							| output
							| return
							|					
							;
atribuicao:					
							TK_IDENTIFIER '=' expressao
							| TK_IDENTIFIER'[' expressao ']' '=' expressao
							;
input:						
							KW_INPUT TK_IDENTIFIER
							;
output:						
							KW_OUTPUT lista_de_elementos
							;
return:						
							KW_RETURN expressao
							;
lista_de_elementos:			
							elemento , resto_elementos
							;
resto_elementos:			
							elemento , lista_de_elementos | elemento
							;					
elemento:					
							LIT_STRING | expressao
							;
expressao:					
							expressao operador expressao
							| '(' expressao ')' 
							| TK_IDENTIFIER
							| TK_IDENTIFIER '[' expressao ']' 
							| LIT_INTEGER
							| LIT_FLOA  
							;
controle_fluxo:				
							KW_IF '('expressao')' KW_THEN comando else_opcional
							| KW_WHILE '('expressao')' comando
							;
else_opcional:				
							KW_ELSE comando
							| comando
							;							
							
operador:				 	
							OPERATOR_LE
							| OPERATOR_GE
							| OPERATOR_EQ
							| OPERATOR_NE
							| OPERATOR_AND
							| OPERATOR_OR
							;
							
							
%%

int yyerror(char* s) {
	fprintf(stdout, "%s na linha %i\n", s,getLineNumber());
	exit(0);
}