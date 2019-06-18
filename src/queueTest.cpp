#include <iostream>
#include "Queue.h"

using namespace std;

int main(){
    Queue queue;
    queue.enqueue(1, 100);
    queue.enqueue(3, 101);
    queue.enqueue(5, 102);
    queue.enqueue(7, 103);
    queue.enqueue(11, 104);
    queue.enqueue(15, 105);
    for(int i=0 ; i<3 ; i++){
        cout << "Dequeued: " << queue.dequeue() << endl;
    }
    queue.enqueue(20, 106);
    queue.enqueue(25, 107);
    queue.enqueue(30, 108);
    for(int i=0 ; i<6 ; i++){
        cout << "Dequeued: " << queue.dequeue() << endl;
    }
    queue.enqueue(45, 109);
    queue.enqueue(58, 110);
    queue.enqueue(60, 111);
    queue.enqueue(70, 106);
    queue.enqueue(80, 107);
    queue.enqueue(90, 108);
    queue.enqueue(100, 109);
    queue.enqueue(200, 110);
    queue.enqueue(300, 111);
    queue.enqueue(400, 106);
    queue.enqueue(500, 107);
    cout << endl << endl << endl << endl;
    for(int i=0 ; i<11 ; i++){
        cout << "Dequeued: " << queue.dequeue() << endl;
    }
}