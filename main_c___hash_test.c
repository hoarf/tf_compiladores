#include "main.h"
/*
 * Este arquivo eh usado para teste apenas
 */

int main(int argc, char **argv) {

	test_init();
	test_insert();
	test_getAddress();
	test_print();

	return 0;
}

void test_init(void) {
	printf("%s\n", "Testing: init() ..");
	init();
	printf("%s\n", "Passed!");
}

void test_print(void) {
	printf("%s\n", "Testing: print() ..");
	insertNode("alan",TK_IDENTIFIER);
	insertNode("alan",LIT_CHAR);
	insertNode("alan",LIT_FALSE);
	print();
	printf("%s\n", "Passed!");
}

void test_insert(void) {
	printf("%s\n", "Testing: insertNode() ..");
	insertNode("alan",TK_IDENTIFIER);
	printf("%s\n", "Passed!");
}

void test_getAddress(void) {
	printf("%s\n", "Testing: getAddress() ..");
	insertNode((char*) "alan",TK_IDENTIFIER);
	printf("Address: %d\n",getAddress("alan"));
	printf("%s\n", "Passed!");
}


