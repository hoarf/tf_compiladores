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

%left OPERATOR_LE  OPERATOR_GE  OPERATOR_EQ  OPERATOR_NE  OPERATOR_AND OPERATOR_OR '<' '>'
%left '-'  '+'
%left '*'  '/'


%%

program:					
							lista_declaracoes_globais funcoes 
							| funcoes 
							| lista_declaracoes_globais
							;
lista_declaracoes_globais:			
							lista_declaracoes_globais declaracao_global
							| declaracao_global
							;	

declaracao_global:
							TK_IDENTIFIER ':' tipo ';'
							| TK_IDENTIFIER ':' tipo '[' LIT_INTEGER ']' ';' 
							;		
tipo:						
							KW_INT
							| KW_FLOAT
							| KW_CHAR
							| KW_BOOL
							;
	
funcoes:	 			
							funcoes funcao
							| funcao
							;	
funcao: 					
							cabecalho lista_declaracoes bloco_de_comandos 
							| cabecalho bloco_de_comandos  
							;
cabecalho:					
							TK_IDENTIFIER ':' tipo '(' lista_de_parametros ')'
							| TK_IDENTIFIER ':' tipo '('  ')'
							;
lista_de_parametros:					
							lista_de_parametros ',' TK_IDENTIFIER ':' tipo
							| TK_IDENTIFIER ':' tipo
							;
lista_declaracoes: 		
							lista_declaracoes TK_IDENTIFIER ':' tipo ';'
							| TK_IDENTIFIER ':' tipo ';'
							;

bloco_de_comandos:		
							'{' comandos '}'  
							;
comandos:					
							comando ';' comandos
							| comando
							;
comando_vazio:				
							;
							
comando:					
							bloco_de_comandos
							| comando_simples
							| comando_vazio		
							; 
comando_simples:			
							 KW_IF '(' expressao ')' KW_THEN comando
							| KW_IF '(' expressao ')' KW_THEN comando KW_ELSE comando							
							| KW_WHILE '(' expressao ')' comando							
							| esquerda '=' expressao
							| input
							| output
							| return
							;
esquerda:					
							TK_IDENTIFIER 
							| TK_IDENTIFIER '[' expressao ']' 
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
							lista_de_elementos ',' elemento
							| elemento
							;
			
elemento:					
							LIT_STRING | expressao
							;
expressao:					
							expressao '+' expressao
							| expressao OPERATOR_LE expressao
							| expressao OPERATOR_GE expressao
							| expressao OPERATOR_EQ expressao
							| expressao OPERATOR_NE expressao
							| expressao OPERATOR_AND expressao
							| expressao OPERATOR_OR expressao
							| expressao '-' expressao
							| expressao '/' expressao
							| expressao '*' expressao
							| expressao '<' expressao
							| expressao '>' expressao
							| '(' expressao ')' 
							| LIT_INTEGER
							| TK_IDENTIFIER 
							| TK_IDENTIFIER '[' expressao ']'
							| LIT_FLOA  
							;

								
	
							
							
%%

int yyerror(char* s) {
	fprintf(stdout, "%s na linha %i\n", s,getLineNumber());
	exit(3);
}