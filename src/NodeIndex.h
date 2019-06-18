#ifndef NODEINDEX_H
#define NODEINDEX_H

#include "sizes.h"

class NodeIndex{
public:
    NodeIndex();
    ~NodeIndex();
    void insertNode(int, int);
    int getListHead(int);
    void initArray(int, int);
    bool searchNode(int);
    int getSize();
    int *array_;
    int size_; //allocated size
    int count_; //number of used cells
};

#endif // NODEINDEX_H