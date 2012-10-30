
#include "astree.h"
#include <stdlib.h>
#include <stdio.h>

void test_create() {
	printf("%s\n","Testando create()...");
	astree_create(AST_ADD,NULL,NULL,NULL,NULL,NULL);
	astree_create(AST_ADD,insertNode("TESTE",1),NULL,NULL,NULL,NULL);
	printf("%s\n","Test passed!");

}


void test_exibe() {
	printf("%s\n","Testando exibe()...");
	astree_exibe(
	astree_create(AST_ADD,NULL,
			astree_create(AST_ATTRIB,NULL,NULL,NULL,NULL,NULL),
			astree_create(AST_AND,NULL,NULL,NULL,NULL,NULL),
			astree_create(AST_BOOL,NULL,NULL,NULL,NULL,NULL),NULL),0);

	printf("%s\n","Test passed!");
}

int main(int argc, char **argv) {
	test_create();
	test_exibe();
}

