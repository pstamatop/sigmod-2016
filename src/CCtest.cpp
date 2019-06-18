#include <iostream>

#include "CC.h"

using namespace std;

int main() {
    bool direct;
    CC comp(10);
    // UpdateIndex ui;  //testing for updateIndex structure
    // ui.addPair(3,5); //before using this segment place updateIndex in CC'c public section
    // ui.addPair(5,6);
    // ui.addPair(6,7);
    // ui.addPair(7,8);
    // ui.addPair(8,9);
    // ui.addPair(3,9);
    // ui.addPair(8,9);
    // ui.addPair(7,8);
    // ui.addPair(6,7);
    // ui.addPair(5,6);
    // ui.addPair(3,5);

    // comp.updateIndex_.addPair(7,8);
    // comp.updateIndex_.addPair(3,5);
    // comp.updateIndex_.addPair(6,7);
    // comp.updateIndex_.addPair(5,6);
    // comp.updateIndex_.addPair(8,9);
    // // comp.updateIndex_.addPair(3,9);

    // if(comp.updateIndex_.inPair(9,3,direct))
    //  cout << "Yep" << endl;
    // else
    //  cout << "Nope" << endl;

    // if(direct == true)
    //  cout << "direct" << endl;
    // else
    //  cout << "not direct" << endl;

    comp.insertCC(6, 3, true);
    comp.insertCC(3, 5, true);
    comp.insertCC(4, 6, true);
    comp.insertCC(1, 7, true);  //Insert node id's with their components
    comp.insertCC(2, 8, true);
    comp.insertCC(5, 9, true);
    comp.insertCC(10, 10, true);

    // comp.initUpdate();
    // comp.insertNewEdge(2, 1);    //Add the edges
    // comp.insertNewEdge(6, 3);
    // comp.insertNewEdge(4, 1);
    // comp.insertNewEdge(3, 4);
    // comp.insertNewEdge(2, 5);

    // comp.initUpdate();
    // comp.insertNewEdge(4, 1);
    // comp.insertNewEdge(6, 3);
    // comp.insertNewEdge(2, 1);    //Add the edges
    // comp.insertNewEdge(3, 4);
    // comp.insertNewEdge(2, 5);

    // comp.initUpdate();
    // comp.insertNewEdge(4, 1);
    // comp.insertNewEdge(6, 3);
    // comp.insertNewEdge(2, 1);    //Add the edges
    // comp.insertNewEdge(3, 4);
    // comp.insertNewEdge(2, 5);

    comp.initUpdate();
    comp.insertNewEdge(0, 6, 3); //3 5
    comp.insertNewEdge(0, 2, 5); //8 9
    comp.insertNewEdge(0, 3, 4);//5 6
    comp.insertNewEdge(0, 2, 1);    //8 7    //Add the edges
    comp.insertNewEdge(0, 4, 1); //6 7
    comp.insertNewEdge(0, 15, 17); //-1 -1 
    comp.insertNewEdge(0, 2, 16);

    // comp.initUpdate();
    // comp.insertNewEdge(2, 5);
    // comp.insertNewEdge(1, 2);
    // comp.insertNewEdge(4, 1);
    // comp.insertNewEdge(3, 4);
    // comp.insertNewEdge(6, 3);

    if(comp.areConnected(0, 6, 5)){ //3 9//Check if the nodes are weakly connected
        cout << "Yep" << endl;
    }
    else
        cout << "Nope" << endl;

    if(comp.areConnected(0, 15, 17)){   //Check if the nodes are weakly connected
        cout << "Yep" << endl;
    }
    else
        cout << "Nope" << endl;

    if(comp.areConnected(0, 2, 16)){    //Check if the nodes are weakly connected
        cout << "Yep" << endl;
    }
    else
        cout << "Nope" << endl;
     // cout << comp.searchCC(4) << endl;
     // cout << comp.searchCC(6) << endl;
}