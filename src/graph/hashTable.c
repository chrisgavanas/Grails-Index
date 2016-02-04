#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "./../../headers/hashTable.h"
#include "./../../headers/bucket.h"
#include "./../../headers/label.h"
#include "./../../headers/generalParams.h"
#include "./../../headers/errors.h"

struct hashTable {
	int tableSize;
	int realTableSize;
	int pointer;
	int round;
	Bucket_t* buckets;
};

int hashFunction(int round, uint32_t id, int tableSize) {
	return id % ((1 << round) * tableSize);
}

void initHashTable(hashTable_t* ht) {
	int i;
	
	*ht = malloc(sizeof(struct hashTable));
	(*ht)->tableSize = (*ht)->realTableSize = HT_SIZE;
	(*ht)->pointer = (*ht)->round = 0;
	(*ht)->buckets = malloc(sizeof(Bucket_t*) * HT_SIZE);
	for (i = 0; i < HT_SIZE; i++)
		initBucket(&((*ht)->buckets)[i]);
}

void increaseHashTable(hashTable_t ht) {
	ht->buckets = realloc(ht->buckets, sizeof(Bucket_t) * ht->realTableSize);
	initBucket(&(ht->buckets[ht->realTableSize - 1]));
}

void splitBucket(hashTable_t ht) {
	Bucket_t oldBucket = (ht->buckets)[ht->pointer];
	Node_t toAdd;

	initBucket(&(ht->buckets[ht->pointer]));
	while ((toAdd = getLastNode(oldBucket)) != NULL) {
		if (!insertNodeSorted(ht->buckets[hashFunction(ht->round + 1, getNodeId(toAdd), ht->tableSize)], toAdd)) {
			doubleNodes(ht->buckets[hashFunction(ht->round + 1, getNodeId(toAdd), ht->tableSize)]);
			insertNodeSorted(ht->buckets[hashFunction(ht->round + 1, getNodeId(toAdd), ht->tableSize)], toAdd);
		}
	}

	deleteBucket(oldBucket);
	free(oldBucket);
}

void insert(hashTable_t ht, Node_t node) {
	int toBePlaced = hashFunction(ht->round, getNodeId(node), ht->tableSize) >= ht->pointer ? hashFunction(ht->round, getNodeId(node), ht->tableSize) : hashFunction(ht->round + 1, getNodeId(node), ht->tableSize);

	if (haveSpace((ht->buckets)[toBePlaced]))
		insertNodeSorted((ht->buckets)[toBePlaced], node);
	else {
		doubleNodes(ht->buckets[toBePlaced]);
		insertNodeSorted((ht->buckets)[toBePlaced], node);
		ht->realTableSize += 1;
		increaseHashTable(ht);
		splitBucket(ht);
		if (ht->pointer == ht->realTableSize >> 1) {
			ht->pointer = 0;
			ht->round++;
		}
		else
			ht->pointer++;
	}
}

Node_t lookUp(hashTable_t ht, uint32_t id) {
	return hashFunction(ht->round, id, ht->tableSize) >= ht->pointer ? 
		lookUpNode(ht->buckets[hashFunction(ht->round, id, ht->tableSize)], id) : lookUpNode(ht->buckets[hashFunction(ht->round + 1, id, ht->tableSize)], id);
}

void sort(hashTable_t ht) {
	int i;
	
	for (i = 0; i < ht->realTableSize; i++)
		sortBucket(ht->buckets[i]);
}

void deleteHashTable(hashTable_t* ht) {
	int i;
	
	for (i = 0; i < (*ht)->realTableSize; i++) {
		deleteBucket((*ht)->buckets[i]);
		free((*ht)->buckets[i]);
	}
	
	free((*ht)->buckets);
	free(*ht);
	*ht = NULL;
}

void buildGrailIndex(hashTable_t ht, int thread) {
	int i, j;
	
	for (i = 0; i < ht->realTableSize; i++) {
		Node_t* nodes = getNodes(ht->buckets[i]);
		int noNodes = getBucketNo(ht->buckets[i]);
		
		for (j = 0; j < noNodes; j++) {
			Node_t node = nodes[j];
			
			if (getVisited(node, thread) == 1)
				continue;
			else
				fixLabels(node, thread);
		}
	}
}

int reachability(hashTable_t ht, uint32_t from, uint32_t to) {
	int i;
	Node_t a = lookUp(ht, from);
	Node_t b = lookUp(ht, to);

	if (a == NULL) {
		setError(NODE_FROM_NOT_FOUND);
		return -1;
	}
	if (b == NULL) {
		setError(NODE_TO_NOT_FOUND);
		return -1;
	}

	if (getNodeId(a) == getNodeId(b))
		return 1;
		
	Label_t* labelsA = getLabels(a);
	Label_t* labelsB = getLabels(b);
	int canAnswer = 0;
	
	for (i = 0; i < LABEL_LEVEL && !canAnswer; i++)
		if (!isSubset(labelsB[i], labelsA[i]))
			canAnswer++;

	if (canAnswer)
		return 0;

		
	Edge_t edge = getEdges(a);
	while (edge != NULL) {
		if (reachability(ht, getNodeId(getNode(edge)), to))
			return 1;
			
		edge = getNextEdge(edge);
	}
		
	return 0;
}

void freeVisitedNodes(hashTable_t ht) {
	int i, j;
	
	for (i = 0; i < ht->realTableSize; i++) {
		Node_t* nodes = getNodes(ht->buckets[i]);
		int noNodes = getBucketNo(ht->buckets[i]);
		
		for (j = 0; j < noNodes; j++)
			freeVisited(nodes[j]);	
	}
}

/*	Used for debugging	*/
void printHashTable(hashTable_t ht) {
	int i;

	for (i = 0; i < ht->realTableSize; i++) {
		printf("Bucket[%d]:\n", i);
		printBucket(ht->buckets[i]);
		printf("\n");
	}
}
