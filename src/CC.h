#ifndef CC_H
#define CC_H

#include "sizes.h"

class UpdateIndex {
public:
    UpdateIndex();
    ~UpdateIndex();
    void init(int);
    void addPair(int, int, int);
    bool inPair(int, int, int);
    void reset();
    void setLastComponent(int);
    void initArray(int, int, int);
    void expandVersion(int);
    void expandWhole();
    void endBatch(int);
private:
    int **updateTable_;
    int *count_;
    int *size_;
    int currentNum_;
    int lastComponent_;
    int maxVersions_;
    int versions_;
    int versionsCreated_;
    int pastVersions_;
};

class CC {
public:
    CC();
    CC(int);
    ~CC();
    void init(int);
    void insertCC(int, int, bool);
    int searchCC(int);
    void insertNewEdge(int, int, int);
    bool areConnected(int, int, int);
    bool rebuildIndexes(int);
    int getCount();
    int getSize();
    int getComponent(int);
    void setLastComponent(int);
    void initArray(int, int);
    void initUpdate();
    void newVersion(int);
private:
    UpdateIndex updateIndex_;
    int *ccIndex_;
    int count_;
    int size_;
    float metric_;
    int succ_queries_;
    int queries_;
    int lastComponent_;
};

#endif