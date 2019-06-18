#ifndef GRAIL_H
#define GRAIL_H

#include "Visited.h"
#include "sizes.h"
#include "Hypergraph.h"
#include "Stack.h"
#include "Hashtable.h"

struct GrailNode {
    int min_rank;
    int rank;
    int parent;
    int iterator;
    int last;
    int getN;
    GrailNode();
    bool visited();
};

class Grail {
public:
    Grail();
    ~Grail();
    void init(int); // allocates the space that is needed depending to the number of existing SCCs
    void constrIndex(Hypergraph &, Stack &);
    int pathExists(int, int);
    void setRank(int, int, int); //only for testing
    void setMinRank(int, int, int);
    int getRank(int, int);
    int getMinRank(int, int);
    void setNode(int, int, int, int);
    void incrIterator(int, int);
    int getIterator(int, int);
    int getParent(int, int);
    int& getLast(int, int);
    int& getN(int, int);
    bool visited(int, int);
    void setShuffledComps(int, int);
    void shuffleArray(int *, int);
private:
    GrailNode *grailIndex_[GRAIL];
    int *shuffledComps_;
    int count_; //number of SCCs in the grail index
};


#endif