#ifndef HYPERGRAPH_H
#define HYPERGRAPH_H

#include "sizes.h"

#include "Buffer.h"
#include "NodeIndex.h"
#include "Hashtable.h"
#include "Stack.h"

class Hypergraph {
public:
    void insertSCC(int);
    void insertEdge(int, int);
    bool DFS(int, int, Stack &stack, Hashtable &);
    int getListHead(int);
    int getTotalNodeCount(int);
    int getNeighbor(int, int, int&, int&);
    int getRandNeighbor(int, int&, int&);
    int getListNodeCount(int);
private:    
    SBuffer SCCbuffer_;
    NodeIndex SCCIndex_;
};

#endif