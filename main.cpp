#include <iostream>
#include "LList.h"

int main() {
    LList parth(5);
    parth.append(5);
//    parth->append(5);
    parth.print();
    cout << parth.size << endl;
    LList rujuta;
    rujuta.copy_from(&parth);
    cout << endl;
    cout << endl;
    rujuta.print();
    cout << rujuta.size << endl;
    rujuta.clear();
    rujuta.append(4);
    cout << endl;
    cout << endl;
    rujuta.append(5);
    rujuta.print();
    cout << rujuta.size << endl;
    return 0;
}
