#include <iostream>

#include "Stack.h"

using namespace std;

//before using this unit test, change stack initial size to 2

int main() {
    Stack stack;
    int id, dummy = -1, dummy2 = -1;
    dummy = 0;
    cin >> id;
    stack.push(id);
    cin >> id;
    stack.push(id);
    cin >> id;
    stack.push(id);
    cin >> id;
    stack.push(id);
    cin >> id;
    stack.push(id);
    cout << stack.pop() << endl;
    cout << stack.pop() << endl;
    cout << stack.pop() << endl;
    cout << stack.pop() << endl;
    cout << stack.pop() << endl;
}
