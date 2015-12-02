#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "./../../headers/edge.h"

struct Edge {
	uint32_t nodeId;
	Edge_t next;
};

void initEdge(Edge_t* edge, uint32_t nodeId) {
	*edge = malloc(sizeof(struct Edge));
	
	(*edge)->nodeId = nodeId;
	(*edge)->next = NULL;
}

uint32_t getId(Edge_t edge) { 
	return edge->nodeId;
}

void setId(Edge_t edge, uint32_t nodeId) {
	edge->nodeId = nodeId;
}

Edge_t getNextEdge(Edge_t edge) {
	if (edge == NULL)
		return NULL;
		
	return edge->next;
}

void setNextEdge(Edge_t edge, Edge_t next) {
	edge->next = next;
}
