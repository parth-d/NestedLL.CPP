#include "LList.h"

LList::LList() {
    head = new node;
    size = 0;
}

node *LList::find_tail() {
    if (!(head->holds_ll) && (head->data.value == -1723))
        return nullptr;
    node* temp = head;
//    cout << "Going below head" << endl;
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
        int data = x;
        head->data.value = data;
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
        cout << temp->data.value << "\t" << &temp->data.value << endl;
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
    }

void LList::clear() {
    node* ptr = head;
    while (ptr != nullptr)
    {
        node* temp = ptr->next;
        delete ptr;
        size--;
        ptr = temp;
    }
    head = new node;
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