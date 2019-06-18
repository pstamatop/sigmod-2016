#ifndef LISTNODE_H
#define LISTNODE_H

#include "sizes.h"

class DListNode {
public:
    DListNode();
    bool addEdge(int, int);
    void addNextListNode(int);
    bool hasNextListNode();
    int getNextListNode();
    int getTotalNodeCount();
    void setTotalNodeCount();
    int getCount();
    int getNeighbor(int);
    int getVersion(int);
    bool searchNeighbor(int);
    void setLastUsed(int);
    int getLastUsed();
    int neighbor_[NEIGHBORS];
    int edgeProperty_[NEIGHBORS];
    int nextListNode_; //initialized with -1
    int totalNodeCount_; //updated only in head listnodes
    int count_;
    int lastUsed_; //updated only in head listnodes
};

class SListNode {
public:
    SListNode();
    bool addEdge(int);
    void addNextListNode(int);
    bool hasNextListNode();
    int getNextListNode();
    int getTotalNodeCount();
    void setTotalNodeCount();
    int getCount();
    int getNeighbor(int);
    bool searchNeighbor(int);
    void setLastUsed(int);
    int getLastUsed();
    int neighbor_[NEIGHBORS];
    int nextListNode_; //initialized with -1
    int totalNodeCount_; //updated only in head listnodes
    int count_;
    int lastUsed_; //updated only in head listnodes
};

#endif // LISTNODE_H