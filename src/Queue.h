#ifndef QUEUE_H
#define QUEUE_H

#include "sizes.h"

struct QueueNode {
    int id;
    int length;
};

class Queue {
public:
    Queue();
    ~Queue();
    void enqueue(int, int);
    int dequeue();
    int getCount();
    int peekFrontLength();
    int peekFrontId();
    bool search(int, int &);
    void reset();
private:
    QueueNode *array_;
    int size_;
    int cursize_;
    int count_;
    int front_;
    int rear_;
};

#endif // QUEUE_H