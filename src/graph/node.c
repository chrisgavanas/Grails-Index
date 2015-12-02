#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "./../../headers/node.h"
#include "./../../headers/edge.h"


struct Node {
	uint32_t nodeId;
	Edge_t edges;
};

void initNode(Node_t* node, uint32_t id) {
	*node = malloc(sizeof(struct Node));

	(*node)->nodeId = id;
	(*node)->edges = NULL;
}

uint32_t getNodeId(Node_t node) {
	return node->nodeId;
}

void setNodeId(Node_t node, uint32_t nodeId) {
	node->nodeId = nodeId;
}

void addFollow(Node_t node, Node_t follow) {
	Edge_t newEdge;
	
	initEdge(&newEdge, follow->nodeId);
	setNextEdge(newEdge, node->edges);
	node->edges = newEdge;
}

Edge_t getEdges(Node_t node) {
	return node->edges;
}

void deleteNode(Node_t node) {
	Edge_t edge;
	
	while ((edge = getNextEdge(node->edges)) != NULL)
		free(edge);
}

/*	Used for debugging	*/
void printNode(Node_t node) {
	printf("%u ", node->nodeId);
}
