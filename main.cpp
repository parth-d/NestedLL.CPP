#include <iostream>
#include "LList.h"

int main() {
    LList parth;
    parth.append(1);
    parth.append(2);
    LList rujuta;
    rujuta.append(11);
    rujuta.append(12);
    rujuta.prepend(&parth);
    rujuta.print();
    cout << rujuta.size << endl;
    return 0;
}
