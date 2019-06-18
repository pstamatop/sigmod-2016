#include <cstdlib>
#include <cstring>

#include "Stack.h"

StackNode::StackNode(int id){
    id_ = id;
}

Stack::Stack() {
    count_ = 0;
    size_ = STACK;
    top_ = 0;
    array_ = (StackNode*) malloc(sizeof(StackNode) * size_);
}

Stack::~Stack() {
    free(array_);
}

void Stack::push(int id) {
    if(count_ + 1 <= size_){
        StackNode *node = new StackNode(id);
        memcpy(&array_[top_], node, sizeof(StackNode));
        delete node;
        top_++;
    }
    else{
        size_ *= 2;
        array_ = (StackNode*) realloc(array_, sizeof(StackNode) * size_);
        StackNode *node = new StackNode(id);
        memcpy(&array_[top_], node, sizeof(StackNode));
        delete node;
        top_++;
    }
    count_++;
}

int Stack::pop() {
    if(count_ == 0) 
        return -1;
    int rem = array_[top_-1].id_;
    top_ --;
    count_ --;
    return rem;
}

int Stack::getCount() {
    return count_;
}

void Stack::reset() {
    count_ = 0;
    top_ = 0;
}

void Stack::getNode(int index, int &id) {
    if(index < count_)
        id = array_[index].id_;
    else
        id = -1;
}

int Stack::getTop() {
    return top_-1;
}
