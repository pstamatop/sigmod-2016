#ifndef SCC_H
#define SCC_H

#include "NodeIndex.h"
#include "sizes.h"

struct ComponentCursor{
    int index; // current component index
    ComponentCursor();
    void reset();
};

class Component {
public:
    Component(int);
    bool addNode(int);
    int getId();
    int getCount();
    int getSize(); //getters for unit testing
    void print(); //testing purposes only
    int getLastUsed();
    void setLastUsed(int);
    int getNextIndex();
    void setNextIndex(int);
    void incrTotalIncludedNodes();
    int getTotalIncludedNodes();
    int getNode(int);
private:
    int id_;
    int count_;
    int includedNodes_[COMPNODES];
    int totalIncludedNodes_;
    int size_;
    int nextIndex_;
    int lastUsed_;
};

class SCC {
public:
    SCC();
    ~SCC();
    void init(int);
    void addComponent(int, bool);
    int searchComponent(int); //returns an index
    bool addNode(int, int);
    int getCompCount();
    void printCompNodes(int); //testing purposes only
    int getCount();
    void iterateSCC(); //begin an iteration aka reset the cursor
    bool nextSSC(); // while in array bounds increment the cursor
    Component* getCurrentSCC();// get the current Component (the one that the component cursor points to)
    int belongsToComponent(int);
    int getNode(int, int, int&, int&);
    int getTotalIncludedNodes(int);
private:
    Component* components_;
    NodeIndex sccIndex_;
    ComponentCursor compCursor_;
    int compCount_;
    int count_;
    int* belongsToComponent_;
    int size_;
    int arraySize_;
};

#endif