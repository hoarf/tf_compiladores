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

%left OPERATOR_LE  OPERATOR_GE  OPERATOR_EQ  OPERATOR_NE  OPERATOR_AND OPERATOR_OR '<' '>'
%left '-'  '+'
%left '*'  '/'

//%left OPERADOR_AND OPERATOR_OR
//%nonassoc OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE '<' '>'

%%

program:
	lista_declaracoes_alto_nivel { $$ = create(AST_LDAN,0,$1,0,0,0); exibeASTREE($$,0); }
	| { exibeASTREE($$,0); }
	;

lista_declaracoes_alto_nivel:				
	lista_declaracoes_alto_nivel declaracao_alto_nivel { $$ = create(AST_LDAN,0,$1,$2,0,0); }
	| declaracao_alto_nivel { $$ = create(AST_DAN,0,$1,0,0,0); }
	;

declaracao_alto_nivel:							
	declaracao_global { $$ = create(AST_DG,0,$1,0,0,0); }
	| funcao ';' { $$ = create(AST_FUNCAO,0,$1,0,0,0); }
	;	
declaracao_global:
	TK_IDENTIFIER ':' tipo ';' { $$ = create(AST_GVARDEC,$1,$3,0,0,0); }
	| TK_IDENTIFIER ':' tipo '[' LIT_INTEGER ']' ';' { $$ = create(AST_GVECDEC,0,$1,$3,$5,0); } 
	;		
tipo:				
	KW_INT { $$ = create(AST_INT,0,0,0,0,0); }
	| KW_FLOAT { $$ = create(AST_FLOA,0,0,0,0,0); }
	| KW_CHAR { $$ = create(AST_CHAR,0,0,0,0,0); }
	| KW_BOOL { $$ = create(AST_BOOL,0,0,0,0,0); }
	;
funcao: 					
	cabecalho lista_declaracoes bloco_de_comandos { $$ = create(AST_CAB,0,$1,$2,$3,0); }
	| cabecalho bloco_de_comandos  { $$ = create(AST_CAB,0,$1,0,$2,0); }
	;
cabecalho:					
	TK_IDENTIFIER ':' tipo '(' lista_de_parametros ')' { $$ = create(AST_CAB,$1,$3,$5,0,0); }
	| TK_IDENTIFIER ':' tipo '('  ')' { $$ = create(AST_CAB,$1,$3,0,0,0); }
	;
lista_de_parametros:					
	lista_de_parametros ',' TK_IDENTIFIER ':' tipo { $$ = create(AST_LPAR,$3,$5,$1,0,0); }
	| TK_IDENTIFIER ':' tipo { $$ = create(AST_PAR,$1,$3,0,0,0); }
	;
lista_declaracoes: 		
	lista_declaracoes TK_IDENTIFIER ':' tipo ';' { $$ = create(AST_LDEC,$2,$4,$1,0,0); }
	| TK_IDENTIFIER ':' tipo ';' { $$ = create(AST_LDEC,$1,$3,0,0,0); }
	;
bloco_de_comandos:		
	'{' comandos '}' { $$ = create(AST_BCOM,0,$2,0,0,0); }
	;
comandos:
	lista_comandos { $$ = create(AST_COMS,0,$1,0,0,0); }
	| { $$ = 0; }
	; 
lista_comandos:					
	comando ';' lista_comandos { $$ = create(AST_LCOM,0,$1,$3,0,0); }
	| comando { $$ = create(AST_COM,0,$1,0,0,0); }
	;
comando_vazio:			
	{ $$ = create(AST_COMV,0,0,0,0,0); }	
	;							
comando:					
	bloco_de_comandos { $$ = create(AST_BCOM,0,$1,0,0,0); }
	| comando_simples { $$ = create(AST_COMS,0,$1,0,0,0); }
	| comando_vazio { $$ = create(AST_CV,0,0,0,0,0); }
	;
comando_simples:			
	KW_IF '(' expressao ')' KW_THEN comando { $$ = create(AST_IF,0,$3,$6,0,0); }
	| KW_IF '(' expressao ')' KW_THEN comando KW_ELSE comando { $$ = create(AST_IFEL,0,$3,$6,$8,0); }
	| KW_WHILE '(' expressao ')' comando { $$ = create(AST_WHILE,0,$3,$5,0,0); }
	| esquerda '=' expressao { $$ = create(AST_ATTRIB,0,$1,$3,0,0); }
	| input { $$ = create(AST_INPUT,0,$1,0,0,0); }
	| output { $$ = create(AST_OUTPUT,0,$1,0,0,0); }
	| return { $$ = create(AST_RETURN,0,$1,0,0,0); }
	;
esquerda:					
		TK_IDENTIFIER { $$ = create(AST_ESQVAR,$1,0,0,0,0); }
		| TK_IDENTIFIER '[' expressao ']' { $$ = create(AST_ESQVEC,$1,$3,0,0,0); }
		;
input:						
		KW_INPUT TK_IDENTIFIER { $$ = create(AST_INPUT,$2,0,0,0,0); }
		;
output:						
		KW_OUTPUT lista_de_elementos { $$ = create(AST_OUTPUT,0,$2,0,0,0); }
		;
return:						
		KW_RETURN expressao { $$ = create(AST_RETURN,0,$2,0,0,0); }
		;
lista_de_elementos:			
		lista_de_elementos ',' elemento { $$ = create(AST_LSTELEM,0,$1,$3,0,0); }
		| elemento { $$ = create(AST_ELEM,0,$1,0,0,0); }
		;
elemento:					
		LIT_STRING { $$ = create(AST_ELEM,$1,0,0,0,0); }
		| expressao { $$ = create(AST_ELEM,0,$1,0,0,0); }
		;
lista_expressoes:
		| expressoes { $$ = create(AST_LSTEXPRS,0,$1,0,0,0); }
		;
expressoes:
		expressoes ',' expressao { $$ = create(AST_EXPRS,0,0,0,0,0); }
		| expressao { $$ = create(AST_EXPR,0,$1,0,0,0); }
		;
expressao:					
		expressao '+' expressao { $$ = create(AST_ADD,0,0,0,0,0); }
		| expressao OPERATOR_LE expressao { $$ = create(AST_LE,0,$1,$3,0,0); }
		| expressao OPERATOR_GE expressao { $$ = create(AST_GE,0,$1,$3,0,0); }
		| expressao OPERATOR_EQ expressao { $$ = create(AST_EQ,0,$1,$3,0,0); }
		| expressao OPERATOR_NE expressao { $$ = create(AST_NE,0,$1,$3,0,0); }
		| expressao OPERATOR_AND expressao { $$ = create(AST_AND,0,$1,$3,0,0); }
		| expressao OPERATOR_OR expressao { $$ = create(AST_OR,0,$1,$3,0,0); }
		| expressao '-' expressao { $$ = create(AST_MINUS,0,$1,$3,0,0); }
		| expressao '/' expressao { $$ = create(AST_DIV,0,$1,$3,0,0); }
		| expressao '*' expressao { $$ = create(AST_MULT,0,$1,$3,0,0); }
		| expressao '<' expressao { $$ = create(AST_LT,0,$1,$3,0,0); }
		| expressao '>' expressao { $$ = create(AST_GT,0,$1,$3,0,0); }
		| '(' expressao ')' { $$ = create(AST_PAREXP,0,$2,0,0,0); }
		| TK_IDENTIFIER '(' lista_expressoes ')' { $$ = create(AST_CALL,$1,$3,0,0,0); }
		| TK_IDENTIFIER { $$ = create(AST_VAR,$1,0,0,0,0); }
		| TK_IDENTIFIER '[' expressao ']' { $$ = create(AST_VEC,$1,$3,0,0,0); }
		| LIT_INTEGER { $$ = create(AST_SYMBOL,$1,0,0,0,0); }
		| LIT_FLOA { $$ = create(AST_SYMBOL,$1,0,0,0,0); }
		| LIT_TRUE { $$ = create(AST_SYMBOL,$1,0,0,0,0); }
		| LIT_FALSE { $$ = create(AST_SYMBOL,$1,0,0,0,0); }
		| LIT_CHAR { $$ = create(AST_SYMBOL,$1,0,0,0,0); }
		| LIT_STRING { $$ = create(AST_SYMBOL,$1,0,0,0,0); }
		;

%%

int yyerror(char* s) {
	fprintf(stdout, "%s na linha %i\n", s,getLineNumber());
	exit(3);
}
