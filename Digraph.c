// PA3: DiGraph Properties
// CMPS 101 
// Winter 2019 
// Stone, Matthew 
// 1673656 
//-------------------------
#include <stdio.h>
#include <stdlib.h>
#include "Digraph.h"
#include "List.h"
typedef struct GraphObj
{
	int numVertices;
	int numEdges;
	List * adjacency;
	int * tracker;
	// pather is a secondary tracker solely for pathexists.
	int * Pather;
	int acyclic;
}GraphObj;

// constructor
Digraph newDigraph(int numVertices)
{
    Digraph NGraph = malloc(sizeof(GraphObj));
    NGraph->numVertices = numVertices;
    NGraph->numEdges = 0;
    NGraph->acyclic = 0;
    NGraph->adjacency = calloc(numVertices+1, sizeof(List));
    for (int x = 0; x < numVertices+1; x++)
    {
        NGraph->adjacency[x] = newList();
    }
    NGraph->tracker = calloc(numVertices+1, sizeof(int));
    return (NGraph);
}

// destructor
void freeDigraph(Digraph *pG)
{
    Digraph G = *pG;
    for (int x = 0; x <= G->numVertices; x++)
    {
        freeList(&G->adjacency[x]);
    }
    free(G->adjacency);
    free(G->tracker);
    free(*pG);
}

// ACCESS FUNCTIONS
int getOrder(Digraph G)
{
    return G->numVertices;
}

int getSize(Digraph G)
{
    return G->numEdges;
}

int getOutDegree(Digraph G, int u)
{
    return length(G->adjacency[u]);
}

List getNeighbors(Digraph G, int u)
{
    return G->adjacency[u];
}

// MANIPULATION FUNCTION
int addEdge(Digraph G, int u, int v)
{
    if ( u > G->numVertices || v > G->numVertices || u < 0 || v < 0 )
    {
        // invalid vertices not allowed.
        return -1;
    }
    else if ( u == v )
    {
        // self loops not allowed
        return -1;
    }
    else
    {
        if ( length(G->adjacency[u]) == 0 )
        {
            append(G->adjacency[u],v);
            G->numEdges++;
            return 0;
        }
        else
        {
            Node temp = getFront(G->adjacency[u]);
            while ( temp != NULL )
            {
                if ( getValue(temp) == v )
                {
                    return 1;
                }
                temp = getNextNode(temp);
            }
            append(G->adjacency[u],v);
            G->numEdges++;
            return 0;
        }
    }
}

int deleteEdge(Digraph G, int u, int v)
{
    if ( u > G->numVertices || v > G->numVertices || u < 0 || v < 0)
    {
        // this cannot exist
        return 1;
    }
    else if ( u == v )
    {
        // this cannot exist
        return 1;
    }
    else
    {
        if ( length(G->adjacency[u]) > 0 )
        {
            Node temp = getFront(G->adjacency[u]);
            while ( temp != NULL )
            {
                if ( getValue(temp) == v )
                {
                    deleteNode(G->adjacency[u],temp);
                    G->numEdges--;
                    return 0;
                }
                temp = getNextNode(temp);
            }
            return 1;
        }
        else
        {
            return 1;
        }
    }
}

void unvisitAll(Digraph G)
{
    for (int x = 0; x <= G->numVertices; x++)
    {
        G->tracker[x] = unvisited;
    }
}

int getMark(Digraph G, int u)
{
    return G->tracker[u];
}

void setMark(Digraph G, int u, int theMark)
{
    G->tracker[u] = theMark;
}

int PathExistsRecursive(Digraph G, int w, int v)
{
    // from pseudocode
    if ( w == v )
    {
        return found;
    }
    else 
    {
        List templist = getNeighbors(G,w);
        Node tempnode = getFront(templist);
        setMark(G,w,inprogress);
        while ( tempnode != NULL )
        {
            if ( getMark(G,getValue(tempnode)) == unvisited )
            {
                if ( PathExistsRecursive(G,getValue(tempnode),v) == found)
                {
                    return found;
                }
            }
            tempnode = getNextNode(tempnode);
        }
        setMark(G,w,alldone);
        return unfound;
    }
}

// OTHER FUNCTIONS
void printDigraph(FILE * out,Digraph G)
{
    fprintf(out,"%d",G->numVertices);
    for ( int x = 1; x <= G->numVertices; x++ )
    {
        Node temp = getFront(G->adjacency[x]);
        for ( int y = 0; y < length(G->adjacency[x]); y++)
        {
            fprintf(out,", %d %d", x, getValue(temp));
            temp = getNextNode(temp);
        }
    }
    fprintf(out,"\n");
}

// this function uses tarjan method, explained in Elizabeth's lab.
int getCountSCC(Digraph G)
{
    // using topological, we get a list that tells us where to start.
    unvisitAll(G);
    List stack = newList();
    for (int x = 1; x <= getOrder(G); x++)
    {
        if ( G->tracker[x] == unvisited )
        {
            inverter(G,stack,x);
        }
    }
    // creates inverted graph to traverse
    Digraph inverted = newDigraph(getOrder(G));
    for (int y = 1; y <= getOrder(inverted); y++)
    {
        Node temp = getFront(G->adjacency[y]);
        while (temp != NULL)
        {
            addEdge(inverted,getValue(temp),y);
            temp = getNextNode(temp);
        }
    }
    // uses DFS on graph to find SCC.
    unvisitAll(G);
    unvisitAll(inverted);
    int count = 0;
    while( getFront(stack) != NULL )
    {
        if ( inverted->tracker[getValue(getFront(stack))] == unvisited )
        {
            count++;
            DFS(inverted,getValue(getFront(stack)));
        }
        deleteFront(stack);
    }
    freeDigraph(&inverted);
    freeList(&stack);
    return count;
}
// this is a helper function used for recursion in getcountSCC. It inverts the graph and creates a list so SCCs can be found.
void inverter(Digraph G, List stack, int w)
{
    Node tempnode = getFront(G->adjacency[w]);
    G->tracker[w] = inprogress;
    while ( tempnode != NULL )
    {
        if ( G->tracker[getValue(tempnode)] == unvisited)
        {
            inverter(G,stack,getValue(tempnode));
        }
        tempnode = getNextNode(tempnode);
    }
    setMark(G,w,alldone);
    prepend(stack,w);
}
// this is a helper function to perform DFS for getcountSCC. 
void DFS(Digraph G, int w)
{
    Node tempnode = getFront(G->adjacency[w]);
    G->tracker[w] = inprogress;
    while ( tempnode != NULL )
    {
        if ( G->tracker[getValue(tempnode)] == unvisited)
        {
            DFS(G,getValue(tempnode));
        }
        tempnode = getNextNode(tempnode);
    }
    setMark(G,w,alldone);
}

int getNumSCCVertices(Digraph G, int u)
{
    int count = 0;
    if ( u <= getOrder(G) && u > 0)
    {
        for (int x = 0; x <= getOrder(G); x++)
        {
            if ( inSameSCC(G,x,u) == 1 )
            {
                count++;
            }
        }
        return count;
    }
    else
    {
        return -1;
    }
}

int inSameSCC(Digraph G, int u, int v)
{
    // checks if invalid, U and V must be in the graph range and cannot be the same.
    if ( u > getOrder(G) || v > getOrder(G)  || u < 0 || v < 0)
    {
        return -1;
    }
    else if ( u == v )
    {
        return 1;
    }
    else 
    {
        // clears tracker to ensure accuracy.
        unvisitAll(G);
        // if U paths to V and V paths to U, it is strongly connected.
        if ( PathExistsRecursive(G,u,v) == found )
        {
            unvisitAll(G);
            if ( PathExistsRecursive(G,v,u) == found )
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            // if U paths to V and V doesn't path to U, it is not connected.
            return 0;
        }
    }
}