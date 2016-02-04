#pragma once

#include <stdint.h>

typedef struct Edge* Edge_t;

#include "./node.h"

void initEdge(Edge_t*, Node_t);
Node_t getNode(Edge_t);
void setNode(Edge_t, Node_t);
Edge_t getNextEdge(Edge_t);
void setNextEdge(Edge_t, Edge_t);
