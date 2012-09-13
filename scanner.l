%{
	#include "tokens.h"
	#include "main.h"
%}

%%

int					{  return KW_INT;        }
float				{  return KW_FLOAT;      }
bool				{  return KW_BOOL;       }
char	 			{  return KW_CHAR;       }
if					{  return KW_IF;         }
then				{  return KW_THEN;       }
else				{  return KW_ELSE;       }
while				{  return KW_WHILE;      }
do					{  return KW_DO;         }
input				{  return KW_INPUT;      }
return				{  return KW_RETURN;     }
output				{  return KW_OUTPUT;     }

"<="				{  return OPERATOR_LE;   }
">="				{  return OPERATOR_GE;   }
"=="				{  return OPERATOR_EQ;   }
"="					{  return OPERATOR_NE;   }
"&&"				{  return OPERATOR_AND;  }
"||"				{  return OPERATOR_OR;   }

[a-z][_a-zA-Z0-9]*	{  return TK_IDENTIFIER; }
[0-9]+				{  return LIT_INTEGER;   }
[0-9]+.[0-9]+		{  return LIT_FLOA;      }
'false'				{  return LIT_FALSE;     }
'true'				{  return LIT_TRUE;	     }
\'[a-zA-Z]\'		{  return LIT_CHAR;      }
\"[a-zA-Z]*\"		{  return LIT_STRING;    }

.					{  return TOKEN_ERROR;   }


%%

int yywrap(void) {
	running = 0;
	return 1;
}


