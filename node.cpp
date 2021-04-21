//
// Created by parth on 20-Apr-21.
//
#include "node.h"

node::node() {
    holds_ll = false;
    data.value = -1723;
    next = nullptr;
}

node::node(int x) {
    holds_ll = false;
    data.value = x;
    next = nullptr;
}

node::node(LList *ll) {
    holds_ll = true;
    data.ll = new LList;
    data.ll->copy_from(ll);
    next = nullptr;
}
