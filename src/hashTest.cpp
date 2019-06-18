#include <iostream>

#include "Hashtable.h"

using namespace std;

int main(){
    Hashtable hash;
    hash.addVisited(23, 1);
    hash.addVisited(20, 2);
    hash.addVisited(33, 3);
    hash.addVisited(30, 4);
    hash.addVisited(31, 5);
    hash.addVisited(44, 6);
    hash.addVisited(42, 7);
    hash.addVisited(22, 8);
    hash.addVisited(21, 9);
    hash.addVisited(29, 10);
    hash.addVisited(39, 11);
    hash.addVisited(28, 12);
    hash.addVisited(41, 13);
    hash.addVisited(51, 13);
    hash.addVisited(61, 13);
    // hash.printHashtable();
    int level = -1;
    cout << hash.searchVisited(2, level) << endl;
    cout << "level of 2 = "<< level << endl;;
    cout << hash.searchVisited(42, level) << endl;
    cout << "level of 42 = "<< level << endl;
}