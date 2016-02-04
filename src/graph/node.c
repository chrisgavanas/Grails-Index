#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "./../../headers/node.h"
#include "./../../headers/edge.h"
#include "./../../headers/label.h"
#include "./../../headers/generalParams.h"


struct Node {
	uint32_t nodeId;
	Edge_t edges;
	int noEdges;
	Label_t* labels;
	int* visited;
};

void initNode(Node_t* node, uint32_t id) {
	int i;
	
	*node = malloc(sizeof(struct Node));

	(*node)->nodeId = id;
	(*node)->edges = NULL;
	(*node)->noEdges = 0;
	(*node)->labels = malloc(getSizeOfLabel() * LABEL_LEVEL);
	(*node)->visited = malloc(sizeof(int) * LABEL_LEVEL);
	for (i = 0; i < LABEL_LEVEL; i++) {
		initLabel(&((*node)->labels[i]));
		(*node)->visited[i] = 0;
	}
}

uint32_t getNodeId(Node_t node) {
	return node->nodeId;
}

void setNodeId(Node_t node, uint32_t nodeId) {
	node->nodeId = nodeId;
}

void addFollow(Node_t node, Node_t follow) {
	Edge_t newEdge;
	
	initEdge(&newEdge, follow);
	setNextEdge(newEdge, node->edges);
	node->edges = newEdge;
	node->noEdges++;
}

Edge_t getEdges(Node_t node) {
	return node->edges;
}

int getVisited(Node_t node, int thread) {
	return node->visited[thread];
}

void setVisited(Node_t node, int thread, int visited) {
	node->visited[thread] = visited;
}

Label_t* getLabels(Node_t node) {
	return node->labels;
}

void fixLabels(Node_t node, int thread) {
	Edge_t edge ;
	extern int* currRank;
	int i;
	node->visited[thread] = 1;

	for (i = 0; i < node->noEdges; i++) {
		int random = rand() % node->noEdges;
		edge = node->edges;
		
		while (random--)
			edge = getNextEdge(edge);

		if (getVisited(getNode(edge), thread)) {
			edge = node->edges;
			while (edge != NULL && getVisited(getNode(edge), thread))
				edge = getNextEdge(edge);

			if (edge == NULL || getVisited(getNode(edge), thread))
				break;
		}

		fixLabels(getNode(edge), thread);
	}
	

	setRank(node->labels[thread], ++currRank[thread]);
	int minSubRank = getRank(node->labels[thread]);
	edge = node->edges;
	while (edge != NULL) {
		Node_t childNode = getNode(edge);
		int childMinSubRank = getMinSubRank(childNode->labels[thread]);
		
		if (childMinSubRank != 0 && childMinSubRank < minSubRank)
			minSubRank = childMinSubRank;
		edge = getNextEdge(edge);
	}
	setMinSubRank(node->labels[thread], minSubRank);
}

void deleteNode(Node_t node) {
	int i;
	Edge_t edge = node->edges;
	
	while (edge != NULL) {
		Edge_t temp = getNextEdge(edge);
		free(edge);
		edge = temp;
	}
	for (i = 0; i < LABEL_LEVEL; i++)
		free(node->labels[i]);
	free(node->labels);
}

void freeVisited(Node_t node) {
	free(node->visited);
	node->visited = NULL;
}

/*	Used for debugging	*/
void printNode(Node_t node) {
	int i;
	printf("Node %u -> Label ", node->nodeId);
	for (i = 0; i < LABEL_LEVEL; i++)
		printf("(%d, %d) ", getMinSubRank(node->labels[i]), getRank(node->labels[i]));
	printf("\n");	
//	printf("%u ", node->nodeId);
}
