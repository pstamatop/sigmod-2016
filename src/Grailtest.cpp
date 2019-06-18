#include <iostream>

#include "Grail.h"

using namespace std;

int main() {
    Grail grail;
    // cout << "Grail index created" << endl;
    // grail.init(5);
    // grail.setRank(1, 2);
    // grail.setMinRank(1, 3);
    // grail.setRank(2, 3);
    // grail.setMinRank(2, 4);
    // grail.setRank(3, 4);
    // grail.setMinRank(3, 5);
    // grail.setRank(4, 5);
    // grail.setMinRank(4, 6);
    // grail.setRank(5, 6);
    // grail.setMinRank(5, 7);

    // cout << grail.getRank(0,1) << endl;
    // cout << grail.getMinRank(0,1) << endl;
    // cout << grail.getRank(0,2) << endl;
    // cout << grail.getMinRank(0,2) << endl;
    // cout << grail.getRank(0,3) << endl;
    // cout << grail.getMinRank(0,3) << endl;
    // cout << grail.getRank(0,4) << endl;
    // cout << grail.getMinRank(0,4) << endl;
    // cout << grail.getRank(0,5) << endl;
    // cout << grail.getMinRank(0,5) << endl;

    // Hypergraph hyperg;
    // Stack stack1, stack2;
    // Visited Visited;
    // hyperg.insertEdge(1,2);
    // hyperg.insertEdge(7,2);
    // hyperg.insertEdge(1,3);
    // hyperg.insertEdge(2,4);
    // hyperg.insertEdge(2,5);
    // hyperg.insertEdge(4,5);
    // hyperg.insertEdge(3,6);
    // grail.init(7);
    // grail.constrIndex(hyperg, stack1);

    // if(grail.pathExists(1, 3) == NO) //maybe
    //  cout << "NO" << endl;
    // else
    //  cout << "MAYBE" << endl;


    // if(grail.pathExists(6, 5) == NO) //no
    //  cout << "NO" << endl;
    // else
    //  cout << "MAYBE" << endl;

    // if(grail.pathExists(1, 4) == NO) //maybe
    //  cout << "NO" << endl;
    // else
    //  cout << "MAYBE" << endl;

    // if(grail.pathExists(5, 1) == NO) //no
    //  cout << "NO" << endl;
    // else
    //  cout << "MAYBE" << endl;

    Hypergraph hyperg;
    Stack stack1, stack2;
    Visited visited;
    hyperg.insertEdge(1, 2);
    hyperg.insertEdge(2, 3);
    hyperg.insertEdge(2, 4);
    hyperg.insertEdge(4, 7);
    hyperg.insertEdge(4, 3);
    hyperg.insertEdge(7, 5);
    hyperg.insertEdge(5, 6);
    hyperg.insertEdge(3, 6);
    hyperg.insertEdge(3, 5);
    hyperg.insertEdge(6, 8);
    visited.init(9);
    grail.init(8);

    cout << "here" << endl;

    grail.constrIndex(hyperg, stack1);

    cout << endl << endl << "1 2 : ";
    if(grail.pathExists(1, 2) == NO) //maybe
        cout << "NO" << endl;
    else
        cout << "MAYBE" << endl;

    cout << endl << "4 8 : ";
    if(grail.pathExists(4, 8) == NO)//maybe
        cout << "NO" << endl;
    else
        cout << "MAYBE" << endl;

    cout << endl << "6 4 : ";
    if(grail.pathExists(6, 4) == NO)//no
        cout << "NO" << endl;
    else
        cout << "MAYBE" << endl;

    cout << endl << "7 6 : ";
    if(grail.pathExists(7, 6) == NO)//maybe
        cout << "NO" << endl;
    else
        cout << "MAYBE" << endl;
    
    cout << endl << "4 5 : ";
    if(grail.pathExists(4, 5) == NO)//maybe
        cout << "NO" << endl;
    else
        cout << "MAYBE" << endl;
    cout << endl << "4 3 : ";
    if(grail.pathExists(4, 3) == NO)//maybe
        cout << "NO" << endl;
    else
        cout << "MAYBE" << endl;
    cout << endl << "3 4 : ";
    if(grail.pathExists(3, 4) == NO)//no
        cout << "NO" << endl;
    else
        cout << "MAYBE" << endl;
    cout << endl << "1 8 : ";
    if(grail.pathExists(1, 8) == NO)//maybe
        cout << "NO" << endl;
    else
        cout << "MAYBE" << endl;
    cout << endl << "3 7 : ";
    if(grail.pathExists(3, 7) == NO)//no
        cout << "NO" << endl;
    else
        cout << "MAYBE" << endl;
}