#include <iostream>

#include "SCC.h"

using namespace std;

int main() {
    int last = 0, cur = 0;
    SCC scc;
    scc.init(2);
    scc.addComponent(1, true);
    scc.addComponent(2, true);
    scc.addComponent(1, true);
    scc.addNode(3, 1);
    scc.addNode(4, 1);
    scc.addNode(5, 1);
    scc.addNode(6, 1);
    scc.addNode(7, 2);
    scc.addNode(8, 2);
    scc.addNode(9, 1);
    scc.addNode(10, 2);
    int comp = scc.searchComponent(1);
    int count = scc.getTotalIncludedNodes(comp);
    for(int i = 0 ; i < count ; i++) {
        cout << "node " << scc.getNode(comp, i, last , cur) << endl;
    }
    cout << endl;
    comp = scc.searchComponent(2);
    count = scc.getTotalIncludedNodes(comp);
    for(int i = 0 ; i < count ; i++) {
        cout << "node " << scc.getNode(comp, i, last , cur) << endl;
    }
    // if(scc.addNode(3,1))
    //  cout << "ok" << endl;
    // else
    //  cout << "nope" << endl;
    // if(scc.addNode(4,1))
    //  cout << "ok" << endl;
    // else
    //  cout << "nope" << endl;
    // if(scc.addNode(5,5))
    //  cout << "meh" << endl;
    // else
    //  cout << "doesn t exist" << endl;
    // cout << scc.getTotalIncludedNodes(2) << endl;
    // cout << scc.getTotalIncludedNodes(1) << endl;

    // if(scc.addNode(5,1))
    //  cout << "ok" << endl;
    // else
    //  cout << "nope" << endl;

    // if(scc.addNode(6,1))
    //  cout << "ok" << endl;
    // else
    //  cout << "nope" << endl;

    // cout << "Nodes of comp 1 : " ;
    // scc.printCompNodes(1);
    // cout << endl;

    // if(scc.addNode(11,2))
    //  cout << "ok" << endl;
    // else
    //  cout << "nope" << endl;

    // if(scc.addNode(12,2))
    //  cout << "ok" << endl;
    // else
    //  cout << "nope" << endl;

    // cout << "Nodes of comp 1 : " ;
    // scc.printCompNodes(1);
    // cout << endl;

    // cout << "Nodes of comp 1 : " ;
    // scc.printCompNodes(1);
    // cout << endl;
    // cout << "Nodes of comp 2 : " ;
    // scc.printCompNodes(2);
    // cout << endl;
    // cout << "Nodes of comp 5 : " ;
    // scc.printCompNodes(5);
    // cout << endl;

    // cout << "Total count is " << scc.getCount() << endl;

}