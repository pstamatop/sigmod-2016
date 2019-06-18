#include <iostream>

#include "CC.h"

using namespace std;

//define VERSIONS = 2 to test this properly

int main() {
    CC wcomponents;
    int version = 0;
    // wcomponents.insertNewEdge(0, 6, 7);
    wcomponents.insertCC(1, 1, true);
    wcomponents.insertCC(2, 2, true);
    wcomponents.insertCC(3, 3, true);
    wcomponents.insertCC(4, 4, true);
    wcomponents.insertCC(5, 5, true);
    wcomponents.setLastComponent(5);
    wcomponents.initUpdate();
    // wcomponents.insertCC(6, 6, true);
    wcomponents.insertNewEdge(version, 1, 2);
    wcomponents.insertNewEdge(version, 2, 3);
    // if(wcomponents.areConnected(version, 1, 3))
    //  cout << "yeap" << endl;
    // else
    //  cout << "nope" << endl;
    version++;
    wcomponents.newVersion(version);
    wcomponents.insertNewEdge(version, 1, 4);
    wcomponents.insertNewEdge(version, 5, 6);
    // if(wcomponents.areConnected(version, 1, 2))
    //  cout << "yeap" << endl;
    // else
    //  cout << "nope" << endl;
    // if(wcomponents.areConnected(version, 2, 3))
    //  cout << "yeap" << endl;
    // else
    //  cout << "nope" << endl;
    // if(wcomponents.areConnected(version, 1, 3))
    //  cout << "yeap" << endl;
    // else
    //  cout << "nope" << endl;
    // if(wcomponents.areConnected(version, 1, 4))
    //  cout << "yeap" << endl;
    // else
    //  cout << "nope" << endl;
    // if(wcomponents.areConnected(version, 5, 6))
    //  cout << "yeap" << endl;
    // else
    //  cout << "nope" << endl;
    version++;
    wcomponents.newVersion(version);
    // if(wcomponents.areConnected(version, 1, 2))
    //  cout << "yeap" << endl;
    // else
    //  cout << "nope" << endl;
    // if(wcomponents.areConnected(version, 2, 3))
    //  cout << "yeap" << endl;
    // else
    //  cout << "nope" << endl;
    // if(wcomponents.areConnected(version, 1, 3))
    //  cout << "yeap" << endl;
    // else
    //  cout << "nope" << endl;
    version++;
    wcomponents.newVersion(version);
    // if(wcomponents.areConnected(version, 1, 2))
    //  cout << "yeap" << endl;
    // else
    //  cout << "nope" << endl;
    // if(wcomponents.areConnected(version, 2, 3))
    //  cout << "yeap" << endl;
    // else
    //  cout << "nope" << endl;
    // if(wcomponents.areConnected(version, 1, 3))
    //  cout << "yeap" << endl;
    // else
    //  cout << "nope" << endl;







    // if(wcomponents.areConnected(0, 1, 3))
    //  cout << "yeap" << endl;
    // else
    //  cout << "nope" << endl;
    // // wcomponents.insertNewEdge(0, 2, 3);
    // if(wcomponents.areConnected(0, 3, 4))
    //  cout << "yeap" << endl;
    // else
    //  cout << "nope" << endl;
    // wcomponents.newVersion(1);
    // wcomponents.insertNewEdge(1, 3, 4);
    // // wcomponents.newVersion(2);
    // if(wcomponents.areConnected(1, 3, 4))
    //  cout << "yeap" << endl;
    // else
    //  cout << "nope" << endl;
    // if(wcomponents.areConnected(0, 3, 4))
    //  cout << "yeap" << endl;
    // else
    //  cout << "nope" << endl;
    // wcomponents.newVersion(2);
    // if(wcomponents.areConnected(2, 1, 3))
    //  cout << "yeap" << endl;
    // else
    //  cout << "nope" << endl;
    // wcomponents.insertCC(5, 5, true);
    // wcomponents.insertCC(6, 6, true);
    // wcomponents.insertNewEdge(2, 5, 1);
    // if(wcomponents.areConnected(0, 5, 1))
    //  cout << "yeap" << endl;
    // else
    //  cout << "nope" << endl;
    // if(wcomponents.areConnected(2, 5, 1))
    //  cout << "yeap" << endl;
    // else
    //  cout << "nope" << endl;
    // wcomponents.insertCC(7, 7, true);
    // wcomponents.rebuildIndexes();
    // if(wcomponents.areConnected(0, 5, 1)) //checks if last version is now the first after the end of the batch
    //  cout << "yeap" << endl;
    // else
    //  cout << "nope" << endl;
    // wcomponents.newVersion(1);
    // wcomponents.insertNewEdge(1, 8, 9);
    // if(wcomponents.areConnected(0, 5, 1)) //checks if last version is now the first after the end of the batch
    //  cout << "yeap" << endl;
    // else
    //  cout << "nope" << endl;
    // if(wcomponents.areConnected(2, 5, 1)) //checks if last version is now the first after the end of the batch
    //  cout << "yeap" << endl;
    // else
    //  cout << "nope" << endl;
}