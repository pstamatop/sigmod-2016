#include <cstdlib>
#include <cstring>

#include "NodeIndex.h"

NodeIndex::NodeIndex() {
    array_ = (int*) malloc(INDEX * sizeof(int));
    size_ = INDEX;
    memset(array_ , 0, size_ * sizeof(int));
    count_ = 0;
}

NodeIndex::~NodeIndex() {
    free(array_);
}

void NodeIndex::insertNode(int id,int index) { 
    if (id + 1 > size_){
        int temp = size_;
        while(temp <= id)
            temp *= 2;
        array_ = (int *)realloc(array_, sizeof(int) * temp);
        memset(array_ + size_, 0, (temp-size_) * sizeof(int));
        size_ = temp;
    }
    if(array_[id] > 0)
        return;
    array_[id] = index + 1;
    count_ ++;
}

int NodeIndex::getListHead(int id) {
    if(id + 1 > size_)
        return - 1;
   return array_[id] - 1;
}

void NodeIndex::initArray(int start, int end){
    for(int i = start; i < end; i++)
        array_[i] = -1;
}

bool NodeIndex::searchNode(int id){
    if((id + 1 <= size_) && (array_[id] > 0))
        return true;
    else
        return false;
}

int NodeIndex::getSize() {
    return size_;
}
