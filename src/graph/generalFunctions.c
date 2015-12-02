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

int getNext(FILE* fptr, Node_t nodeA, Node_t nodeB) {
	uint32_t node1, node2;
	int rv = fscanf(fptr, "%u %u\n", &node1, &node2) < 2 ? -1 : 1;
	
	setNodeId(nodeA, node1);
	setNodeId(nodeB, node2);

	return rv;
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

Node_t binarySearch(Node_t* array, int dim, uint32_t id) {
	if (dim < 0)
		return NULL;
		
	while (array[dim] == NULL) {
		if (dim == 0)
			return NULL;
		dim--;
	}
	int first = 0, middle = dim / 2;

	while (first <= dim) {
		if (getNodeId(array[middle]) < id)
			first = middle + 1;
		else if (getNodeId(array[middle]) == id)
			return array[middle];
		else
			dim = middle - 1;
		middle = (first + dim) / 2;
	}
	return NULL;
}
