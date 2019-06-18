#include <iostream>
#include <cstdlib>

#include "Graph.h"

using namespace std;

int main(){
    DGraph graph;
    Queue queueStart, queueEnd;
    graph.insertEdge(1,2,0);
    graph.insertEdge(1,3,0);
    graph.insertEdge(1,4,0);
    graph.insertEdge(4,5,0);
    graph.insertEdge(5,6,0);
    Visited visitedStart, visitedEnd;
    int maxSize = graph.getMaxIndexSize();
    visitedStart.init(maxSize);
    visitedEnd.init(maxSize);
    int *levelStart = (int *) malloc(maxSize * sizeof(int));
    int *levelEnd = (int *) malloc(maxSize * sizeof(int));
    cout << "Shortest distance from 1 to 6: " << graph.bidirectionalBFS(1, 6 , queueStart, queueEnd, visitedStart, visitedEnd, levelStart, levelEnd, 1, 0) << endl;
    graph.insertEdge(2,6,0);
    cout << "Shortest distance from 1 to 6 (after inserting edge): " << graph.bidirectionalBFS(1, 6, queueStart, queueEnd, visitedStart, visitedEnd, levelStart, levelEnd, 2, 0) << endl;
    free(levelStart);
    free(levelEnd);
}