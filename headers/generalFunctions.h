#pragma once

#include <stdint.h>

#include "./node.h"

typedef struct threadArgs* args_t;

FILE* openFile(char*);
int getNext(FILE*, uint32_t*);
void closeFile(FILE*);
void quickSort(Node_t*, int, int);
int partition(Node_t*, int, int);
void swap(Node_t*, Node_t*);
Node_t binarySearch(Node_t*, int, uint32_t);
void* startThread(void*);
