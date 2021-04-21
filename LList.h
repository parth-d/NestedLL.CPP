//
// Created by parth on 20-Apr-21.
//

#ifndef MYTRY2_LLIST_H
#define MYTRY2_LLIST_H

#include <iostream>

using namespace std;
#include "node.h"
class node;
class LList {
public:
    node* head;
    int size;

    LList();
    explicit LList(int x);
//    explicit LList(LList* ll);
    void append(int x);
//    void append(LList* ll);
    node* find_tail();

    void print();

    void copy_from(LList *ll);
    void clear();
    void clear(node* node);
};

#endif //MYTRY2_LLIST_H
