#include <cstdlib>
#include <cstring>

#include "Buffer.h"

DBuffer::DBuffer() { 
    size_ = BUFFER;
    count_ = 0;
    buffer_ = (DListNode*) malloc(size_ * sizeof(DListNode));
}

DBuffer::~DBuffer() {
    free(buffer_);
}

int DBuffer::allocNewNode() {
    if(count_ + 1 > size_) { //if there is no space allocate memory
        int oldSize = size_;
        size_ = 2 * size_;
        buffer_ = (DListNode *) realloc(buffer_, sizeof(DListNode) * size_);
    }
    count_ ++;
    DListNode *node = new DListNode();
    memcpy(&buffer_[count_ - 1], node, sizeof(DListNode));
    delete node;
    return count_ - 1;  //return index of available DListNode
}

DListNode* DBuffer::getListNode(int index) {
    return &buffer_[index];
}


void DBuffer::addEdge(int index, int id, int version){
    int initIndex = index; //index of Node's head
    int newIndex;
    if(buffer_[index].count_ == 0)
        buffer_[index].lastUsed_ = index;
    int lastUsed = buffer_[index].lastUsed_;
    if(!buffer_[lastUsed].addEdge(id, version)){ //if there is no space in the currently in use DListNode 
        newIndex = allocNewNode();
        buffer_[initIndex].lastUsed_ = newIndex;
        buffer_[newIndex].addEdge(id, version);
        buffer_[initIndex].totalNodeCount_ =  buffer_[initIndex].totalNodeCount_ + 1;
        buffer_[lastUsed].nextListNode_ = newIndex; //connect previous "last used" node with the new one
    }
    else
        buffer_[index].totalNodeCount_ =  buffer_[index].totalNodeCount_ + 1; 
}

bool DBuffer::searchNeighbor(int index, int id) {
    if(buffer_[index].searchNeighbor(id))
        return true;
    while(buffer_[index].hasNextListNode()){
        index = buffer_[index].nextListNode_;
        if(buffer_[index].searchNeighbor(id))
            return true;
    }
    return false;
}

int DBuffer::getTotalNodeCount(int index) {
    return buffer_[index].totalNodeCount_;
}

void DBuffer::setLastUsed(int index){
    buffer_[index].lastUsed_ = index;
}

int DBuffer::getNeighbor(int index, int i, int& last , int& node, int& version){ //return neighbor in given index and position
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
    version = buffer_[last].getVersion(neighbor);
    return buffer_[last].neighbor_[neighbor];
}

int DBuffer::getRandNeighbor(int index, int &randNeighbor, int &next) {
    next = buffer_[index].nextListNode_;
    int count = buffer_[index].count_;
    randNeighbor = rand() % (count);
    return buffer_[index].getNeighbor(randNeighbor);
}

int DBuffer::getListNodeCount(int index) {
    return buffer_[index].count_;
}
