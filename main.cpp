#include <iostream>
#include "LList.h"

int main() {
    LList parth(1);
    parth.append(2);
//    parth.print();
    LList rujuta;
    rujuta.copy_from(&parth);
    parth.append(3);
    rujuta.print();
    cout << endl;
    parth.print();
    return 0;
}
