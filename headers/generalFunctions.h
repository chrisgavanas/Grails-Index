#pragma once

#include <stdint.h>

#include "./node.h"

FILE* openFile(char*);
int getNext(FILE*, Node_t, Node_t);
void closeFile(FILE*);
void quickSort(Node_t*, int, int);
int partition(Node_t*, int, int);
void swap(Node_t*, Node_t*);
Node_t binarySearch(Node_t*, int, uint32_t);
