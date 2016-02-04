#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "./../../headers/edge.h"
#include "./../../headers/node.h"

struct Edge {
	Node_t node;
	Edge_t next;
};

void initEdge(Edge_t* edge, Node_t node) {
	*edge = malloc(sizeof(struct Edge));
	
	(*edge)->node = node;
	(*edge)->next = NULL;
}

Node_t getNode(Edge_t edge) { 
	return edge->node;
}

void setNode(Edge_t edge, Node_t node) {
	edge->node = node;
}

Edge_t getNextEdge(Edge_t edge) {
	if (edge == NULL)
		return NULL;
		
	return edge->next;
}

void setNextEdge(Edge_t edge, Edge_t next) {
	edge->next = next;
}
