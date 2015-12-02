#include <stdio.h>
#include <stdlib.h>

#include "./../../headers/generalParams.h"
#include "./../../headers/generalFunctions.h"
#include "./../../headers/errors.h"
#include "./../../headers/hashTable.h"
#include "./../../headers/node.h"


int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("%s\n", getError());
		return -1;
	}
	char* PATH = argv[1];
	
	FILE* fptr = openFile(PATH);
	if (fptr == NULL) {
		printf("%s\n", getError());
		return -1;
	}

	hashTable_t ht;
	initHashTable(&ht);

	uint32_t idA, idB;

	for (; ;) {
		idA = idB = 0;
		getNext(fptr, &idA);
		getNext(fptr, &idB);
		
		if (!idA || !idB)
			break;
	
		Node_t nodeA, nodeB;
		nodeA = lookUp(ht, idA);
		nodeB = lookUp(ht, idB);
		
		if (nodeA == NULL) {
			initNode(&nodeA, idA);
			insert(ht, nodeA);
		}
		if (nodeB == NULL) {
			initNode(&nodeB, idB);
			insert(ht, nodeB);
		}
		addFollow(nodeA, nodeB);
	}

	printHashTable(ht);
	deleteHashTable(&ht);
	
	closeFile(fptr);

	return 0;
}
