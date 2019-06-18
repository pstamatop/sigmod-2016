#ifndef STACK_H
#define STACK_H

#include "sizes.h"

struct StackNode {
    int id_;
    StackNode(int);
};

class Stack {
public:
    Stack();
    ~Stack();
    void push(int);
    int pop();
    int getCount();
    void initArray(int);
    bool search(int);
    void reset();
    void getNode(int, int &);
    void setNode(int);
    int getTop();
private:
    StackNode *array_;
    int size_;
    int count_;
    int top_;
};

#endif // QUEUE_H
