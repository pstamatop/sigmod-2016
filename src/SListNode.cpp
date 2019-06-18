#include <cstdlib>

#include "ListNode.h"


SListNode::SListNode() {
    totalNodeCount_ = 0;
    count_ = 0;
    nextListNode_ = -1;
    lastUsed_ = -1;
}

bool SListNode::addEdge(int id) {
    if(count_ == NEIGHBORS) return false;
    neighbor_[count_] = id;
    count_ ++;
    return true;
}

void SListNode::addNextListNode(int index) {
    nextListNode_ = index;
}

bool SListNode::hasNextListNode() {
    return (nextListNode_ >= 0);
}

int SListNode::getNextListNode() { 
    return nextListNode_;
}

int SListNode::getCount() {
    return count_;
}

int SListNode::getTotalNodeCount() {
    return totalNodeCount_;
}

void SListNode::setTotalNodeCount(){
    totalNodeCount_ = totalNodeCount_ + 1;
}

int SListNode::getNeighbor(int i) {
    return neighbor_[i];
}

bool SListNode::searchNeighbor(int id) {
    for(int i =  0; i < count_; i++){
        if(neighbor_[i] == id)
            return true;
    }
    return false;
}

void SListNode::setLastUsed(int index) {
    lastUsed_ = index;
}

int SListNode::getLastUsed(){
    return lastUsed_;
}
