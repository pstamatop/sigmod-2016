#include <cstdlib>

#include "ListNode.h"


DListNode::DListNode() {
    totalNodeCount_ = 0;
    count_ = 0;
    nextListNode_ = -1;
    lastUsed_ = -1;
}

bool DListNode::addEdge(int id, int version) {
    if(count_ == NEIGHBORS) return false;
    neighbor_[count_] = id;
    edgeProperty_[count_] = version;
    count_ ++;
    return true;
}

void DListNode::addNextListNode(int index) {
    nextListNode_ = index;
}

bool DListNode::hasNextListNode() {
    return (nextListNode_ >= 0);
}

int DListNode::getNextListNode() { 
    return nextListNode_;
}

int DListNode::getCount() {
    return count_;
}

int DListNode::getTotalNodeCount() {
    return totalNodeCount_;
}

void DListNode::setTotalNodeCount(){
    totalNodeCount_ = totalNodeCount_ + 1;
}

int DListNode::getNeighbor(int i) {
    return neighbor_[i];
}

int DListNode::getVersion(int i) {
    return edgeProperty_[i];
}

bool DListNode::searchNeighbor(int id) {
    for(int i =  0; i < count_; i++){
        if(neighbor_[i] == id)
            return true;
    }
    return false;
}

void DListNode::setLastUsed(int index) {
    lastUsed_ = index;
}

int DListNode::getLastUsed(){
    return lastUsed_;
}

