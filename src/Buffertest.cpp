#include <iostream>
#include "Buffer.h"

using namespace std;

//NEIGHBORS 1
//Make ListNode private members public to run this

int main(){
    SBuffer buff;
    int index = -1;
    index = buff.allocNewNode();
    cout << "Index of allocated ListNode:" << index << endl;
    cout << "Total node count of allocated ListNode: " << buff.buffer_[0].getTotalNodeCount() << endl;
    buff.addEdge(0, 1);
    cout << "Total node count of ListNode 0: " << buff.buffer_[0].getTotalNodeCount() << endl;
    buff.addEdge(0, 2);
    cout << "Total node count of ListNode 0: " << buff.buffer_[0].getTotalNodeCount() << endl;
    buff.addEdge(0, 3);
    cout << "Total node count of ListNode 0: " << buff.buffer_[0].getTotalNodeCount() << endl;
    cout << "LastUsed of ListNode 0: " << buff.buffer_[0].getLastUsed() << endl;
    cout << "NextListNode of ListNode 0" << buff.buffer_[0].getNextListNode() << endl;
    if(buff.searchNeighbor(0, 2))
        cout << "Found 2." << endl;
    buff.addEdge(0, 4);
    buff.addEdge(0, 5);
    buff.addEdge(0, 6);
    buff.addEdge(0, 7);
    buff.addEdge(0, 8);
    buff.addEdge(0, 9);
    int index3 = 0;
    for(int i=0 ; i<8 ; i++){
        index3 = buff.buffer_[index3].getNextListNode();
        cout << "Index of NextListNode: " << index3 << endl;
    }
    int count = buff.buffer_[0].getTotalNodeCount();
    cout << "Total node count of ListNode 0: " << buff.buffer_[0].getTotalNodeCount() << endl;
    cout << "Total node count of ListNode 0: " << buff.buffer_[0].getLastUsed() << endl;
    // cout << "Neighbor in position 0 in node 0" << buff.getNeighbor(0, 0) << endl;
    int last = -1;
    cout << endl << endl;
    for(int i = 0 ; i < count ; i++){
        cout << buff.getNeighbor(index, i , last) << endl;
    }
}
