#include <cstdlib>
#include <cstring>

#include "Tarjantable.h"

TarjanTable::TarjanTable(){
    size_ = 0;
    tarjanNodes_ = NULL;
}

void TarjanTable::tarjanTableInit(int size){
    size_ = size;
    tarjanNodes_ = (TarjanNode*) malloc(sizeof(TarjanNode) * size_);
    for(int i = 0; i < size_; i++){
        TarjanNode *node = new TarjanNode();
        memcpy(&tarjanNodes_[i], node, sizeof(TarjanNode));
        delete node;
    }
}

TarjanTable::~TarjanTable(){
    if(tarjanNodes_ != NULL)
        free(tarjanNodes_);
}

void TarjanTable::setNode(int i, int index, int parent){
    tarjanNodes_[i].index_ = index;
    tarjanNodes_[i].lowlink_ = index;
    tarjanNodes_[i].parent_ = parent;
    tarjanNodes_[i].iterator_ = 0;
    tarjanNodes_[i].last_ = -1;
    tarjanNodes_[i].getN_= -1;
}

void TarjanTable::incrIterator(int i){
    tarjanNodes_[i].iterator_++;
}

int TarjanTable::getIterator(int i){
    return tarjanNodes_[i].iterator_;
}

int TarjanTable::getParent(int i){
    return tarjanNodes_[i].parent_;
}

int TarjanTable::getIndex(int i){
    return tarjanNodes_[i].index_;
}

int TarjanTable::getLowlink(int i){
    return tarjanNodes_[i].lowlink_;
}

void TarjanTable::setLowlink(int i, int lowlink){
    tarjanNodes_[i].lowlink_ = lowlink;
}

int& TarjanTable::getLast(int i){
    return tarjanNodes_[i].last_;
}

int& TarjanTable::getN(int i){
    return tarjanNodes_[i].getN_;
}
