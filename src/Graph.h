#ifndef GRAPH_H
#define GRAPH_H

#include "Buffer.h"
#include "NodeIndex.h"
#include "CC.h"
#include "Queue.h"
#include "Hashtable.h"
#include "Stack.h"
#include "SCC.h"
#include "Hypergraph.h"
#include "Grail.h"
#include "Tarjantable.h"
#include "Visited.h"


class DGraph {
public:
    void insertNodes(int, int, int);
    void insertEdge(int, int, int);
    int bidirectionalBFS(int, int, Queue &, Queue &, Visited &, Visited &, int *, int *, int, int);
    int BFS(Queue &, Visited &, Visited &, int *, int *, int &, bool, int, int, int, int, int&);
    void estimateConnectedComponents(Stack &, int);
    void createHypergraph();
    void estimateStronglyConnectedComponents(Stack &);
    void createSCC(int);//testing
    void addSCC(int);//testing
    void addNodeSCC(int, int);//testing;
    void dynamicInit(int);
    void staticInit();
    void setType(int);
    void CCaddition(int, int, int);
    void resetUpdate(int, int);
    int getMaxIndexSize();
    void newVersion(int);
private:    
    DBuffer bufferOut_;
    NodeIndex nodeIndexOut_;
    NodeIndex versionOut_;
    DBuffer bufferIn_;
    NodeIndex nodeIndexIn_;
    NodeIndex versionIn_;
    CC wcomponents_;
    Visited visited;
};

class SGraph {
public:
    void insertNodes(int, int);
    void insertEdge(int, int);
    int bidirectionalBFS(int, int, Queue &, Queue &, Visited &, Visited &, int *, int *, int);
    int BFS(Queue &, Visited &, Visited &, int *, int *, int &, bool, int, int, int, int&);
    void estimateConnectedComponents(Stack &, int);
    void createHypergraph();
    void estimateStronglyConnectedComponents(Stack &);
    void createSCC(int);//testing
    void addSCC(int);//testing
    void addNodeSCC(int, int);//testing;
    void dynamicInit(int);
    void staticInit();
    void setType(int);
    void CCaddition(int, int);
    void resetUpdate(int);
    int getMaxIndexSize();
    int getMaxIndexCount();
    int getCompCount();
    void visitedInit(int);
    void copySccs();
private:    
    SBuffer bufferOut_;
    NodeIndex nodeIndexOut_;
    SBuffer bufferIn_;
    NodeIndex nodeIndexIn_;
    SCC scomponents_;
    Hypergraph hypergOut_;
    Hypergraph hypergIn_;
    Grail grailIndexOut_;
    Grail grailIndexIn_;
    TarjanTable tarjanTable_;
    Visited visited;
};

#endif // GRAPH_H