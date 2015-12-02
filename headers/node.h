#pragma once

#include <stdint.h>
#include "./edge.h"

typedef struct Node* Node_t;

void initNode(Node_t*, uint32_t);
uint32_t getNodeId(Node_t);
void setNodeId(Node_t, uint32_t);
Edge_t getEdges(Node_t);
void addFollow(Node_t, Node_t);
void deleteNode(Node_t);
void printNode(Node_t);
