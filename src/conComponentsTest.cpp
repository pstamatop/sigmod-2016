#include <iostream>
#include "Graph.h"
#include "Stack.h"
#include "Hashtable.h"

#include <fstream>


// using namespace std;

// int main(){
//  // Graph graph;
    // Stack stack;
    // Hashtable visited;
    // graph.insertEdge(0, 10);
    // graph.insertEdge(1, 2);
    // graph.insertEdge(1, 3);
    // graph.insertEdge(1, 4);
    // graph.insertEdge(3, 9);
    // graph.insertEdge(4, 5);
    // graph.insertEdge(4, 6);
    // graph.insertEdge(4, 8);
    // graph.insertEdge(8, 9);
    // graph.insertEdge(8, 1);
    // graph.insertEdge(5, 7);


    // // Another Component
    // graph.insertEdge(33, 34);


    // graph.estimateConnectedComponents(stack, visited);
    // graph.printConnectedComponents();

    // if(graph.wcomponents_.areConnected(10, 9)){  //Check if the nodes are weakly connected
    //  cout << "Yep" << endl;
    // }
    // else
    //  cout << "Nope" << endl;
    
    // // Insert Edge after costructing CCs
    // graph.insertEdge(1, 10);
    // graph.wcomponents_.insertNewEdge(1, 10);


    // // graph.estimateConnectedComponents(stack, visited);
    // graph.printConnectedComponents();
    // if(graph.wcomponents_.areConnected(10, 9)){  //Check if the nodes are weakly connected
    //  cout << "Yep" << endl;
    // }
    // else
    //  cout << "Nope" << endl;
// }

// #include <iostream>
// #include <fstream>

// #include "Graph.h"

#define MAX 100

using namespace std;

int main(int argc, char *argv[]){
    int id1, id2;
    char line[MAX],command;
    DGraph graph;
    Stack stack;
    Hashtable visited;
    ifstream input(argv[1]);
    ifstream workload(argv[2]);
    Queue queueStart, queueEnd;
    Hashtable hashStart, hashEnd;
    if(!input || !workload){
        cout << "Failed to open files" << endl;
        return -1;
    }
    while(input >> id1 >> id2){
        graph.insertEdge(id1, id2, 0);
    }
    // while(workload.getline(line,MAX)){
    //  sscanf(line, "%c", &command);
    //  if(command == 'F')
    //      continue;
    //  sscanf(line,"%c %d %d", &command, &id1, &id2);
    //  if(command == 'A'){
    //      graph.insertEdge(id1, id2);
    //  }
    //  else if(command == 'Q'){
    //      cout << graph.bidirectionalBFS(id1, id2, queueStart, queueEnd, hashStart, hashEnd) << endl; 
    //  }
    // }

    graph.estimateConnectedComponents(stack, 1);

    // cout << graph.bidirectionalBFS(19,6) << endl;
    //  graph.insertEdge(3, 15);
    //  graph.insertEdge(11, 1);
    // cout << graph.bidirectionalBFS(17,16) << endl;
    // cout << graph.bidirectionalBFS(8,16) << endl;
    // cout << graph.bidirectionalBFS(10,2) << endl;
    // cout << graph.bidirectionalBFS(14,7) << endl;
    // cout << graph.bidirectionalBFS(8,19) << endl;
    //  graph.insertEdge(8, 15);
    //  graph.insertEdge(9, 17);

    // graph.insertEdge(0, 3);
    // cout << "Insert edge 0-10" << endl;
    // graph.insertEdge(0, 10);
    // graph.insertEdge(0, 10);
    // cout << "Insert edge 0-11" << endl;
    // graph.insertEdge(0, 11);
    // cout << "Insert edge 12-10" << endl;
    // graph.insertEdge(12, 30);
    // graph.insertEdge(0,12);
    // graph.insertEdge(0,4);
    // graph.printNode(0);
    // graph.printNode(1);
}

