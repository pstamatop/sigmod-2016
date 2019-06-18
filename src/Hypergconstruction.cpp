#include <iostream>

#include "Graph.h"

using namespace std;

int main() {
    SGraph graph;
    graph.insertEdge(1, 3);
    graph.insertEdge(3, 2);
    graph.insertEdge(2, 1);
    graph.insertEdge(3, 4);

    graph.createSCC(2);
    graph.addSCC(1);
    graph.addSCC(2);
    graph.addNodeSCC(1, 1);
    graph.addNodeSCC(2, 1);
    graph.addNodeSCC(3, 1);
    graph.addNodeSCC(4, 2);

    // int scccount = scomponents_.getCompCount();
    // vis.init(scccount+1);

    int scccount = graph.getCompCount();
    graph.visitedInit(scccount+1);

    graph.createHypergraph();
}   