#pragma once

#include "./node.h"

typedef struct Bucket* Bucket_t;

void initBucket(Bucket_t*);
int getBucketNo(Bucket_t);
void setBucketNo(Bucket_t, int);
int getBucketMaxCap(Bucket_t);
void setBucketMaxCap(Bucket_t, int);
Node_t* getNodes(Bucket_t);
int haveSpace(Bucket_t);
int insertNode(Bucket_t, Node_t);
int insertNodeSorted(Bucket_t, Node_t);
Node_t lookUpNode(Bucket_t, uint32_t);
void doubleNodes(Bucket_t);
Node_t getLastNode(Bucket_t);
void sortBucket(Bucket_t);
void deleteBucket(Bucket_t);
void printBucket(Bucket_t);
