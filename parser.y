%{

#include <stdio.h>
#include <stdlib.h>
#include "astree.h"
#include "scanner.h"
#define YYDEBUG 1

int yylex(void);
int yyerror(char *);

%}

%union {
	 HASH_NODE * symbol;
	 struct _ASTREE * ast;
}

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

%token <symbol>TK_IDENTIFIER
%token <symbol>LIT_INTEGER
%token <symbol>LIT_FLOA
%token <symbol>LIT_FALSE
%token <symbol>LIT_TRUE
%token <symbol>LIT_CHAR
%token <symbol>LIT_STRING

%token TOKEN_ERROR

%type <ast>program
%type <ast>lista_declaracoes_alto_nivel
%type <ast>declaracao_alto_nivel
%type <ast>declaracao_global
%type <ast>tipo
%type <ast>funcao
%type <ast>cabecalho
%type <ast>lista_de_parametros
%type <ast>lista_declaracoes
%type <ast>bloco_de_comandos
%type <ast>comandos
%type <ast>lista_comandos
%type <ast>comando_vazio
%type <ast>comando
%type <ast>comando_simples
%type <ast>esquerda
%type <ast>input
%type <ast>output
%type <ast>return
%type <ast>lista_de_elementos
%type <ast>elemento
%type <ast>expressao
%type <ast>lista_expressoes
%type <ast>expressoes
%type <ast>tipo_cont

%left OPERATOR_LE  OPERATOR_GE  OPERATOR_EQ  OPERATOR_NE  OPERATOR_AND OPERATOR_OR '<' '>'
%left '-'  '+'
%left '*'  '/'

%%

program:
	lista_declaracoes_alto_nivel { 
	  $$ = astree_create(AST_PROGRAM,0,$1,0,0,0); 
	  astree_exibe($$,0); 
	  astree_toFile($$,"tmp1.tmp");
	}
	
	| { $$ = 0;}
	;

lista_declaracoes_alto_nivel:
	lista_declaracoes_alto_nivel declaracao_alto_nivel { $$ = astree_create(AST_LDAN,0,$1,$2,0,0); }
	| declaracao_alto_nivel 
	;

declaracao_alto_nivel:
	declaracao_global 
	| funcao ';' 
	;	
declaracao_global:
	TK_IDENTIFIER ':' tipo ';' { $$ = astree_create(AST_GVARDEC,$1,$3,0,0,0); }
	| TK_IDENTIFIER ':' tipo '[' tipo_cont ']' ';' { $$ = astree_create(AST_GVECDEC,$1,$3,$5,0,0); } 
	;
	
tipo_cont:
	LIT_INTEGER { $$ = astree_create(AST_INT,$1,0,0,0,0); } 
	;

tipo:
	KW_INT { $$ = astree_create(AST_INT,0,0,0,0,0); }
	| KW_FLOAT { $$ = astree_create(AST_FLOA,0,0,0,0,0); }
	| KW_CHAR { $$ = astree_create(AST_CHAR,0,0,0,0,0); }
	| KW_BOOL { $$ = astree_create(AST_BOOL,0,0,0,0,0); }
	;
funcao:
	cabecalho lista_declaracoes bloco_de_comandos { $$ = astree_create(AST_CAB,0,$1,$2,$3,0); }
	| cabecalho bloco_de_comandos  { $$ = astree_create(AST_CAB,0,$1,$2,0,0); }
	;
cabecalho:					
	TK_IDENTIFIER ':' tipo '(' lista_de_parametros ')' { $$ = astree_create(AST_CAB,$1,$3,$5,0,0); }
	| TK_IDENTIFIER ':' tipo '('  ')' { $$ = astree_create(AST_CAB,$1,$3,0,0,0); }
	;
lista_de_parametros:					
	lista_de_parametros ',' TK_IDENTIFIER ':' tipo { $$ = astree_create(AST_LPAR,$3,$5,$1,0,0); }
	| TK_IDENTIFIER ':' tipo { $$ = astree_create(AST_PAR,$1,$3,0,0,0); }
	;
lista_declaracoes: 		
	lista_declaracoes TK_IDENTIFIER ':' tipo ';' { $$ = astree_create(AST_LDEC,$2,$4,$1,0,0); }
	| TK_IDENTIFIER ':' tipo ';' { $$ = astree_create(AST_LDEC,$1,$3,0,0,0); }
	;
bloco_de_comandos:		
	'{' comandos '}' { $$ = astree_create(AST_BCOM,0,$2,0,0,0); }
	;
comandos:
	lista_comandos 
	| { $$ = 0; }
	; 
lista_comandos:					
	comando ';' lista_comandos { $$ = astree_create(AST_LCOM,0,$1,$3,0,0); }
	| comando 
	;
comando_vazio:			
	{ $$ = astree_create(AST_COMV,0,0,0,0,0); }	
	;							
comando:					
	bloco_de_comandos 
	| comando_simples 
	| comando_vazio { $$ = astree_create(AST_CV,0,0,0,0,0); }
	;
comando_simples:			
	KW_IF '(' expressao ')' KW_THEN comando { $$ = astree_create(AST_IF,0,$3,$6,0,0); }
	| KW_IF '(' expressao ')' KW_THEN comando KW_ELSE comando { $$ = astree_create(AST_IFEL,0,$3,$6,$8,0); }
	| KW_WHILE '(' expressao ')' comando { $$ = astree_create(AST_WHILE,0,$3,$5,0,0); }
	| esquerda '=' expressao { $$ = astree_create(AST_ATTRIB,0,$1,$3,0,0); }
	| input 
	| output 
	| return 
	;
esquerda:					
		TK_IDENTIFIER { $$ = astree_create(AST_ESQVAR,$1,0,0,0,0); }
		| TK_IDENTIFIER '[' expressao ']' { $$ = astree_create(AST_ESQVEC,$1,$3,0,0,0); }
		;
input:						
		KW_INPUT TK_IDENTIFIER { $$ = astree_create(AST_INPUT,$2,0,0,0,0); }
		;
output:						
		KW_OUTPUT lista_de_elementos { $$ = astree_create(AST_OUTPUT,0,$2,0,0,0); }
		;
return:						
		KW_RETURN expressao { $$ = astree_create(AST_RETURN,0,$2,0,0,0); }
		;
lista_de_elementos:			
		lista_de_elementos ',' elemento { $$ = astree_create(AST_LSTELEM,0,$1,$3,0,0); }
		| elemento 
		;
elemento:					
		LIT_STRING { $$ = astree_create(AST_ELEM,$1,0,0,0,0); }
		| expressao 
		;
lista_expressoes: { $$ = 0; }
		| expressoes 
		;
expressoes:
		expressoes ',' expressao { $$ = astree_create(AST_EXPRS,0,0,0,0,0); }
		| expressao 
		;
expressao:					
		expressao '+' expressao { $$ = astree_create(AST_ADD,0,0,0,0,0); }
		| expressao OPERATOR_LE expressao { $$ = astree_create(AST_LE,0,$1,$3,0,0); }
		| expressao OPERATOR_GE expressao { $$ = astree_create(AST_GE,0,$1,$3,0,0); }
		| expressao OPERATOR_EQ expressao { $$ = astree_create(AST_EQ,0,$1,$3,0,0); }
		| expressao OPERATOR_NE expressao { $$ = astree_create(AST_NE,0,$1,$3,0,0); }
		| expressao OPERATOR_AND expressao { $$ = astree_create(AST_AND,0,$1,$3,0,0); }
		| expressao OPERATOR_OR expressao { $$ = astree_create(AST_OR,0,$1,$3,0,0); }
		| expressao '-' expressao { $$ = astree_create(AST_MINUS,0,$1,$3,0,0); }
		| expressao '/' expressao { $$ = astree_create(AST_DIV,0,$1,$3,0,0); }
		| expressao '*' expressao { $$ = astree_create(AST_MULT,0,$1,$3,0,0); }
		| expressao '<' expressao { $$ = astree_create(AST_LT,0,$1,$3,0,0); }
		| expressao '>' expressao { $$ = astree_create(AST_GT,0,$1,$3,0,0); }
		| '(' expressao ')' { $$ = astree_create(AST_PAREXP,0,$2,0,0,0); }
		| TK_IDENTIFIER '(' lista_expressoes ')' { $$ = astree_create(AST_CALL,$1,$3,0,0,0); }
		| TK_IDENTIFIER { $$ = astree_create(AST_VAR,$1,0,0,0,0); }
		| TK_IDENTIFIER '[' expressao ']' { $$ = astree_create(AST_VEC,$1,$3,0,0,0); }
		| LIT_INTEGER { $$ = astree_create(AST_SYMBOL,$1,0,0,0,0); }
		| LIT_FLOA { $$ = astree_create(AST_SYMBOL,$1,0,0,0,0); }
		| LIT_TRUE { $$ = astree_create(AST_SYMBOL,$1,0,0,0,0); }
		| LIT_FALSE { $$ = astree_create(AST_SYMBOL,$1,0,0,0,0); }
		| LIT_CHAR { $$ = astree_create(AST_SYMBOL,$1,0,0,0,0); }
		| LIT_STRING { $$ = astree_create(AST_SYMBOL,$1,0,0,0,0); }
		;

%%

int yyerror(char* s) {
	fprintf(stdout, "%s na linha %i\n", s,getLineNumber());
	exit(3);
}
