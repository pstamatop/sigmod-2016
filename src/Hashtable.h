#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "sizes.h"

struct BNode{
    int id_;
    int length_;
    BNode();
};

struct Bucket {
    BNode bucket_[BUCKET];
    int count_;
    int nextBucket_;
    int lastUsed_; //updated only in the head bucket
    Bucket();
    void add(int, int);
    bool searchVisited(int, int &);
    void resetCount();
};

class Hashtable{
public:
    Hashtable();
    Hashtable(int);
    ~Hashtable();
    void addVisited(int, int);
    int allocnewBucket();
    bool searchVisited(int, int &);
    void reset();
private:
    int value_;
    int size_;
    int count_;
    Bucket *array_;
};

#endif // HASHTABLE_H
