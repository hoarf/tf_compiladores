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
%type <ast>high_lvl_statements
%type <ast>high_lvl_statement
%type <ast>global_var_dec
%type <ast>tipo
%type <ast>function
%type <ast>cabecalho
%type <ast>lista_de_parametros
%type <ast>lista_declaracoes
%type <ast>comandos
%type <ast>comando
%type <ast>esquerda
%type <ast>lista_de_elementos
%type <ast>elemento
%type <ast>expressao
%type <ast>expressoes
%type <ast>tipo_cont
%type <ast>command_archetype
%type <ast>command_block

%left OPERATOR_LE  OPERATOR_GE  OPERATOR_EQ  OPERATOR_NE  OPERATOR_AND OPERATOR_OR '<' '>'
%left '-'  '+'
%left '*'  '/'

%%

program:
	high_lvl_statements 	{  astree_exibe_botton_up($$,0); }// astree_toFile($$,"tmp1.tmp");	}
	| { $$ = 0 ;}
	;

high_lvl_statements:
	high_lvl_statements high_lvl_statement { $$ = astree_create(ASTN_LIST, NULL, $1, $2, NULL, NULL); }
	| high_lvl_statement 
	;

high_lvl_statement: 
	global_var_dec ';' 
	| function ';' 
	;

global_var_dec:
	TK_IDENTIFIER ':' tipo  { $$ =  astree_create_basic(ASTN_VAD, $1, $3); }
	| TK_IDENTIFIER ':' tipo '[' tipo_cont ']'  { $$ = astree_create(ASTN_VED, $1, $3, $5,NULL, NULL); }
	;
	
tipo_cont:
	LIT_INTEGER { $$ =  astree_create_symbol(ASTN_IV, $1); }
	;

tipo:
	KW_INT { $$ =  astree_create_empty(ASTN_IT); }
	| KW_FLOAT { $$ =  astree_create_empty(ASTN_FT); }
	| KW_CHAR { $$ =  astree_create_empty(ASTN_CT); }
	| KW_BOOL { $$ =  astree_create_empty(ASTN_BT); }
	;

function:
	cabecalho lista_declaracoes command_block { $$ = astree_create(ASTN_FUNCTION, NULL, $1, $2, $3, NULL); }
	;

cabecalho:					
	TK_IDENTIFIER ':' tipo '(' lista_de_parametros ')' { $$ = astree_create(ASTN_HEADER, $1 ,$3 ,$5, NULL, NULL); }
	;

lista_de_parametros:					
	lista_de_parametros ',' TK_IDENTIFIER ':' tipo { $$ = astree_create(ASTN_LIST, $3, $1 , $5 , NULL, NULL); }
	| TK_IDENTIFIER ':' tipo { $$ = astree_create_basic(ASTN_VAD, $1, $3); }
	| {$$ = 0; }
	;

lista_declaracoes: 		
	lista_declaracoes TK_IDENTIFIER ':' tipo ';' { $$ = astree_create(ASTN_LIST, $2, $1 , $4 , NULL, NULL); }
	| TK_IDENTIFIER ':' tipo ';' { $$ = astree_create_basic(ASTN_VAD, $1, $3); }
	| {$$ = 0; }
	;

comandos:
    | command_archetype ';' comandos  { $$ =  astree_create(ASTN_LIST, NULL, $1,$3,NULL,NULL); }
	| command_archetype
	; 

command_archetype:
	| command_block
	| comando
    | { $$ = 0;}
    ;
command_block:
	'{' comandos '}' { $$ =  astree_create_default(ASTN_LIST, $2); }
	;

comando:			
	KW_IF '(' expressao ')' KW_THEN comando {$$= astree_create(ASTN_IF,NULL,$3,$6,NULL,NULL);}
	| KW_IF '(' expressao ')' KW_THEN comando KW_ELSE comando {$$= astree_create(ASTN_IF,NULL,$3,$6,$8,NULL);}
	| KW_WHILE '(' expressao ')' comando {$$= astree_create(ASTN_WHILE,NULL,$3,$5,NULL,NULL);}
	| esquerda '=' expressao { $$= astree_create(ASTN_ASSIGNMENT,NULL,$1,$3,NULL,NULL);}
	| KW_INPUT TK_IDENTIFIER { $$= astree_create_symbol(ASTN_INPUT,$2); }
	| KW_OUTPUT lista_de_elementos { $$= astree_create_default(ASTN_OUTPUT,$2);}
	| KW_RETURN expressao {$$= astree_create_default(ASTN_RETURN,$2);}
	;

esquerda:					
	TK_IDENTIFIER { $$ =  astree_create_symbol(ASTN_, $1); }
	| TK_IDENTIFIER '[' expressao ']' { $$ =  astree_create_symbol(ASTN_, $1); }
	;

lista_de_elementos:	
	lista_de_elementos ',' elemento { $$ =  astree_create_default(ASTN_, $1); }
	| elemento { $$ =  astree_create_default(ASTN_, $1); }
	;

elemento:					
	LIT_STRING { $$ =  astree_create_symbol(ASTN_, $1); }
	| expressao { $$ =  astree_create_default(ASTN_, $1); }
	;

expressoes:
	expressoes ',' expressao { $$ =  astree_create_default(ASTN_, $1); }
	| expressao { $$ =  astree_create_default(ASTN_, $1); }
	;

expressao:
	expressao op expressao 					
	| '(' expressao ')' 
	| TK_IDENTIFIER '(' expressoes ')' { $$ =  astree_create_symbol(ASTN_, $1); }
	| TK_IDENTIFIER { $$ =  astree_create_symbol(ASTN_, $1); }
	| TK_IDENTIFIER '[' expressao ']' { $$ =  astree_create_symbol(ASTN_, $1); }
	| LIT_INTEGER { $$ =  astree_create_symbol(ASTN_, $1); }
	| LIT_FLOA { $$ =  astree_create_symbol(ASTN_, $1); }
	| LIT_TRUE { $$ =  astree_create_symbol(ASTN_, $1); }
	| LIT_FALSE { $$ =  astree_create_symbol(ASTN_, $1); }
	| LIT_CHAR { $$ =  astree_create_symbol(ASTN_, $1); }
	| LIT_STRING { $$ =  astree_create_symbol(ASTN_, $1); }
	;

op:
	'+' 
	| '-' 
	| '/' 
	| '*' 
	| '<' 
	| '>' 
	| OPERATOR_OR 
	| OPERATOR_AND 
	| OPERATOR_NE 
	| OPERATOR_EQ 
	| OPERATOR_LE 
	| OPERATOR_GE 

%%

int yyerror(char* s) {
	fprintf(stdout, "%s na linha %i\n", s,getLineNumber());
	exit(3);
}