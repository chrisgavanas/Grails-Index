#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "./../../headers/generalParams.h"
#include "./../../headers/generalFunctions.h"
#include "./../../headers/errors.h"
#include "./../../headers/hashTable.h"
#include "./../../headers/node.h"

//#include <sys/resource.h>

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("%s\n", getError());
		return -1;
	}
	char* PATH = argv[1];
	
//	struct rlimit rl;
//	getrlimit(RLIMIT_STACK, &rl);
//	rl.rlim_cur = 64L * 1024L * 1024L;

	
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
	srand((unsigned int) time(NULL));
	
	int i;
	extern int* currRank;
	currRank = malloc(sizeof(int) * LABEL_LEVEL);
	memset(currRank, 0, sizeof(int) * LABEL_LEVEL);
	pthread_t threads[5];
	for (i = 0; i < LABEL_LEVEL; i++) {
		args_t args;
		initArgs(&args, ht, i);
		pthread_create(&threads[i], NULL, startThread, (void*) args);
	}
	for (i = 0; i < LABEL_LEVEL; i++) 
		pthread_join(threads[i], NULL);	
	
	freeVisitedNodes(ht);	
		
	reachability(ht, 1, 10);
	
	
	deleteHashTable(&ht);
	closeFile(fptr);
	free(currRank);

	return 0;
}
