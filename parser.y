%{

#include <stdio.h>
#include <stdlib.h>
#include "astree.h"
#include "scanner.h"
#define YYDEBUG 1

int yylex(void);
int yyerror(char *);


%}

%union 
{
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
%token KW_DO
%token KW_WHILE
%token KW_INPUT
%token KW_RETURN
%token KW_OUTPUT

%token TOKEN_ERROR


%token OPERATOR_LE
%token OPERATOR_GE
%token OPERATOR_EQ
%token OPERATOR_NE
%token OPERATOR_AND
%token OPERATOR_OR

%token <symbol>ID
%token <symbol>LIT_INTEGER
%token <symbol>LIT_FLOA
%token <symbol>LIT_FALSE
%token <symbol>LIT_TRUE
%token <symbol>LIT_CHAR
%token <symbol>LIT_STRING


%type <ast>program
%type <ast>hl_statements
%type <ast>hl_statement
%type <ast>tipo
%type <ast>cabecalho
%type <ast>lista_de_parametros
%type <ast>seq_decl
%type <ast>cmd
%type <ast>left
%type <ast>lista_de_elementos
%type <ast>E
%type <ast>expressoes
%type <ast>cmd_block
%type <ast>eopc
%type <ast>var_dec
%type <ast>cmds

%left OPERATOR_LE  OPERATOR_GE  OPERATOR_EQ  OPERATOR_NE  OPERATOR_AND OPERATOR_OR '<' '>'
%left '-'  '+'
%left '*'  '/'

%%

program:
	hl_statements 							{ 
												//astree_check_semantics($$);
												if (display_ast) astree_exibe($$,0);
												
												if (display_tac)  
												{
													genco($$);	
													tac_print($$);
												}
												if (numberOfErrors == 0)
												{
												   printf("Gerando arquivo de de saída: %s\n","output.s");
//												   generate_machine_code("output.s",NULL);
												}  
											}
	;

hl_statements:
	hl_statements hl_statement 				{ $$ = astree_create(ASTN_LIST, NULL, $1, $2, NULL, NULL);}
	|										{ $$ = 0 ;}  
	;
hl_statement: 
	ID ':' tipo ';'  						{ $$ = astree_create_basic(ASTN_VAD, $1, $3); }
	| ID ':' tipo '[' LIT_INTEGER ']' ';'	{ $$ = astree_create(ASTN_VED, $1, $3,astree_create_symbol(ASTN_IV, $5),NULL, NULL); }
	| cabecalho seq_decl cmd_block ';' 		{ $$ = astree_create(ASTN_FUNCTION, NULL, $1, $2, $3, NULL); }
	;
	
tipo:
	KW_INT 									{ $$ =  astree_create_empty(ASTN_IT); }
	| KW_FLOAT 								{ $$ =  astree_create_empty(ASTN_FT); }
	| KW_CHAR 								{ $$ =  astree_create_empty(ASTN_CT); }
	| KW_BOOL 								{ $$ =  astree_create_empty(ASTN_BT); }
	;

cabecalho:					
	ID ':' tipo '(' lista_de_parametros ')' { $$ = astree_create(ASTN_HEADER, $1 ,$3 ,$5, NULL, NULL); }
	;

lista_de_parametros:					
	lista_de_parametros ',' var_dec 		{ $$ = astree_create(ASTN_LIST, NULL ,$1,$3,NULL,NULL);}
	| var_dec					    		/* default */
	| 										{ $$ = 0; }
	;

seq_decl: 		
	seq_decl var_dec ';'			       	{ $$ = astree_create(ASTN_LIST, NULL ,$1,$2,NULL,NULL); }
	| 										{ $$ = 0; }
	;

var_dec:
	ID ':' tipo 							{ $$ = astree_create_basic(ASTN_VAD,$1, $3); }
	;

cmd_block:
	'{' cmds '}' 							{ $$ =  astree_create_default(ASTN_LIST, $2); }
	;

cmds:
	cmds ';' cmd 							{ $$ =   astree_create(ASTN_LIST, NULL ,$1,$3,NULL,NULL); 	}	
	| cmd 									/* default */
	;

eopc:
	KW_ELSE cmd_block 						{ $$ = astree_create_default(ASTN_IF_ELSE,$2);}
	|										{ $$ = 0; }
	;

cmd:			
	KW_IF '(' E ')' KW_THEN cmd_block eopc	{ $$= astree_create(ASTN_IF,NULL,$3,$6,$7,NULL);}
	| KW_WHILE '(' E ')' cmd_block 			{ $$= astree_create(ASTN_WHILE,NULL,$3,$5,NULL,NULL);}
	| left '=' E 							{ $$= astree_create(ASTN_ASSIGNMENT,NULL,$1,$3,NULL,NULL);}
	| KW_INPUT ID 							{ $$= astree_create_symbol(ASTN_INPUT,$2); }
	| KW_OUTPUT lista_de_elementos 			{ $$= astree_create_default(ASTN_OUTPUT,$2);}
	| KW_RETURN E 							{ $$= astree_create_default(ASTN_RETURN,$2);}
	| 										{ $$ = 0; }
	| cmd_block 							/* default */
	;

left:					
	ID										{ $$ =  astree_create_symbol(ASTN_SYMBOL_VAR, $1); }
	| ID '[' E ']' 							{ $$ = astree_create_basic(ASTN_SYMBOL_VEC,$1, $3); }
	;

lista_de_elementos:	
	lista_de_elementos ',' E 				{ $$ = astree_create(ASTN_LIST, NULL, $1, $3, NULL,NULL); }
	| E 									/* default */
	;


expressoes:
	expressoes ',' E 						{ $$ = astree_create(ASTN_LIST, NULL, $1,$3,NULL,NULL); }
	| E  									/* default */
	| 										{ $$ = 0; }
	;

E:
	E '+' E 								{ $$ = astree_create_op(ASTN_OP_ADD,$1,$3); }
	| E '-' E 								{ $$ = astree_create_op(ASTN_OP_SUB,$1,$3); }	 					
	| E '/' E 								{ $$ = astree_create_op(ASTN_OP_DIV,$1,$3); }	 					
	| E '*' E 								{ $$ = astree_create_op(ASTN_OP_MUL,$1,$3); }	 					
	| E '<' E 								{ $$ = astree_create_op(ASTN_OP_GT,$1,$3); }	 					
	| E '>' E 								{ $$ = astree_create_op(ASTN_OP_LT,$1,$3); }	 					
	| E OPERATOR_OR E 						{ $$ = astree_create_op(ASTN_OP_OR,$1,$3); }	 				
	| E OPERATOR_AND E 						{ $$ = astree_create_op(ASTN_OP_AND,$1,$3); }	 					
	| E OPERATOR_NE E 						{ $$ = astree_create_op(ASTN_OP_NE,$1,$3); }	 					
	| E OPERATOR_EQ E 						{ $$ = astree_create_op(ASTN_OP_EQ,$1,$3); }	 					
	| E OPERATOR_LE E 						{ $$ = astree_create_op(ASTN_OP_LE,$1,$3); }	 					
	| E OPERATOR_GE E 						{ $$ = astree_create_op(ASTN_OP_GE,$1,$3); }	 					
	| '(' E ')' 							{ $$ = astree_create_default(ASTN_PAR,$2); }
	| ID '(' expressoes ')' 				{ $$ = astree_create_basic(ASTN_FUNCALL, $1, $3); }
	| ID 									{ $$ = astree_create_symbol(ASTN_SYMBOL_VAR, $1); }
	| '-'E	 								{ $$ = astree_create_default(UMINUS, $2); }
	| ID '[' E ']' 							{ $$ = astree_create_basic(ASTN_SYMBOL_VEC, $1,$3);  }
	| LIT_INTEGER 							{ $$ = astree_create_symbol(ASTN_IV, $1); }
	| LIT_FLOA 								{ $$ = astree_create_symbol(ASTN_FV, $1); }
	| LIT_TRUE 								{ $$ = astree_create_symbol(ASTN_TRUE, $1);}
	| LIT_FALSE 							{ $$ = astree_create_symbol(ASTN_FALSE, $1); }
	| LIT_CHAR 								{ $$ = astree_create_symbol(ASTN_CV, $1); }
	| LIT_STRING 							{ $$ = astree_create_symbol(ASTN_SV, $1); }
	;

%%

int yyerror(char* s) 
{
	fprintf(stdout, "%s na linha %i\n", s,getLineNumber());
	exit(3);
}