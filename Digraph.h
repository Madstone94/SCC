// PA4: Strongly Connected Components
// CMPS 101 
// Winter 2019 
// Stone, Matthew 
// 1673656 
//------------------------- 
#include <stdio.h>
#include "List.h"
#ifndef DIGRAPH_H_
#define DIGRAPH_H_
#define unvisited 0
#define inprogress 1
#define alldone 2
#define unfound 3
#define found 4

typedef struct GraphObj* Digraph;

typedef struct VerticeObj* Vertice;

// constructor
Digraph newDigraph(int numVertices);
// destructor
void freeDigraph(Digraph *pG);
// ACCESS FUNCTIONS
int getOrder(Digraph G);

int getSize(Digraph G);

int getOutDegree(Digraph G, int u);

List getNeighbors(Digraph G, int u);

// MANIPULATION FUNCTION

int addEdge(Digraph G, int u, int v);

int deleteEdge(Digraph G, int u, int v);

void unvisitAll(Digraph G);

int getMark(Digraph G, int u);

void setMark(Digraph G, int u, int theMark);

int PathExistsRecursive(Digraph G, int w, int v);

// OTHER FUNCTIONS

void printDigraph(FILE * out,Digraph G);

void inverter(Digraph G, List stack, int w);

void DFS(Digraph G, int w);

int getCountSCC(Digraph G);

int getNumSCCVertices(Digraph G, int u);

int inSameSCC(Digraph G, int u, int v);

#endif