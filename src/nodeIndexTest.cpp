#include <iostream>

#include "NodeIndex.h"

using namespace std;

int main(){
    NodeIndex index;
    //NODEINDEX = 5, 0-4

    index.insertNode(3, 10); // index[3] = 10
    index.insertNode(4, 11);

    cout << "GetListHead of 4 = " << index.getListHead(4) << endl;
    cout << "SearchNode for 3 returns " << index.searchNode(3) << endl;
    cout << "SearchNode for 7 returns " << index.searchNode(7) << endl;

    index.insertNode(7, 12);
    //NODEINDEX = 5, 0-4

    cout << "SearchNode for 7 after insertion returns " << index.searchNode(7) << endl;
    cout << "GetListHead of 7 = " << index.getListHead(7) << endl;

    cout << "GetListHead of 1 = " << index.getListHead(1) << endl;
    cout << "GetListHead of 1 = " << index.getListHead(9) << endl;
}