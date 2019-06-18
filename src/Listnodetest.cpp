#include <iostream>
#include "ListNode.h"

using namespace std;

//NEIGHBORS 5

int main(){
    SListNode node[2]; //Array of two ListNodes, second node works as an extension of the first one
    int edge = -1, index = -1;
    for(int i=0 ; i<3 ; i++){ //Insertion of 3 edges
        cout << "Type edge: ";
        cin >> edge;
        node[0].addEdge(edge);
        node[0].setTotalNodeCount();
        cout << endl;
    }
    cout << "Count of node 0: " << node[0].getCount() << endl;
    cout << "Next list node of node 0 is: " << node[0].getNextListNode() << endl;
    cout << "Total count of node 0 is: " << node[0].getTotalNodeCount() << endl;
    cout << "Type position: ";
    cin >> edge;
    cout << endl;
    cout << "Neighbor in this position is: " << node[0].getNeighbor(index) << endl;
    for(int i=0; i<3 ; i++){
        cout << "Type edge: ";
        cin >> edge;
        cout << endl;
        if(node[0].addEdge(edge))
            node[0].setTotalNodeCount();
        else
            cout << "No space." << endl;
    }
    cout << "Count of node 0: " << node[0].getCount() << endl;
    cout << "Next list node of node 0 is: " << node[0].getNextListNode() << endl;
    cout << "Total count of node 0 is: " << node[0].getTotalNodeCount() << endl;
    for(int i=0 ; i<5 ; i++){
        cout << "Type edge: ";
        cin >> edge;
        cout << endl;
        if(node[1].addEdge(edge))
            node[0].setTotalNodeCount();
        else
            cout << "No space" << endl;
    }
    node[0].addNextListNode(1); //Connecting the two nodes
    cout << "Count of node 0: " << node[0].getCount() << endl;
    cout << "Count of node 1: " << node[1].getCount() << endl;
    cout << "Next list node of node 0 is: " << node[0].getNextListNode() << endl;
    cout << "Total count of node 0 is: " << node[0].getTotalNodeCount() << endl;
}