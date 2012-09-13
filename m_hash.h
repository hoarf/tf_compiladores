/*
 * hash.h
 *
 *  Created on: Sep 7, 2012
 *      Author: alan
 */
#ifndef HASH_H_
#define HASH_H_

#define HASH_SIZE	977

struct _Hash_Node;
typedef struct _Hash_Node HASH_NODE;

int getAddress(char* name);

HASH_NODE* getItem(int address);

HASH_NODE* putItem(int address, HASH_NODE* item);

void printTable();

#endif /* HASH_H_ */
