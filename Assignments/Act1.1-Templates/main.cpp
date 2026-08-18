#include <iostream>
#include "list.h"
using namespace std;

int main() {
    List<int> myList;
    myList.insert(5);
    myList.insert(10);
    myList.insert(15);
    myList.print();
    cout << "Max: " << myList.getMax() << endl;
    myList.removeAt(1);
    myList.print();
    myList.removeLast();
    myList.print();
    cout << "Size: " << myList.getSize() << endl;
    cout << "Data en pos 0: " << myList.getData(0) << endl;
    myList.insertAt(0, 99);
    myList.print();
    return 0;
}