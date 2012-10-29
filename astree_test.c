
#include "astree.h"
#include <stdlib.h>

void test_create() {
	printf("%s","Testando create()...");
	astree_create(AST_ADD,NULL,NULL,NULL,NULL,NULL);
	astree_create(AST_ADD,insertNode("TESTE",1),NULL,NULL,NULL,NULL);

}


int main(int argc, char **argv) {
	test_create();
}

