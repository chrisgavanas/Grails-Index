#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "./../../headers/hashTable.h"
#include "./../../headers/bucket.h"
#include "./../../headers/generalParams.h"

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
		if (!insertNode(ht->buckets[hashFunction(ht->round + 1, getNodeId(toAdd), ht->tableSize)], toAdd)) {
			doubleNodes(ht->buckets[hashFunction(ht->round + 1, getNodeId(toAdd), ht->tableSize)]);
			insertNode(ht->buckets[hashFunction(ht->round + 1, getNodeId(toAdd), ht->tableSize)], toAdd);
		}
	}

	deleteBucket(oldBucket);
	free(oldBucket);
}

void insert(hashTable_t ht, Node_t node) {
	int toBePlaced = hashFunction(ht->round, getNodeId(node), ht->tableSize) >= ht->pointer ? hashFunction(ht->round, getNodeId(node), ht->tableSize) : hashFunction(ht->round + 1, getNodeId(node), ht->tableSize);

	if (haveSpace((ht->buckets)[toBePlaced]))
		insertNode((ht->buckets)[toBePlaced], node);
	else {
		doubleNodes(ht->buckets[toBePlaced]);
		insertNode((ht->buckets)[toBePlaced], node);
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

/*	Used for debugging	*/
void printHashTable(hashTable_t ht) {
	int i;

	for (i = 0; i < ht->realTableSize; i++) {
		printf("Bucket[%d]:\n", i);
		printBucket(ht->buckets[i]);
		printf("\n");
	}
}
