#pragma once

#include <stdint.h>

typedef struct Node* Node_t;

#include "./edge.h"
#include "./label.h"

void initNode(Node_t*, uint32_t);
uint32_t getNodeId(Node_t);
void setNodeId(Node_t, uint32_t);
Edge_t getEdges(Node_t);
Label_t* getLabels(Node_t);
void addFollow(Node_t, Node_t);
int getVisited(Node_t, int);
void setVisited(Node_t, int, int);
void fixLabels(Node_t, int);
void deleteNode(Node_t);
void freeVisited(Node_t);
void printNode(Node_t);
