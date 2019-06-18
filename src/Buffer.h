#ifndef BUFFER_H
#define BUFFER_H

#include "ListNode.h"
#include "NodeIndex.h"
#include "sizes.h"

class DBuffer {
public:
    DBuffer();
    ~DBuffer();
    int allocNewNode();
    DListNode* getListNode(int);
    void addEdge(int, int, int);
    bool searchNeighbor(int,int);
    int getTotalNodeCount(int);
    void setLastUsed(int);
    int getNeighbor(int, int, int& , int&, int&);
    int getRandNeighbor(int, int&, int&);
    int getListNodeCount(int);
    int size_; //number of allocated ListNodes
    int count_; //number of ListNodes in use
    DListNode *buffer_;
};

class SBuffer {
public:
    SBuffer();
    ~SBuffer();
    int allocNewNode();
    SListNode* getListNode(int);
    void addEdge(int, int);
    bool searchNeighbor(int,int);
    int getTotalNodeCount(int);
    void setLastUsed(int);
    int getNeighbor(int, int, int& , int&);
    int getRandNeighbor(int, int&, int&);
    int getListNodeCount(int);
    int size_; //number of allocated ListNodes
    int count_; //number of ListNodes in use
    SListNode *buffer_;
};

#endif // BUFFER_H