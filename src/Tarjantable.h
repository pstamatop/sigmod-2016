#ifndef TARJANTABLE_H
#define TARJANTABLE_H

struct TarjanNode{
    int index_;
    int lowlink_;
    int parent_;
    int iterator_;
    int last_; //used for getNeighbor
    int getN_; //used fot getNeighbor
};

class TarjanTable{
public:
    TarjanTable();
    ~TarjanTable();
    void tarjanTableInit(int);
    void setNode(int, int, int);
    void incrIterator(int);
    int getIterator(int);
    int getParent(int);
    int getIndex(int);
    int getLowlink(int);
    void setLowlink(int, int);
    int& getLast(int);
    int& getN(int);
private:
    int size_;
    TarjanNode *tarjanNodes_;
};

#endif // TARJANTABLE_H