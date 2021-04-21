//
// Created by parth on 20-Apr-21.
//

#ifndef MYTRY2_LLIST_H
#define MYTRY2_LLIST_H

#include <iostream>
#include "node.h"
using namespace std;

class node;
class LList {
public:
    node* head;
    int size;

    // Constructors
    LList();
    explicit LList(int x);

    // Functions
    void append(int x);
    void append(LList* ll);
    node* find_tail() const;
    void print() const;
    void copy_from(LList *ll);
    void clear();
    void prepend(int x);
    void prepend(LList* ll);
};

#endif //MYTRY2_LLIST_H
