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


/*	hashTable_t ht;
	initHashTable(&ht);
	
	Node_t n1, n2, n3, n4, n5, n6, n7, n8, n9;

	initNode(&n9, 9);	
	initNode(&n8, 8);			
	initNode(&n7, 7);		
	initNode(&n6, 6);		
	initNode(&n5, 5);		
	initNode(&n4, 4);
	initNode(&n3, 3);
	initNode(&n2, 2);	
	initNode(&n1, 1);
	
	insert(ht, n9);
	insert(ht, n8);
	insert(ht, n7);
	insert(ht, n6);
	insert(ht, n5);
	insert(ht, n4);
	insert(ht, n3);
	insert(ht, n2);
	insert(ht, n1);

	sort(ht);
	printHashTable(ht);

	printf("%d\n", lookUp(ht, 5) == NULL);

	deleteHashTable(&ht);
*/

	return 0;
}
