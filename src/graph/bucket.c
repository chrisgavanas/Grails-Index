#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./../../headers/generalParams.h"
#include "./../../headers/generalFunctions.h"
#include "./../../headers/bucket.h"
#include "./../../headers/node.h"

struct Bucket {
	int bucketNo;
	int maxCapacity;
	Node_t* node;
};

void initBucket(Bucket_t* bucket) {
	int i;
	
	*bucket = malloc(sizeof(struct Bucket));
	(*bucket)->bucketNo = 0;
	(*bucket)->maxCapacity = BUCKET_SIZE;
	(*bucket)->node = malloc(sizeof(Node_t) * BUCKET_SIZE);
	memset((*bucket)->node, 0, sizeof(Node_t) * BUCKET_SIZE);
}

int getBucketNo(Bucket_t bucket) {
	return bucket->bucketNo;
}

void setBucketNo(Bucket_t bucket, int bucketNo) {
	bucket->bucketNo = bucketNo;
}

int getBucketMaxCap(Bucket_t bucket) {
	return bucket->maxCapacity;
}

void setBucketMaxCap(Bucket_t bucket, int maxCapacity) {
	bucket->maxCapacity = maxCapacity;
}

Node_t* getNode(Bucket_t bucket) {
	return bucket->node;
}

int haveSpace(Bucket_t bucket) {
	return bucket->maxCapacity - bucket->bucketNo;
}

int insertNode(Bucket_t bucket, Node_t node) {
	if (bucket->bucketNo == bucket->maxCapacity)
		return 0;
	else {
		bucket->node[bucket->bucketNo++] = node;
		return 1;
	}
}

Node_t lookUpNode(Bucket_t bucket, uint32_t id) {
	return binarySearch(bucket->node, bucket->bucketNo - 1, id);
}

void doubleNodes(Bucket_t bucket) {
	bucket->node = realloc(bucket->node, sizeof(Node_t) * bucket->bucketNo * 2);
	memset(bucket->node + bucket->bucketNo, 0, bucket->bucketNo * sizeof(Node_t));
	bucket->maxCapacity <<= 1;
}

Node_t getLastNode(Bucket_t bucket) {
	if (!bucket->bucketNo)
		return NULL;
	else {
		Node_t rv = bucket->node[bucket->bucketNo-- - 1];
		bucket->node[bucket->bucketNo] = NULL;
		return rv;
	}
}

void sortBucket(Bucket_t bucket) {
	quickSort(bucket->node, 0, bucket->bucketNo - 1);	
}

void deleteBucket(Bucket_t bucket) {
	int i;
	
	for (i = 0; i < bucket->bucketNo; i++) {
		deleteNode(bucket->node[i]);
		free(bucket->node[i]);
	}
		
	free(bucket->node);
}

/*	Used for debugging	*/
void printBucket(Bucket_t bucket) {
	int i;
	
	for (i = 0; i < bucket->bucketNo; i++)
		if (bucket->node[i] == NULL)
			break;
		else
			printNode(bucket->node[i]);
}
