#include <iostream>

#include "Hypergraph.h"

using namespace std;

int main() {
    Hypergraph hyperg;
    cout << "Hypergraph created" << endl;
    Stack stack;
    Hashtable hash;
    hyperg.insertEdge(1,2);
    hyperg.insertEdge(1,3);
    hyperg.insertEdge(1,4);
    hyperg.insertEdge(4,5);
    hyperg.insertEdge(5,6);

    hyperg.insertEdge(7, 3);
    if(hyperg.DFS(7,1,stack,hash))
        cout << "there is a path" << endl;
    else
        cout << "Nope" << endl;

    if(hyperg.DFS(3,1,stack,hash))
        cout << "there is a path" << endl;
    else
        cout << "Nope" << endl;

    if(hyperg.DFS(1,6,stack,hash))
        cout << "there is a path" << endl;
    else
        cout << "Nope" << endl;
}