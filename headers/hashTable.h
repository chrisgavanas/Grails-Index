#pragma once

#include <stdint.h>

#include "./node.h"

typedef struct hashTable* hashTable_t;

int hashFunction(int, uint32_t, int);
void initHashTable(hashTable_t*);
void increaseHashTable(hashTable_t);
void splitBucket(hashTable_t);
void insert(hashTable_t, Node_t);
Node_t lookUp(hashTable_t, uint32_t);
void sort(hashTable_t);
void deleteHashTable(hashTable_t*);
void buildGrailIndex(hashTable_t, int);
void freeVisitedNodes(hashTable_t);
int reachability(hashTable_t, uint32_t, uint32_t);
void printHashTable(hashTable_t);
