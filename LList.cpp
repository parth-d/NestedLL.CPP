#include "LList.h"

LList::LList() {
    head = new node;
    size = 0;
}

node *LList::find_tail() {
    if (!(head->holds_ll) && (head->data.value == NULL))
        return NULL;
    node* temp = head;
    while (true)
    {
        if (temp->next == nullptr)
            return temp;
        temp = temp->next;
    }
}

void LList::append(int x) {
    node* tail = find_tail();
    if (tail == nullptr)
    {
        head->data.value = x;
        size++;
        return;
    }
    tail->next = new node(x);
    size++;
}

void LList::print(){
    if (find_tail() == nullptr)
    {
        return;
    }
    node* temp = head;
    while (temp != nullptr)
    {
        cout << temp->data.value << endl;
        temp = temp->next;
    }
}

LList::LList(int x) {
    head = new node(x);
    size = 1;
}

void LList::copy_from(LList* ll)
{
    if (ll->find_tail() == nullptr)
        return;
    node* ptr = ll->head;
    while (ptr != nullptr)
    {
        append(ptr->data.value);
        ptr = ptr->next;
    }
    return;
}

void LList::clear() {
    clear(head);
    head = new node;
}

void LList::clear(node *node) {
    if (node->next != nullptr){
        clear(node->next);
    }
    delete node;
    size--;
}

//LList::LList(LList *ll) {
//    if (!(ll->head->holds_ll) && (ll->head->data.value == 0))
//        head = new node;
//    else
//    {
//        node* ptr = ll->head;
//        while (ptr != nullptr)
//        {
//            if (ptr->holds_ll)
//                append(ptr->data.ll);
//            else
//                append(ptr->data.value);
//        }
//    }
//}

//void LList::append(LList *ll) {
//    node* tail = find_tail();
//    tail->next = new node(ll);
//}