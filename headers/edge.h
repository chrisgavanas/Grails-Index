#pragma once

#include <stdint.h>

typedef struct Edge* Edge_t;

void initEdge(Edge_t*, uint32_t);
uint32_t getId(Edge_t);
void setId(Edge_t, uint32_t);
Edge_t getNextEdge(Edge_t);
void setNextEdge(Edge_t, Edge_t);
