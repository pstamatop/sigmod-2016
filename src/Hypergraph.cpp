#include "Hypergraph.h"
#include "Hashtable.h"
#include "Stack.h"


 void Hypergraph::insertSCC(int id) {
    int index;
    if(!SCCIndex_.searchNode(id)){  //if it does not exist in the Index
        index = SCCbuffer_.allocNewNode(); //allocate node in buffer
        SCCbuffer_.setLastUsed(index); //update node's last used listnode
        SCCIndex_.insertNode(id,index);
    }
 }

 void Hypergraph::insertEdge(int id1, int id2) {
    this->insertSCC(id1); //insert node in the Index
    int index = SCCIndex_.getListHead(id1);
    SCCbuffer_.addEdge(index, id2);
 }

 bool Hypergraph::DFS(int id1, int id2, Stack &stack, Hashtable &visited) {
    int dummy = -1, dummy2 = -1;
    int last = -1, node = -1, index, neighbor; // for getNeighbor
    int count = 0, n;
    stack.push(id1);
    while(stack.getCount() > 0) {
        n = stack.pop();
        if(!visited.searchVisited(n, dummy)){
            visited.addVisited(n, dummy);
            // Push to stack all in and out vertices
            index = SCCIndex_.getListHead(n);
            if(index < 0)
                count = 0;
            else
                count = SCCbuffer_.getTotalNodeCount(index);
            for(int i = 0; i < count; i++){
                neighbor = SCCbuffer_.getNeighbor(index, i, last, node);
                if(neighbor == id2)
                    return true;
                if(!visited.searchVisited(neighbor, dummy))
                    stack.push(neighbor);
            }
        }
    }
    return false;
 }

int Hypergraph::getListHead(int index) {
    return SCCIndex_.getListHead(index);
}

int Hypergraph::getTotalNodeCount(int index) {
    return SCCbuffer_.getTotalNodeCount(index);
}

int Hypergraph::getNeighbor(int index, int i, int& last , int& node) {
    return SCCbuffer_.getNeighbor(index , i, last, node); // i hope this works
}

int Hypergraph::getRandNeighbor(int index, int& rand, int& next) {
    return SCCbuffer_.getRandNeighbor(index, rand, next);
}

 int Hypergraph::getListNodeCount(int index) {
    return SCCbuffer_.getListNodeCount(index);
 }
