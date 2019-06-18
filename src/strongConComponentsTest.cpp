#include <iostream>
#include "Graph.h"
#include "Stack.h"
#include "Hashtable.h"

#include <fstream>


using namespace std;

int main(){
    SGraph graph;
    Stack successors;
    graph.createSCC(15);
    graph.insertEdge(1, 2);
    graph.insertEdge(2, 4);
    graph.insertEdge(4, 1);
    graph.insertEdge(4, 3);
    graph.insertEdge(3, 1);
    graph.insertEdge(6, 4);
    graph.insertEdge(5, 6);
    graph.insertEdge(5, 3);
    graph.insertEdge(6, 5);
    graph.insertEdge(7, 5);
    graph.insertEdge(6, 8);
    graph.insertEdge(7, 9);

    graph.insertEdge(10, 11);
    graph.insertEdge(11, 12);
    graph.insertEdge(12, 10);



    graph.estimateStronglyConnectedComponents(successors); //should be 4


    // if(graph.wcomponents_.areConnected(10, 9)){  //Check if the nodes are weakly connected
    //  cout << "Yep" << endl;
    // }
    // else
    //  cout << "Nope" << endl;
    
    // Insert Edge after costructing CCs
    // graph.insertEdge(1, 10);
    // graph.wcomponents_.insertNewEdge(1, 10);

    //  if(graph.wcomponents_.areConnected(10, 9)){ //Check if the nodes are weakly connected
    //      cout << "Yep" << endl;
    //  }
    //  else
    //      cout << "Nope" << endl;
}
