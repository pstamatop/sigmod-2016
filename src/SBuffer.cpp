#include <cstdlib>
#include <cstring>
#include <iostream>

#include "Buffer.h"

using namespace std;

SBuffer::SBuffer() { 
    size_ = BUFFER;
    count_ = 0;
    buffer_ = (SListNode*) malloc(size_ * sizeof(SListNode));
}

SBuffer::~SBuffer() {
    free(buffer_);
}

int SBuffer::allocNewNode() {
    if(count_ + 1 > size_) { //if there is no space allocate memory
        int oldSize = size_;
        size_ = 2 * size_;
        buffer_ = (SListNode *) realloc(buffer_, sizeof(SListNode) * size_);
    }
    count_ ++;
    SListNode *node = new SListNode();
    memcpy(&buffer_[count_ - 1], node, sizeof(SListNode));
    delete node;
    return count_ - 1;  //return index of available SListNode
}

SListNode* SBuffer::getListNode(int index) {
    return &buffer_[index];
}


void SBuffer::addEdge(int index, int id){
    int initIndex = index; //index of Node's head
    int newIndex;
    if(buffer_[index].count_ == 0)
        buffer_[index].lastUsed_ = index;
    int lastUsed = buffer_[index].lastUsed_;
    if(!buffer_[lastUsed].addEdge(id)){ //if there is no space in the currently in use SListNode 
        newIndex = allocNewNode();
        buffer_[initIndex].lastUsed_ = newIndex;
        buffer_[newIndex].addEdge(id);
        buffer_[initIndex].totalNodeCount_ =  buffer_[initIndex].totalNodeCount_ + 1;
        buffer_[lastUsed].nextListNode_ = newIndex; //connect previous "last used" node with the new one
    }
    else
        buffer_[index].totalNodeCount_ =  buffer_[index].totalNodeCount_ + 1; 
}

bool SBuffer::searchNeighbor(int index, int id) {
    if(buffer_[index].searchNeighbor(id))
        return true;
    while(buffer_[index].hasNextListNode()){
        index = buffer_[index].nextListNode_;
        if(buffer_[index].searchNeighbor(id))
            return true;
    }
    return false;
}

int SBuffer::getTotalNodeCount(int index) {
    return buffer_[index].totalNodeCount_;
}

void SBuffer::setLastUsed(int index){
    buffer_[index].lastUsed_ = index;
}

int SBuffer::getNeighbor(int index, int i, int& last , int& node){ //return neighbor in given index and position
    int tempnode = i / NEIGHBORS;
    int neighbor = i % NEIGHBORS;
    if(i == 0){
       last = index;
       node = tempnode;
    }
    index = last;
    if(tempnode != node){
        index = buffer_[last].nextListNode_;
    }
    last = index;
    node = tempnode;
    return buffer_[last].neighbor_[neighbor];
}

int SBuffer::getRandNeighbor(int index, int &randNeighbor, int &next) {
    next = buffer_[index].nextListNode_;
    int count = buffer_[index].count_;
    randNeighbor = rand() % (count);
    return buffer_[index].getNeighbor(randNeighbor);
}

int SBuffer::getListNodeCount(int index) {
    return buffer_[index].count_;
}
