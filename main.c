/*
 * Main.c
 *
 *  Created on: Sep 7, 2012
 *      Author: alan
 */

#include <stdio.h>
#include "tokens.h"
#include "m_hash.h"
#include "main.h"

int main(int argc, char **argv) {
int r = running;
	int token;
	token = yylex();
	printf("%d",token);

}


