/* * hash.c
 *
 *  Created on: Sep 7, 2012
 */
#include "m_hash.h"

struct HASH_NODE {
	int code;
	HASH_NODE* next;
};

int getAddress(int code) {
	return code % HASH_SIZE;
}

HASH_NODE * getNode(int * code) {


}
