#include <cstdlib>
#include <cstring>
#include <iostream>

#include "Queue.h"


using namespace std;
//Implementation of an array-queue that doubles its size when there is no space

Queue::Queue(){
    count_ = 0;
    cursize_ = 0;
    size_ = QUEUE;
    front_ = 0;
    rear_ = 0;
    array_ = (QueueNode*) malloc(sizeof(QueueNode) * size_);
    for(int i = 0; i < size_; i++){
        QueueNode *node = new QueueNode();
        memcpy(&array_[i], node, sizeof(QueueNode));
        delete node;
        array_[i].id = -1;
        array_[i].length = -1;
    }
}

Queue::~Queue(){
    free(array_);
}

void Queue::enqueue(int id, int length){
    if(cursize_ + 1 <= size_){
        array_[rear_].id = id;
        array_[rear_].length = length;
        rear_ = rear_ + 1;
    }
    else{
        int initSize = size_;
        size_ = size_ * 2;
        array_ = (QueueNode*) realloc(array_, sizeof(QueueNode) * size_);
        for(int i = initSize; i < size_; i++){
            QueueNode *node = new QueueNode();
            memcpy(&array_[i], node, sizeof(QueueNode));
            delete node;
            array_[i].id = -1;
            array_[i].length = -1;
        }
        array_[rear_].id = id;
        array_[rear_].length = length;
        rear_ = rear_ + 1;
    }
    cursize_++;
    count_++;
}

int Queue::dequeue() {
    if(count_ == 0) return -1;
    int temp = array_[front_].id;
    array_[front_].id = -1;
    array_[front_].length = -1;
    front_ = front_ + 1;
    count_--;
    return temp;
}

int Queue::getCount() {
    return count_;
}

int Queue::peekFrontLength(){
    return array_[front_].length;
}

int Queue::peekFrontId(){
    return array_[front_].id;
}

bool Queue::search(int id, int &length){
    if(count_ == 0)
        return false;
    for(int i = 0 ; i < cursize_ ; i++){
        if(array_[i].id == id){
            length = array_[i].length;
            return true;
        }
    }
    return false;
}

void Queue::reset(){
    cursize_ = 0;
    count_ = 0;
    front_ = 0;
    rear_ = 0;
}