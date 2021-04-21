//
// Created by parth on 20-Apr-21.
//

#ifndef MYTRY2_NODE_H
#define MYTRY2_NODE_H


#include "LList.h"
class LList;
class node {
    // Union definition
    union data_union{
        int value;
        LList* ll;
    };

public:

    // Object variables
    union data_union data{};
    node* next;
    bool holds_ll;

    // Constructors
    node();
    node(int x);
    node(LList* ll);
};



#endif //MYTRY2_NODE_H
