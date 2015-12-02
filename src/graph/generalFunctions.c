#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "./../../headers/generalParams.h"
#include "./../../headers/generalFunctions.h"
#include "./../../headers/errors.h"
#include "./../../headers/node.h"


FILE* openFile(char* path) {
	FILE* rv = fopen(path, FILEMODE);
	if (rv == NULL)
		setError(INVALID_PATH);
	
	return rv;
}

int getNext(FILE* fptr, uint32_t* id) {
	return fscanf(fptr, "%u", id) == 1;
}

void closeFile(FILE* fptr) {
	if (fptr != NULL)
		fclose(fptr);
}

void quickSort(Node_t* array, int from,int limit) {
	int lead;

	if (from < limit) {
		lead = partition(array, from, limit);
		quickSort(array, from, lead - 1);
		quickSort(array, lead + 1, limit);
	}
}

//Function used by QuickSort
int partition(Node_t* array, int from, int limit) {
	uint32_t lead = getNodeId(array[from]);
	int started = from, i;

	for (i = from + 1; i <= limit; i++)
		if (getNodeId(array[i]) <= lead) {
			started++;
			swap(&array[i], &array[started]);
		}
	swap(&array[from], &array[started]);

	return started; 
}

//Function used by QuickSort
void swap(Node_t* from, Node_t* to) {
	Node_t temp;

	temp = *from;
	*from = *to;
	*to = temp;
}

Node_t binarySearch(Node_t* array, int to, uint32_t id) {
	int from = 0;
	
	while (from <= to) {
		int mid = from + (to - from) / 2;
		
		if (getNodeId(array[mid]) > id)
			to = mid - 1;
		else if (getNodeId(array[mid]) < id)
			from = mid + 1; 
		else
			return array[mid];
	}
	
	return NULL;
}
