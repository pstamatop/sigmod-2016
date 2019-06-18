#include <cstdlib>
#include <cstring>

#include "Hashtable.h"

//Similar implementation to Buffer.cpp

BNode::BNode(){
    id_ = -1;
    length_ = -1;
}


Bucket::Bucket() {
    count_ = 0;
    nextBucket_ = -1;
    lastUsed_ = -1;
}

void Bucket::add(int id, int length){
    BNode *node = new BNode();
    node->id_ = id;
    node->length_ = length;
    memcpy(&bucket_[count_], node, sizeof(BNode));
    count_ ++;
    delete node;
}

void Bucket::resetCount(){
    count_ = 0;
}

bool Bucket::searchVisited(int id, int &length){
    for(int i = 0 ; i < count_ ; i++){
        if(bucket_[i].id_ == id){
            length = bucket_[i].length_;
            return true;
        }
    }
    length = 0;
    return false;
}

Hashtable::Hashtable() {
    size_ = HASH; 
    count_ = HASH;
    value_ = HASH;
    array_ = (Bucket*) malloc(sizeof(Bucket) * size_);
    for(int i = 0; i < size_ ; i++){
        Bucket *buck = new Bucket();
        memcpy(&array_[i], buck, sizeof(Bucket));
        delete buck;
    }

}

Hashtable::Hashtable(int size) {
    size_ = size; 
    count_ = size;
    value_ = size_;
    array_ = (Bucket*) malloc(sizeof(Bucket) * size_);
    for(int i = 0; i < size_ ; i++){
        Bucket *buck = new Bucket();
        memcpy(&array_[i], buck, sizeof(Bucket));
        delete buck;
    }
}

Hashtable::~Hashtable() {
    free(array_);
}

int Hashtable::allocnewBucket() {
    if(count_ + 1 > size_){
        int oldSize = size_;
        size_ = 2 * size_;
        array_ = (Bucket *) realloc(array_, sizeof(Bucket) * size_);
    }
    count_ ++;
    Bucket *buck = new Bucket();
    memcpy(&array_[count_-1], buck, sizeof(Bucket));
    delete buck;
    return count_ - 1;
}

void Hashtable::addVisited(int id, int length) {
    int hash = id % value_;
    if(array_[hash].count_ == 0)
        array_[hash].lastUsed_ = hash;
    int lastUsed = array_[hash].lastUsed_;
    if(array_[lastUsed].count_ + 1 > BUCKET){
        int newBucket = allocnewBucket();
        array_[hash].lastUsed_ = newBucket;
        array_[lastUsed].nextBucket_ = newBucket;
        lastUsed = newBucket;
    }
    array_[lastUsed].add(id, length);
}

bool Hashtable::searchVisited(int id, int &length_) {
    int hash = id % value_;
    int index = hash;
    bool flag = false;
    while((flag = array_[index].searchVisited(id, length_)) == false){
        if(array_[index].nextBucket_ >= 0)
            index = array_[index].nextBucket_;
        else 
            break;
    }
    return flag;
}

void Hashtable::reset(){
    for(int i=0 ; i < size_ ; i++){
        array_[i].resetCount();
    }
    count_ = HASH;
}
